// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _AIS_Shape_HeaderFile
#define _AIS_Shape_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_AIS_Shape_HeaderFile
#include <Handle_AIS_Shape.hxx>
#endif

#ifndef _TopoDS_Shape_HeaderFile
#include <TopoDS_Shape.hxx>
#endif
#ifndef _Bnd_Box_HeaderFile
#include <Bnd_Box.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _AIS_InteractiveObject_HeaderFile
#include <AIS_InteractiveObject.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _AIS_KindOfInteractive_HeaderFile
#include <AIS_KindOfInteractive.hxx>
#endif
#ifndef _Handle_PrsMgr_PresentationManager3d_HeaderFile
#include <Handle_PrsMgr_PresentationManager3d.hxx>
#endif
#ifndef _Handle_Prs3d_Presentation_HeaderFile
#include <Handle_Prs3d_Presentation.hxx>
#endif
#ifndef _Handle_PrsMgr_PresentationManager2d_HeaderFile
#include <Handle_PrsMgr_PresentationManager2d.hxx>
#endif
#ifndef _Handle_Graphic2d_GraphicObject_HeaderFile
#include <Handle_Graphic2d_GraphicObject.hxx>
#endif
#ifndef _Handle_Prs3d_Projector_HeaderFile
#include <Handle_Prs3d_Projector.hxx>
#endif
#ifndef _Handle_Geom_Transformation_HeaderFile
#include <Handle_Geom_Transformation.hxx>
#endif
#ifndef _Handle_SelectMgr_Selection_HeaderFile
#include <Handle_SelectMgr_Selection.hxx>
#endif
#ifndef _Quantity_NameOfColor_HeaderFile
#include <Quantity_NameOfColor.hxx>
#endif
#ifndef _Graphic3d_NameOfMaterial_HeaderFile
#include <Graphic3d_NameOfMaterial.hxx>
#endif
#ifndef _TopAbs_ShapeEnum_HeaderFile
#include <TopAbs_ShapeEnum.hxx>
#endif
#ifndef _Handle_Prs3d_Drawer_HeaderFile
#include <Handle_Prs3d_Drawer.hxx>
#endif
class TopoDS_Shape;
class PrsMgr_PresentationManager3d;
class Prs3d_Presentation;
class PrsMgr_PresentationManager2d;
class Graphic2d_GraphicObject;
class Prs3d_Projector;
class Geom_Transformation;
class SelectMgr_Selection;
class Quantity_Color;
class Graphic3d_MaterialAspect;
class Bnd_Box;
class Prs3d_Drawer;


//! A framework to manage presentation and selection of shapes. <br>
//! AIS_Shape is the interactive object which is used the <br>
//! most by   applications. There are standard functions <br>
//! available which allow you to prepare selection <br>
//! operations on the constituent elements of shapes - <br>
//! vertices, edges, faces etc - in an open local context. <br>
//! The selection modes specific to "Shape" type objects <br>
//! are referred to as Standard Activation Mode. These <br>
//! modes are only taken into account in open local <br>
//! context and only act on Interactive Objects which <br>
//! have redefined the virtual method <br>
//! AcceptShapeDecomposition so that it returns true. <br>
//! Several advanced functions are also available. These <br>
//! include functions to manage deviation angle and <br>
//! deviation coefficient - both HLR and non-HLR - of <br>
//! an inheriting shape class. These services allow you to <br>
//! select one type of shape interactive object for higher <br>
//! precision drawing. When you do this, the <br>
//! AIS_Drawer::IsOwn... functions corresponding to the <br>
//! above deviation angle and coefficient functions return <br>
//! true indicating that there is a local setting available <br>
//! for the specific object. <br>
class AIS_Shape : public AIS_InteractiveObject {

public:

  //! Initializes construction of the shape shap from wires, <br>
//! edges and vertices. <br>
  Standard_EXPORT   AIS_Shape(const TopoDS_Shape& shap);
  //! Returns index 0. This value refers to SHAPE from TopAbs_ShapeEnum <br>
  Standard_EXPORT   virtual  Standard_Integer Signature() const;
  //! Returns Object as the type of Interactive Object. <br>
  Standard_EXPORT   virtual  AIS_KindOfInteractive Type() const;
  //! Returns true if the Interactive Object accepts shape decomposition. <br>
  Standard_EXPORT   virtual  Standard_Boolean AcceptShapeDecomposition() const;
  //! Constructs an instance of the shape object ashape. <br>
        void Set(const TopoDS_Shape& ashap) ;
  //! Returns this shape object. <br>
       const TopoDS_Shape& Shape() const;
  //! Sets a local value for deviation coefficient for this specific shape. <br>
  Standard_EXPORT     Standard_Boolean SetOwnDeviationCoefficient() ;
  //! Sets a local value for HLR deviation coefficient for this specific shape. <br>
  Standard_EXPORT     Standard_Boolean SetOwnHLRDeviationCoefficient() ;
  //! Sets a local value for deviation angle for this specific shape. <br>
  Standard_EXPORT     Standard_Boolean SetOwnDeviationAngle() ;
  //! Sets a local value for HLR deviation angle for this specific shape. <br>
  Standard_EXPORT     Standard_Boolean SetOwnHLRDeviationAngle() ;
  //! Sets a local value for deviation coefficient for this specific shape. <br>
  Standard_EXPORT     void SetOwnDeviationCoefficient(const Standard_Real aCoefficient) ;
  //! sets myOwnHLRDeviationCoefficient field in AIS_Drawer & <br>
//!          recomputes presentation <br>
  Standard_EXPORT     void SetOwnHLRDeviationCoefficient(const Standard_Real aCoefficient) ;
  //! this compute a new angle and Deviation from the value anAngle <br>
//!   and set the values stored in myDrawer with these that become local to the shape <br>
  Standard_EXPORT     void SetAngleAndDeviation(const Standard_Real anAngle) ;
  //! gives back the angle initial value put by the User. <br>
  Standard_EXPORT     Standard_Real UserAngle() const;
  //! sets myOwnDeviationAngle field in AIS_Drawer & recomputes presentation <br>
  Standard_EXPORT     void SetOwnDeviationAngle(const Standard_Real anAngle) ;
  //! this compute a new Angle and Deviation from the value anAngle for HLR <br>
//!   and set the values stored in myDrawer for with these that become local to the shape <br>
  Standard_EXPORT     void SetHLRAngleAndDeviation(const Standard_Real anAngle) ;
  //! sets myOwnHLRDeviationAngle field in AIS_Drawer & recomputes presentation <br>
  Standard_EXPORT     void SetOwnHLRDeviationAngle(const Standard_Real anAngle) ;
  //!   Returns true and the values of the deviation <br>
//! coefficient aCoefficient and the previous deviation <br>
//! coefficient aPreviousCoefficient. If these values are <br>
//! not already set, false is returned. <br>
  Standard_EXPORT     Standard_Boolean OwnDeviationCoefficient(Standard_Real& aCoefficient,Standard_Real& aPreviousCoefficient) const;
  //!  Returns   true and the values of the HLR deviation <br>
//! coefficient aCoefficient and the previous HLR <br>
//! deviation coefficient aPreviousCoefficient. If these <br>
//! values are not already set, false is returned. <br>
  Standard_EXPORT     Standard_Boolean OwnHLRDeviationCoefficient(Standard_Real& aCoefficient,Standard_Real& aPreviousCoefficient) const;
  //! Returns true and the values of the deviation angle <br>
//! anAngle and the previous deviation angle aPreviousAngle. <br>
//! If these values are not already set, false is returned. <br>
  Standard_EXPORT     Standard_Boolean OwnDeviationAngle(Standard_Real& anAngle,Standard_Real& aPreviousAngle) const;
  //! Returns true and the values   of the HLR deviation <br>
//! angle anAngle and of the previous HLR deviation <br>
//! angle aPreviousAngle. If these values are not <br>
//! already set, false is returned. <br>
  Standard_EXPORT     Standard_Boolean OwnHLRDeviationAngle(Standard_Real& anAngle,Standard_Real& aPreviousAngle) const;
  //! Sets the color aColor in the reconstructed <br>
//! compound shape. Acts via the Drawer methods below on the appearance of: <br>
//! -   free boundaries: <br>
//!   AIS_Drawer_FreeBoundaryAspect, <br>
//! -   isos: AIS_Drawer_UIsoAspect, <br>
//!   AIS_Drawer_VIsoAspect, <br>
//! -   shared boundaries: <br>
//!   AIS_Drawer_UnFreeBoundaryAspect, <br>
//! -   shading: AIS_Drawer_ShadingAspect, <br>
//! -   visible line color in hidden line mode: <br>
//!   AIS_Drawer_SeenLineAspect <br>
//! -   hidden line color in hidden line mode: <br>
//!   AIS_Drawer_HiddenLineAspect. <br>
  Standard_EXPORT   virtual  void SetColor(const Quantity_NameOfColor aColor) ;
  
  Standard_EXPORT   virtual  void SetColor(const Quantity_Color& aColor) ;
  //! Removes settings for color in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void UnsetColor() ;
  //! Sets the value aValue for line width in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void SetWidth(const Standard_Real aValue) ;
  //! Removes the setting for line width in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void UnsetWidth() ;
  
  Standard_EXPORT   virtual  void SetMaterial(const Graphic3d_NameOfMaterial aName) ;
  //! Allows you to provide settings for the material aName <br>
//! in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void SetMaterial(const Graphic3d_MaterialAspect& aName) ;
  //! Removes settings for material in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void UnsetMaterial() ;
  //! Sets the value aValue for transparency in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void SetTransparency(const Standard_Real aValue = 0.6) ;
  //! Removes the setting for transparency in the reconstructed compound shape. <br>
  Standard_EXPORT   virtual  void UnsetTransparency() ;
  //! Constructs a bounding box with which to reconstruct <br>
//! compound topological shapes for presentation. <br>
  Standard_EXPORT   virtual const Bnd_Box& BoundingBox() ;
  //! Returns the NameOfColor attributes of the shape accordingly to <br>
//!  the current facing model; <br>
  Standard_EXPORT   virtual  Quantity_NameOfColor Color() const;
  //! Returns the Color attributes of the shape accordingly to <br>
//!  the current facing model; <br>
  Standard_EXPORT   virtual  void Color(Quantity_Color& aColor) const;
  //! Returns the NameOfMaterial attributes of the shape accordingly to <br>
//!  the current facing model; <br>
  Standard_EXPORT   virtual  Graphic3d_NameOfMaterial Material() const;
  //! Returns the transparency attributes of the shape accordingly to <br>
//!  the current facing model; <br>
  Standard_EXPORT   virtual  Standard_Real Transparency() const;
  //! Activates the same TopAbs shape enumerations as <br>
//! those used by SelectionMode assigning a type to the mode aDecompositionMode. <br>
  Standard_EXPORT   static  TopAbs_ShapeEnum SelectionType(const Standard_Integer aDecompositionMode) ;
  //! Establishes an equivalence between a mode and the <br>
//! type, aShapeType,   of selection. The correspondences are as follows: <br>
//! -   mode 0 - Shape <br>
//! -   mode 1 - Vertex <br>
//! -   mode 2 - Edge <br>
//! -   mode 3 - Wire <br>
//! -   mode 4 - Face <br>
//! -   mode 5 - Shell <br>
//! -   mode 6 - Solid <br>
//! -   mode 7 - Compsolid <br>
//! -   mode 8 - Compound <br>
  Standard_EXPORT   static  Standard_Integer SelectionMode(const TopAbs_ShapeEnum aShapeType) ;
  
  Standard_EXPORT   static  Standard_Real GetDeflection(const TopoDS_Shape& aShape,const Handle(Prs3d_Drawer)& aDrawer) ;




  DEFINE_STANDARD_RTTI(AIS_Shape)

protected:

  
  Standard_EXPORT   virtual  void Compute(const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,const Handle(Prs3d_Presentation)& aPresentation,const Standard_Integer aMode = 0) ;
  
  Standard_EXPORT   virtual  void Compute(const Handle(PrsMgr_PresentationManager2d)& aPresentationManager,const Handle(Graphic2d_GraphicObject)& aPresentation,const Standard_Integer aMode = 0) ;
  
  Standard_EXPORT   virtual  void Compute(const Handle(Prs3d_Projector)& aProjector,const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   virtual  void Compute(const Handle(Prs3d_Projector)& aProjector,const Handle(Geom_Transformation)& aTrsf,const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   virtual  void ComputeSelection(const Handle(SelectMgr_Selection)& aSelection,const Standard_Integer aMode) ;
  
  Standard_EXPORT     void LoadRecomputable(const Standard_Integer TheMode) ;
  
  Standard_EXPORT   static  void DisplayBox(const Handle(Prs3d_Presentation)& aPrs,const Bnd_Box& aBox,const Handle(Prs3d_Drawer)& aDrawer) ;

TopoDS_Shape myshape;
Bnd_Box myBB;
Standard_Boolean myCompBB;


private: 

  
  Standard_EXPORT     void Compute(const Handle(Prs3d_Projector)& aProjector,const Handle(Prs3d_Presentation)& aPresentation,const TopoDS_Shape& ashape) ;

Standard_Real myInitAng;


};


#include <AIS_Shape.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
