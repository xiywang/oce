// Created on: 2000-08-31
// Created by: Andrey BETENEV
// Copyright (c) 2000-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.


#include <ShapeProcess_OperLibrary.ixx>

#include <Precision.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRep_Builder.hxx>
#include <BRepLib.hxx>

#include <Message_MsgFile.hxx>
#include <Message_ProgressIndicator.hxx>

#include <ShapeExtend_MsgRegistrator.hxx>
#include <ShapeProcess.hxx>
#include <ShapeProcess_UOperator.hxx>
#include <ShapeProcess_ShapeContext.hxx>

#include <BRepTools_Modifier.hxx>
#include <BRepTools_Modification.hxx>
#include <ShapeCustom_DirectModification.hxx>
#include <ShapeCustom_RestrictionParameters.hxx>
#include <ShapeCustom_BSplineRestriction.hxx>
#include <ShapeCustom_ConvertToRevolution.hxx>
#include <ShapeCustom_SweptToElementary.hxx>
#include <ShapeCustom_ConvertToBSpline.hxx>

#include <ShapeExtend.hxx>
#include <ShapeBuild_ReShape.hxx>
#include <ShapeUpgrade_ShapeDivideAngle.hxx>
#include <ShapeUpgrade_ShapeConvertToBezier.hxx>
#include <ShapeUpgrade_ShapeDivideContinuity.hxx>
#include <ShapeUpgrade_ShapeDivideClosed.hxx>
#include <ShapeUpgrade_ShapeDivideClosedEdges.hxx>

#include <ShapeFix_ShapeTolerance.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_FixSmallFace.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <ShapeFix.hxx>
#include <ShapeFix_SplitCommonVertex.hxx>


//=======================================================================
//function : ApplyModifier
//purpose  : Applies BRepTools_Modification to a shape,
//           taking into account sharing of components of compounds
//=======================================================================

TopoDS_Shape ShapeProcess_OperLibrary::ApplyModifier (const TopoDS_Shape &S, 
                                                      const Handle(ShapeProcess_ShapeContext)& context,
                                                      const Handle(BRepTools_Modification) &M,
                                                      TopTools_DataMapOfShapeShape &map)
{
  // protect against INTERNAL/EXTERNAL shapes
  TopoDS_Shape SF = S.Oriented(TopAbs_FORWARD);

  // Process COMPOUNDs separately in order to handle sharing in assemblies
  if ( SF.ShapeType() == TopAbs_COMPOUND ) {
    Standard_Boolean locModified = Standard_False;
    TopoDS_Compound C;
    BRep_Builder B;
    B.MakeCompound ( C );
    for ( TopoDS_Iterator it(SF); it.More(); it.Next() ) {
      TopoDS_Shape shape = it.Value();
      TopLoc_Location L = shape.Location(), nullLoc;
      shape.Location ( nullLoc );
      TopoDS_Shape res;
      if(map.IsBound ( shape ))
	res = map.Find ( shape ).Oriented ( shape.Orientation() );

      else {
	res = ApplyModifier (shape, context, M, map );
	map.Bind ( shape, res );
      }
      if ( ! res.IsSame ( shape ) ) locModified = Standard_True;
      res.Location ( L );
      B.Add ( C, res );
    }
    if ( ! locModified ) return S;
    
    map.Bind ( SF, C );
    return C.Oriented ( S.Orientation() );
  }

  // Modify the shape
  BRepTools_Modifier MD(SF,M);
  context->RecordModification ( SF, MD );
  return MD.ModifiedShape(SF).Oriented(S.Orientation());
}


//=======================================================================
//function : directfaces
//purpose  : 
//=======================================================================

static Standard_Boolean directfaces (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Handle(ShapeCustom_DirectModification) DM = new ShapeCustom_DirectModification;
  TopTools_DataMapOfShapeShape map;
  TopoDS_Shape res = ShapeProcess_OperLibrary::ApplyModifier ( ctx->Result(), ctx, DM, map );
  ctx->RecordModification ( map );
  ctx->SetResult ( res );
  return Standard_True;
}


//=======================================================================
//function : sameparam
//purpose  : 
//=======================================================================

static Standard_Boolean sameparam (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;
  ShapeFix::SameParameter ( ctx->Result(), 
			    ctx->IntegerVal ( "Force", Standard_False ),
			    ctx->RealVal ( "Tolerance3d", Precision::Confusion() /* -1 */) ); 
  // WARNING: no update of context yet!
  return Standard_True;
}


//=======================================================================
//function : settol
//purpose  : 
//=======================================================================

static Standard_Boolean settol (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Real val;
  if ( ctx->IntegerVal ( "Mode", 0 ) >0 && ctx->GetReal ( "Value", val ) ) {
    Standard_Real rat = ctx->RealVal ( "Ratio", 1. );
    if ( rat >= 1 ) {
      ShapeFix_ShapeTolerance SFST;
      SFST.LimitTolerance (ctx->Result(), val/rat, val*rat);
    }
  }

  BRepLib::UpdateTolerances (ctx->Result(),Standard_True);

  Standard_Real reg;
  if ( ctx->GetReal ("Regularity", reg) )  
    BRepLib::EncodeRegularity (ctx->Result(), reg);

  // WARNING: no update of context yet!
  return Standard_True;
}


//=======================================================================
//function : splitangle
//purpose  : 
//=======================================================================

static Standard_Boolean splitangle (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;
  
  ShapeUpgrade_ShapeDivideAngle SDA ( ctx->RealVal ( "Angle", 2*M_PI ), ctx->Result() );
  SDA.SetMaxTolerance ( ctx->RealVal ( "MaxTolerance", 1. ) );
  
  if ( ! SDA.Perform() && SDA.Status (ShapeExtend_FAIL) ) {
#ifdef DEB
    cout<<"ShapeDivideAngle failed"<<endl;
#endif
    return Standard_False;
  }
  
  ctx->RecordModification ( SDA.GetContext() );
  ctx->SetResult ( SDA.Result() );
  return Standard_True;
}


//=======================================================================
//function : bsplinerestriction
//purpose  : 
//=======================================================================

static Standard_Boolean bsplinerestriction (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Boolean ModeSurf  = ctx->IntegerVal ( "SurfaceMode", Standard_True );
  Standard_Boolean ModeC3d   = ctx->IntegerVal ( "Curve3dMode", Standard_True );
  Standard_Boolean ModeC2d   = ctx->IntegerVal ( "Curve2dMode", Standard_True );

  Standard_Real aTol3d = ctx->RealVal ( "Tolerance3d", 0.01 );
  Standard_Real aTol2d = ctx->RealVal ( "Tolerance2d", 1e-06 );
  
  GeomAbs_Shape aCont3d = ctx->ContinuityVal ( "Continuity3d", GeomAbs_C1 );
  GeomAbs_Shape aCont2d = ctx->ContinuityVal ( "Continuity2d", GeomAbs_C2 );

  Standard_Integer aMaxDeg = ctx->IntegerVal ( "RequiredDegree", 9 );
  Standard_Integer aMaxSeg = ctx->IntegerVal ( "RequiredNbSegments", 10000 );
  
  Standard_Boolean ModeDeg  = ctx->IntegerVal ( "PreferDegree", Standard_True );
  Standard_Boolean Rational = ctx->IntegerVal ( "RationalToPolynomial", Standard_False );
  
  Handle(ShapeCustom_RestrictionParameters)   aParameters = new ShapeCustom_RestrictionParameters;
  ctx->GetInteger ( "MaxDegree",          aParameters->GMaxDegree() );
  ctx->GetInteger ( "MaxNbSegments",      aParameters->GMaxSeg() );
  ctx->GetBoolean ( "OffsetSurfaceMode",  aParameters->ConvertOffsetSurf() );
  ctx->GetBoolean ( "OffsetCurve3dMode",  aParameters->ConvertOffsetCurv3d() );
  ctx->GetBoolean ( "OffsetCurve2dMode",  aParameters->ConvertOffsetCurv2d() );
  ctx->GetBoolean ( "LinearExtrusionMode",aParameters->ConvertExtrusionSurf() );
  ctx->GetBoolean ( "RevolutionMode",     aParameters->ConvertRevolutionSurf() );
  ctx->GetBoolean ( "SegmentSurfaceMode", aParameters->SegmentSurfaceMode() );
  ctx->GetBoolean ( "ConvCurve3dMode",    aParameters->ConvertCurve3d() );
  ctx->GetBoolean ( "ConvCurve2dMode",    aParameters->ConvertCurve2d() );
  ctx->GetBoolean ( "BezierMode",         aParameters->ConvertBezierSurf() );
  //modes to convert elementary surfaces
  ctx->GetBoolean ( "PlaneMode",          aParameters->ConvertPlane() );
  //ctx->GetBoolean ("ElementarySurfMode", aParameters->ConvertElementarySurf());
  ctx->GetBoolean ( "ConicalSurfMode", aParameters->ConvertConicalSurf());
  ctx->GetBoolean ( "CylindricalSurfMode", aParameters->ConvertCylindricalSurf());
  ctx->GetBoolean ( "ToroidalSurfMode", aParameters->ConvertToroidalSurf());
  ctx->GetBoolean ( "SphericalSurfMode", aParameters->ConvertSphericalSurf());
  
  Handle(ShapeCustom_BSplineRestriction) LD = 
    new ShapeCustom_BSplineRestriction ( ModeSurf, ModeC3d, ModeC2d,
					 aTol3d, aTol2d, aCont3d, aCont2d,
					 aMaxDeg, aMaxSeg, ModeDeg, Rational, aParameters );
  TopTools_DataMapOfShapeShape map;
  TopoDS_Shape res = ShapeProcess_OperLibrary::ApplyModifier ( ctx->Result(), ctx, LD, map );
  ctx->RecordModification ( map );
  ctx->SetResult ( res );
  return Standard_True;
}


//=======================================================================
//function : torevol
//purpose  : 
//=======================================================================

static Standard_Boolean torevol (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Handle(ShapeCustom_ConvertToRevolution) CR =
    new ShapeCustom_ConvertToRevolution();
  TopTools_DataMapOfShapeShape map;
  TopoDS_Shape res = ShapeProcess_OperLibrary::ApplyModifier ( ctx->Result(), ctx, CR, map );
  ctx->RecordModification ( map );
  ctx->SetResult ( res );
  return Standard_True;
}


//=======================================================================
//function : swepttoelem
//purpose  : 
//=======================================================================

static Standard_Boolean swepttoelem (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Handle(ShapeCustom_SweptToElementary) SE = new ShapeCustom_SweptToElementary();
  TopTools_DataMapOfShapeShape map;
  TopoDS_Shape res = ShapeProcess_OperLibrary::ApplyModifier ( ctx->Result(), ctx, SE, map );
  ctx->RecordModification ( map );
  ctx->SetResult ( res );
  return Standard_True;
}


//=======================================================================
//function : shapetobezier
//purpose  : 
//=======================================================================

static Standard_Boolean shapetobezier (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Boolean ModeC3d        = ctx->BooleanVal ( "Curve3dMode",        Standard_False );
  Standard_Boolean ModeC2d        = ctx->BooleanVal ( "Curve2dMode",        Standard_False );
  Standard_Boolean ModeSurf       = ctx->BooleanVal ( "SurfaceMode",        Standard_False );
  Standard_Boolean ModeLine3d     = ctx->BooleanVal ( "Line3dMode",         Standard_True );
  Standard_Boolean ModeCircle3d   = ctx->BooleanVal ( "Circle3dMode",       Standard_True );
  Standard_Boolean ModeConic3d    = ctx->BooleanVal ( "Conic3dMode",        Standard_True );
  Standard_Boolean SegmentMode    = ctx->BooleanVal ( "SegmentSurfaceMode", Standard_True );
  Standard_Boolean PlaneMode      = ctx->BooleanVal ( "PlaneMode",          Standard_True );
  Standard_Boolean RevolutionMode = ctx->BooleanVal ( "RevolutionMode",     Standard_True );
  Standard_Boolean ExtrusionMode  = ctx->BooleanVal ( "ExtrusionMode",      Standard_True );
  Standard_Boolean BSplineMode    = ctx->BooleanVal ( "BSplineMode",        Standard_True );

  ShapeUpgrade_ShapeConvertToBezier SCB (ctx->Result());
  SCB.SetSurfaceSegmentMode(SegmentMode);
  SCB.SetSurfaceConversion (ModeSurf);
  SCB.Set2dConversion (ModeC2d);
  SCB.Set3dConversion (ModeC3d);
  if(ModeC3d) {
    SCB.Set3dLineConversion (ModeLine3d);
    SCB.Set3dCircleConversion (ModeCircle3d);
    SCB.Set3dConicConversion (ModeConic3d);
  }
  if(ModeSurf) {
    SCB.SetPlaneMode(PlaneMode);
    SCB.SetRevolutionMode(RevolutionMode);
    SCB.SetExtrusionMode(ExtrusionMode);
    SCB.SetBSplineMode(BSplineMode);
  }
  
  Standard_Real maxTol, minTol;
  if ( ctx->GetReal ( "MaxTolerance",   maxTol ) ) SCB.SetMaxTolerance(maxTol);
  if ( ctx->GetReal ( "MinCurveLength", minTol ) ) SCB.SetMinTolerance(minTol);
  
  Standard_Boolean EdgeMode;
  if ( ctx->GetBoolean ( "EdgeMode", EdgeMode ) ) SCB.SetEdgeMode(EdgeMode);
 
  if ( ! SCB.Perform() && SCB.Status (ShapeExtend_FAIL) ) { 
#ifdef DEB
    cout<<"Shape::ShapeConvertToBezier failed"<<endl; // !!!!
#endif
    return Standard_False;
  }

  ctx->RecordModification ( SCB.GetContext() );
  ctx->SetResult ( SCB.Result() );
  return Standard_True;
}


//=======================================================================
//function : converttobspline
//purpose  : 
//=======================================================================

static Standard_Boolean converttobspline (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Boolean extrMode   = ctx->BooleanVal ( "LinearExtrusionMode", Standard_True );
  Standard_Boolean revolMode  = ctx->BooleanVal ( "RevolutionMode",      Standard_True ); 
  Standard_Boolean offsetMode = ctx->BooleanVal ( "OffsetMode",          Standard_True );
  
  Handle(ShapeCustom_ConvertToBSpline) CBspl = new ShapeCustom_ConvertToBSpline();
  CBspl->SetExtrusionMode(extrMode);
  CBspl->SetRevolutionMode(revolMode);
  CBspl->SetOffsetMode(offsetMode);
    
  TopTools_DataMapOfShapeShape map;
  TopoDS_Shape res = ShapeProcess_OperLibrary::ApplyModifier ( ctx->Result(), ctx, CBspl, map );
  ctx->RecordModification ( map );
  ctx->SetResult ( res );
  return Standard_True;
}


//=======================================================================
//function : splitcontinuity
//purpose  : Split by Continuity
//=======================================================================

static Standard_Boolean splitcontinuity (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Real aTol = ctx->RealVal ( "Tolerance3d", 1.e-7 );
  Standard_Real aTol2D = ctx->RealVal ( "Tolerance2d", 1.e-9 );
  GeomAbs_Shape aCrvCont = ctx->ContinuityVal ( "CurveContinuity",   GeomAbs_C1 );
  GeomAbs_Shape aSrfCont = ctx->ContinuityVal ( "SurfaceContinuity", GeomAbs_C1 );
  GeomAbs_Shape aCrv2dCont = ctx->ContinuityVal ( "Curve2dContinuity",   GeomAbs_C1 );
  ShapeUpgrade_ShapeDivideContinuity tool (ctx->Result());
  tool.SetBoundaryCriterion(aCrvCont);
  tool.SetSurfaceCriterion(aSrfCont);
  tool.SetPCurveCriterion(aCrv2dCont);
  tool.SetTolerance(aTol);
  tool.SetTolerance2d(aTol2D);
  
  Standard_Real maxTol;
  if ( ctx->GetReal ( "MaxTolerance", maxTol ) ) tool.SetMaxTolerance(maxTol);
  
  if ( ! tool.Perform() && tool.Status (ShapeExtend_FAIL) ) { 
#ifdef DEB
    cout<<"SplitContinuity failed"<<endl; 
#endif
    return Standard_False; 
  }
  
  ctx->RecordModification ( tool.GetContext() );
  ctx->SetResult ( tool.Result() );
  return Standard_True;
}


//=======================================================================
//function : splitclosedfaces
//purpose  : 
//=======================================================================

static Standard_Boolean splitclosedfaces (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  ShapeUpgrade_ShapeDivideClosed tool ( ctx->Result() );

  Standard_Real closeTol;
  if ( ctx->GetReal ( "CloseTolerance", closeTol ) ) tool.SetPrecision(closeTol);
  
  Standard_Real maxTol;
  if ( ctx->GetReal ( "MaxTolerance", maxTol ) ) tool.SetMaxTolerance(maxTol);
  
  Standard_Integer num = ctx->IntegerVal ( "NbSplitPoints", 1 );
   Standard_Boolean hasSeg = Standard_True;
   ctx->GetBoolean ( "SegmentSurfaceMode", hasSeg);
  
  tool.SetNbSplitPoints(num);
  tool.SetSurfaceSegmentMode(hasSeg);
  if ( ! tool.Perform() && tool.Status (ShapeExtend_FAIL) ) { 
#ifdef DEB
    cout<<"Splitting of closed faces failed"<<endl; 
#endif
    return Standard_False; 
  }
  
  ctx->RecordModification ( tool.GetContext() );
  ctx->SetResult ( tool.Result() );
  return Standard_True;
}


//=======================================================================
//function : fixfacesize
//purpose  : 
//=======================================================================

static Standard_Boolean fixfacesize (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Handle(ShapeBuild_ReShape) reshape = new ShapeBuild_ReShape;
  ShapeFix_FixSmallFace FSC;
  FSC.SetContext(reshape);
  FSC.Init(ctx->Result());

  Standard_Real aTol;
  if ( ctx->GetReal ( "Tolerance", aTol ) ) FSC.SetPrecision (aTol);

  FSC.Perform();
  TopoDS_Shape newsh = FSC.Shape();

  if ( newsh != ctx->Result() ) {
    ctx->RecordModification ( reshape );
    ctx->SetResult ( newsh );
  }

  return Standard_True;
}


//=======================================================================
//function : fixwgaps
//purpose  : 
//=======================================================================

static Standard_Boolean fixwgaps (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Real aTol3d = ctx->RealVal ( "Tolerance3d", Precision::Confusion() );

  Handle(ShapeBuild_ReShape) reshape = new ShapeBuild_ReShape;
  Handle(ShapeFix_Wireframe) sfwf = new ShapeFix_Wireframe(ctx->Result());
  sfwf->SetContext(reshape);
  sfwf->SetPrecision(aTol3d);
  sfwf->FixWireGaps();
  TopoDS_Shape result = sfwf->Shape();

  if ( result != ctx->Result() ) {
    ctx->RecordModification ( reshape );
    ctx->SetResult ( result );
  }
  return Standard_True;
}

/*
//=======================================================================
//function :
//purpose  : 
//=======================================================================

static Standard_Boolean dropsmalledges (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  //Handle(ShapeBuild_ReShape) ctx = new ShapeBuild_ReShape;
  Handle(MoniFrame_Element) elem = astep->Operand();
  TopoDS_Shape Shape = MoniShape::Shape(elem);
  Standard_Real aTol3d = Precision::Confusion();
  Handle(MoniFrame_TypedValue) ptol3d   = aproc->StackParam("Tolerance3d",Standard_True);
  if (ptol3d->IsSetValue()) aTol3d = ptol3d->RealValue();
  Handle(ShapeBuild_ReShape) context; 
  TopoDS_Shape result = ShapeFix::RemoveSmallEdges(Shape,aTol3d,context);
  if (result == Shape) astep->AddTouched (aproc->Infos(),MoniShape::Element(Shape));
  else 
    MoniShapeSW::UpdateFromReShape (aproc->Infos(), astep, Shape, context, TopAbs_FACE);
  return 0;
}
*/


//=======================================================================
//function : mergesmalledges
//purpose  : 
//=======================================================================

static Standard_Boolean mergesmalledges (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Real aTol3d = ctx->RealVal ( "Tolerance3d", Precision::Confusion() );

  Handle(ShapeBuild_ReShape) reshape = new ShapeBuild_ReShape;
  ShapeFix_Wireframe ShapeFixWireframe(ctx->Result());
  ShapeFixWireframe.SetContext(reshape);
  ShapeFixWireframe.SetPrecision(aTol3d);
  
  if ( ShapeFixWireframe.FixSmallEdges() ) {
    ctx->RecordModification ( reshape );
  }
  return Standard_True;
}


//=======================================================================
//function : fixshape
//purpose  : 
//=======================================================================

static Standard_Boolean fixshape (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  // activate message mechanism if it is supported by context
  Handle(ShapeExtend_MsgRegistrator) msg;
  if ( ! ctx->Messages().IsNull() ) msg = new ShapeExtend_MsgRegistrator;
  
  Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
  sfs->SetMsgRegistrator ( msg );
  Handle(ShapeFix_Face) sff  = Handle(ShapeFix_Face)::DownCast(sfs->FixFaceTool());
  Handle(ShapeFix_Wire) sfw  = Handle(ShapeFix_Wire)::DownCast(sfs->FixWireTool());
  
  sfs->SetPrecision    ( ctx->RealVal ( "Tolerance3d",    Precision::Confusion() ) );
  sfs->SetMinTolerance ( ctx->RealVal ( "MinTolerance3d", Precision::Confusion() ) );
  sfs->SetMaxTolerance ( ctx->RealVal ( "MaxTolerance3d", Precision::Confusion() ) );	

  sfs->FixFreeShellMode()     = ctx->IntegerVal ( "FixFreeShellMode", -1 );
  sfs->FixFreeFaceMode()      = ctx->IntegerVal ( "FixFreeFaceMode", -1 );
  sfs->FixFreeWireMode()      = ctx->IntegerVal ( "FixFreeWireMode", -1 );
  sfs->FixSameParameterMode() = ctx->IntegerVal ( "FixSameParameterMode", -1 );
  sfs->FixSolidMode()         = ctx->IntegerVal ( "FixSolidMode", -1 );
  sfs->FixVertexPositionMode() = ctx->IntegerVal ( "FixVertexPositionMode", 0 );

  sfs->FixSolidTool()->FixShellMode() = ctx->IntegerVal ( "FixShellMode", -1 );
  sfs->FixSolidTool()->CreateOpenSolidMode() = ctx->IntegerVal ( "CreateOpenSolidMode", 1 );

  sfs->FixShellTool()->FixFaceMode() = ctx->IntegerVal ( "FixFaceMode", -1 );

  //parameters for ShapeFix_Face
  sff->FixWireMode()              = ctx->IntegerVal ( "FixWireMode", -1 );
  sff->FixOrientationMode()       = ctx->IntegerVal ( "FixOrientationMode", -1 );
  sff->FixAddNaturalBoundMode()   = ctx->IntegerVal ( "FixAddNaturalBoundMode", -1 );
  sff->FixMissingSeamMode()       = ctx->IntegerVal ( "FixMissingSeamMode", -1 );
  sff->FixSmallAreaWireMode()     = ctx->IntegerVal ( "FixSmallAreaWireMode", -1 );
  sff->FixIntersectingWiresMode() = ctx->IntegerVal ( "FixIntersectingWiresMode", -1 );
  sff->FixLoopWiresMode()         = ctx->IntegerVal ( "FixLoopWiresMode", -1 );
  sff->FixSplitFaceMode()         = ctx->IntegerVal ( "FixSplitFaceMode", -1 );

  //parameters for ShapeFix_Wire
  sfw->ModifyTopologyMode()   = ctx->BooleanVal ( "ModifyTopologyMode",   Standard_False );
  sfw->ModifyGeometryMode()   = ctx->BooleanVal ( "ModifyGeometryMode",   Standard_True );
  sfw->ClosedWireMode()       = ctx->BooleanVal ( "ClosedWireMode",       Standard_True );
  sfw->PreferencePCurveMode() = ctx->BooleanVal ( "PreferencePCurveMode", Standard_True );
  sfw->FixReorderMode()	             = ctx->IntegerVal ( "FixReorderMode", -1 );
  sfw->FixSmallMode()	             = ctx->IntegerVal ( "FixSmallMode", -1 );
  sfw->FixConnectedMode()            = ctx->IntegerVal ( "FixConnectedMode", -1 );
  sfw->FixEdgeCurvesMode()           = ctx->IntegerVal ( "FixEdgeCurvesMode", -1 );
  sfw->FixDegeneratedMode()          = ctx->IntegerVal ( "FixDegeneratedMode", -1 );
  sfw->FixLackingMode()              = ctx->IntegerVal ( "FixLackingMode", -1 );
  sfw->FixSelfIntersectionMode()     = ctx->IntegerVal ( "FixSelfIntersectionMode", -1 );
  sfw->ModifyRemoveLoopMode()        = ctx->IntegerVal ( "RemoveLoopMode", -1);
  sfw->FixReversed2dMode()           = ctx->IntegerVal ( "FixReversed2dMode", -1 );
  sfw->FixRemovePCurveMode()         = ctx->IntegerVal ( "FixRemovePCurveMode", -1 );
  sfw->FixRemoveCurve3dMode()        = ctx->IntegerVal ( "FixRemoveCurve3dMode", -1 );
  sfw->FixAddPCurveMode()            = ctx->IntegerVal ( "FixAddPCurveMode", -1 );
  sfw->FixAddCurve3dMode()           = ctx->IntegerVal ( "FixAddCurve3dMode", -1 );
  sfw->FixShiftedMode()	             = ctx->IntegerVal ( "FixShiftedMode", -1 );
  sfw->FixSeamMode()	             = ctx->IntegerVal ( "FixSeamMode", -1 );
  sfw->FixSameParameterMode()        = ctx->IntegerVal ( "FixEdgeSameParameterMode", -1 );
  sfw->FixNotchedEdgesMode()         = ctx->IntegerVal ( "FixNotchedEdgesMode", -1 );
  sfw->FixSelfIntersectingEdgeMode() = ctx->IntegerVal ( "FixSelfIntersectingEdgeMode", -1 );
  sfw->FixIntersectingEdgesMode()    = ctx->IntegerVal ( "FixIntersectingEdgesMode", -1 );
  sfw->FixNonAdjacentIntersectingEdgesMode() = ctx->IntegerVal ( "FixNonAdjacentIntersectingEdgesMode", -1 );
  
  sfs->Init(ctx->Result());
  sfs->Perform(ctx->Progress());

  if ( !ctx->Progress().IsNull() && ctx->Progress()->UserBreak() )
    return Standard_False;

  TopoDS_Shape result = sfs->Shape();
  if ( result != ctx->Result() ) {
    ctx->RecordModification ( sfs->Context(), msg );
    ctx->SetResult ( result );
  }
  return Standard_True;
}


//=======================================================================
//function : spltclosededges
//purpose  : 
//=======================================================================

static Standard_Boolean spltclosededges (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx =
    Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Standard_Integer nbSplits = ctx->IntegerVal ( "NbSplitPoints", 1 );

  ShapeUpgrade_ShapeDivideClosedEdges tool (ctx->Result());
  tool.SetNbSplitPoints(nbSplits);
  
  if ( ! tool.Perform() && tool.Status (ShapeExtend_FAIL) ) { 
#ifdef DEB
    cout<<"Splitting of closed edges failed"<<endl; 
#endif
    return Standard_False; 
  }
  
  ctx->RecordModification ( tool.GetContext() );
  ctx->SetResult ( tool.Result() );
  return Standard_True;
}


//=======================================================================
//function : splitcommonvertex
//purpose  : Two wires have common vertex - this case is valid in BRep model
//           and isn't valid in STEP => before writing into STEP it is necessary
//           to split this vertex (each wire must has one vertex)
//=======================================================================
static Standard_Boolean splitcommonvertex (const Handle(ShapeProcess_Context)& context)
{
  Handle(ShapeProcess_ShapeContext) ctx = Handle(ShapeProcess_ShapeContext)::DownCast ( context );
  if ( ctx.IsNull() ) return Standard_False;

  Handle(ShapeBuild_ReShape) reshape = new ShapeBuild_ReShape;
  ShapeFix_SplitCommonVertex SCV;
  SCV.SetContext(reshape);
  SCV.Init(ctx->Result());

  SCV.Perform();
  TopoDS_Shape newsh = SCV.Shape();

  if ( newsh != ctx->Result() ) {
    ctx->RecordModification ( reshape );
    ctx->SetResult ( newsh );
  }

  return Standard_True;
}


//=======================================================================
//function : Init
//purpose  : Register standard operators
//=======================================================================

void ShapeProcess_OperLibrary::Init ()
{
  static Standard_Boolean done = Standard_False;
  if ( done ) return;
  done = Standard_True;

  ShapeExtend::Init();
  
  // load message file for Shape Processing
  Message_MsgFile::LoadFromEnv ("CSF_SHMessage", "SHAPE");

  ShapeProcess::RegisterOperator ( "DirectFaces",           new ShapeProcess_UOperator ( directfaces ) );
  ShapeProcess::RegisterOperator ( "SameParameter",         new ShapeProcess_UOperator ( sameparam ) );
  ShapeProcess::RegisterOperator ( "SetTolerance",          new ShapeProcess_UOperator ( settol ) );  
  ShapeProcess::RegisterOperator ( "SplitAngle",            new ShapeProcess_UOperator ( splitangle ) );
  ShapeProcess::RegisterOperator ( "BSplineRestriction",    new ShapeProcess_UOperator ( bsplinerestriction ) );
  ShapeProcess::RegisterOperator ( "ElementaryToRevolution",new ShapeProcess_UOperator ( torevol ) );
  ShapeProcess::RegisterOperator ( "SweptToElementary",     new ShapeProcess_UOperator ( swepttoelem ) );
  ShapeProcess::RegisterOperator ( "SurfaceToBSpline",      new ShapeProcess_UOperator ( converttobspline ) );
  ShapeProcess::RegisterOperator ( "ToBezier",              new ShapeProcess_UOperator ( shapetobezier ) );
  ShapeProcess::RegisterOperator ( "SplitContinuity",       new ShapeProcess_UOperator ( splitcontinuity ) );
  ShapeProcess::RegisterOperator ( "SplitClosedFaces",      new ShapeProcess_UOperator ( splitclosedfaces ) );
  ShapeProcess::RegisterOperator ( "FixWireGaps",           new ShapeProcess_UOperator ( fixwgaps ) );
  ShapeProcess::RegisterOperator ( "FixFaceSize",           new ShapeProcess_UOperator ( fixfacesize ) );
  ShapeProcess::RegisterOperator ( "DropSmallEdges",        new ShapeProcess_UOperator ( mergesmalledges ) );
  ShapeProcess::RegisterOperator ( "FixShape",              new ShapeProcess_UOperator ( fixshape ) );
  ShapeProcess::RegisterOperator ( "SplitClosedEdges",      new ShapeProcess_UOperator ( spltclosededges ) );
  ShapeProcess::RegisterOperator ( "SplitCommonVertex",     new ShapeProcess_UOperator ( splitcommonvertex ) );
}
