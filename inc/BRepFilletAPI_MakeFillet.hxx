// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepFilletAPI_MakeFillet_HeaderFile
#define _BRepFilletAPI_MakeFillet_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _ChFi3d_FilBuilder_HeaderFile
#include <ChFi3d_FilBuilder.hxx>
#endif
#ifndef _TopTools_MapOfShape_HeaderFile
#include <TopTools_MapOfShape.hxx>
#endif
#ifndef _BRepFilletAPI_LocalOperation_HeaderFile
#include <BRepFilletAPI_LocalOperation.hxx>
#endif
#ifndef _ChFi3d_FilletShape_HeaderFile
#include <ChFi3d_FilletShape.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Handle_Law_Function_HeaderFile
#include <Handle_Law_Function.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_TopOpeBRepBuild_HBuilder_HeaderFile
#include <Handle_TopOpeBRepBuild_HBuilder.hxx>
#endif
#ifndef _Handle_ChFiDS_SecHArray1_HeaderFile
#include <Handle_ChFiDS_SecHArray1.hxx>
#endif
#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _ChFiDS_ErrorStatus_HeaderFile
#include <ChFiDS_ErrorStatus.hxx>
#endif
class StdFail_NotDone;
class Standard_NoSuchObject;
class TopoDS_Shape;
class TopoDS_Edge;
class Law_Function;
class TColgp_Array1OfPnt2d;
class TopoDS_Vertex;
class TopOpeBRepBuild_HBuilder;
class TopTools_ListOfShape;
class ChFiDS_SecHArray1;
class Geom_Surface;


//! Describes functions to build fillets on the broken edges of a shell or solid. <br>
//! A MakeFillet object provides a framework for: <br>
//! -   initializing the construction algorithm with a given shape, <br>
//! -   acquiring the data characterizing the fillets, <br>
//! -   building the fillets and constructing the resulting shape, and <br>
//! -   consulting the result. <br>
class BRepFilletAPI_MakeFillet  : public BRepFilletAPI_LocalOperation {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  //! Initializes   the computation    of   the  fillets. <br>
//!          <FShape> sets   the type   of fillet  surface. The <br>
//!          default value is ChFi3d_Rational (classical  nurbs <br>
//!          representation of  circles).   ChFi3d_QuasiAngular <br>
//!          corresponds to  a  nurbs representation of circles <br>
//!          which   parameterisation matches  the  circle one. <br>
//!          ChFi3d_Polynomial  corresponds to  a    polynomial <br>
//!          representation of circles. <br>
  Standard_EXPORT   BRepFilletAPI_MakeFillet(const TopoDS_Shape& S,const ChFi3d_FilletShape FShape = ChFi3d_Rational);
  
  Standard_EXPORT     void SetParams(const Standard_Real Tang,const Standard_Real Tesp,const Standard_Real T2d,const Standard_Real TApp3d,const Standard_Real TolApp2d,const Standard_Real Fleche) ;
  //! Changes     the      parameters     of  continiuity <br>
//!          InternalContinuity to produce fillet'surfaces with <br>
//!          an continuity   Ci (i=0,1 or    2). <br>
//!          By defaultInternalContinuity = GeomAbs_C1. <br>
//!          AngularTolerance  is the G1 tolerance between fillet <br>
//!          and support'faces. <br>
  Standard_EXPORT     void SetContinuity(const GeomAbs_Shape InternalContinuity,const Standard_Real AngularTolerance) ;
  //! Adds a  fillet contour in  the  builder  (builds a <br>
//!          contour  of tangent edges). <br>
//!          The Radius must be set after. <br>
//! <br>
  Standard_EXPORT     void Add(const TopoDS_Edge& E) ;
  //! Adds a  fillet description in  the  builder <br>
//!          - builds a contour  of tangent edges, <br>
//!          - sets the radius. <br>
//! <br>
  Standard_EXPORT     void Add(const Standard_Real Radius,const TopoDS_Edge& E) ;
  //! Adds a  fillet description in  the  builder <br>
//!          - builds a contour  of tangent edges, <br>
//!          - sets a linear radius evolution law between <br>
//!            the first and last vertex of the spine. <br>
//! <br>
  Standard_EXPORT     void Add(const Standard_Real R1,const Standard_Real R2,const TopoDS_Edge& E) ;
  //! Adds a  fillet description in  the  builder <br>
//!          - builds a contour  of tangent edges, <br>
//!          - sest the radius evolution law. <br>
//! <br>
  Standard_EXPORT     void Add(const Handle(Law_Function)& L,const TopoDS_Edge& E) ;
  //! Adds a  fillet description in  the  builder <br>
//!          - builds a contour  of tangent edges, <br>
//!          - sets the radius evolution law interpolating the values <br>
//!          given in the array UandR : <br>
//! <br>
//!          p2d.X() = relative parameter on the spine [0,1] <br>
//!          p2d.Y() = value of the radius. <br>
//! <br>
  Standard_EXPORT     void Add(const TColgp_Array1OfPnt2d& UandR,const TopoDS_Edge& E) ;
  //! Sets the parameters of the fillet <br>
//! along the contour of index IC generated using the Add function <br>
//! in the internal data structure of <br>
//! this algorithm, where Radius is the radius of the fillet. <br>
  Standard_EXPORT     void SetRadius(const Standard_Real Radius,const Standard_Integer IC,const Standard_Integer IinC) ;
  //! Sets the parameters of the fillet <br>
//! along the contour of index IC generated using the Add function <br>
//! in the internal data structure of this algorithm, where the radius of the <br>
//!   fillet evolves according to a linear evolution law defined <br>
//!   from R1 to R2, between the first and last vertices of the contour of index IC. <br>
  Standard_EXPORT     void SetRadius(const Standard_Real R1,const Standard_Real R2,const Standard_Integer IC,const Standard_Integer IinC) ;
  //! Sets the parameters of the fillet <br>
//! along the contour of index IC generated using the Add function <br>
//! in the internal data structure of this algorithm, where the radius of the <br>
//!   fillet evolves according to the evolution law L, between the <br>
//!   first and last vertices of the contour of index IC. <br>
  Standard_EXPORT     void SetRadius(const Handle(Law_Function)& L,const Standard_Integer IC,const Standard_Integer IinC) ;
  //! Sets the parameters of the fillet <br>
//! along the contour of index IC generated using the Add function <br>
//! in the internal data structure of this algorithm, <br>
//! where the radius of the fillet evolves according to the evolution law <br>
//! which interpolates the set of parameter and radius pairs given <br>
//! in the array UandR as follows: <br>
//! -   the X coordinate of a point in UandR defines a <br>
//!   relative parameter on the contour (i.e. a parameter between 0 and 1), <br>
//! -          the Y coordinate of a point in UandR gives the <br>
//!   corresponding value of the radius, and the radius evolves <br>
//!   between the first and last vertices of the contour of index IC. <br>
  Standard_EXPORT     void SetRadius(const TColgp_Array1OfPnt2d& UandR,const Standard_Integer IC,const Standard_Integer IinC) ;
  //! Erases the radius information on the contour of index <br>
//! IC in the internal data structure of this algorithm. <br>
//! Use the SetRadius function to reset this data. <br>
//! Warning <br>
//! Nothing is done if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     void ResetContour(const Standard_Integer IC) ;
  //! Returns true if the radius of the fillet along the contour of index IC <br>
//!   in the internal data structure of this algorithm is constant, <br>
//!   Warning <br>
//! False is returned if IC is outside the bounds of the table <br>
//! of contours or if E does not belong to the contour of index IC. <br>
  Standard_EXPORT     Standard_Boolean IsConstant(const Standard_Integer IC) ;
  //! Returns the radius of the fillet along the contour of index IC in the <br>
//!  internal data structure of this algorithm <br>
//!     Warning <br>
//! -   Use this function only if the radius is constant. <br>
//! -   -1. is returned if IC is outside the bounds of the <br>
//!   table of contours or if E does not belong to the contour of index IC. <br>
  Standard_EXPORT     Standard_Real Radius(const Standard_Integer IC) ;
  //! Returns true if the radius of the fillet along the edge E of the <br>
//!  contour of index IC in the internal data structure of <br>
//!  this algorithm is constant. <br>
//!   Warning <br>
//! False is returned if IC is outside the bounds of the table <br>
//! of contours or if E does not belong to the contour of index IC. <br>
  Standard_EXPORT     Standard_Boolean IsConstant(const Standard_Integer IC,const TopoDS_Edge& E) ;
  //! Returns the radius of the fillet along the edge E of the contour of index <br>
//! IC in the internal data structure of this algorithm. <br>
//! Warning <br>
//! -   Use this function only if the radius is constant. <br>
//! -   -1 is returned if IC is outside the bounds of the <br>
//! table of contours or if E does not belong to the contour of index IC. <br>
  Standard_EXPORT     Standard_Real Radius(const Standard_Integer IC,const TopoDS_Edge& E) ;
  //! Assigns Radius as the radius of the fillet on the edge E <br>
  Standard_EXPORT     void SetRadius(const Standard_Real Radius,const Standard_Integer IC,const TopoDS_Edge& E) ;
  
  Standard_EXPORT     void SetRadius(const Standard_Real Radius,const Standard_Integer IC,const TopoDS_Vertex& V) ;
  
  Standard_EXPORT     Standard_Boolean GetBounds(const Standard_Integer IC,const TopoDS_Edge& E,Standard_Real& F,Standard_Real& L) ;
  
  Standard_EXPORT     Handle_Law_Function GetLaw(const Standard_Integer IC,const TopoDS_Edge& E) ;
  
  Standard_EXPORT     void SetLaw(const Standard_Integer IC,const TopoDS_Edge& E,const Handle(Law_Function)& L) ;
  //! Assigns FShape as the type of fillet shape built by this algorithm. <br>
  Standard_EXPORT     void SetFilletShape(const ChFi3d_FilletShape FShape) ;
  //! Returns the type of fillet shape built by this algorithm. <br>
  Standard_EXPORT     ChFi3d_FilletShape GetFilletShape() const;
  //! Returns the number of contours generated using the <br>
//! Add function in the internal data structure of this algorithm. <br>
  Standard_EXPORT     Standard_Integer NbContours() const;
  //! Returns the index of the contour in the internal data <br>
//! structure of this algorithm which contains the edge E of the shape. <br>
//! This function returns 0 if the edge E does not belong to any contour. <br>
//! Warning <br>
//! This index can change if a contour is removed from the <br>
//! internal data structure of this algorithm using the function Remove. <br>
  Standard_EXPORT     Standard_Integer Contour(const TopoDS_Edge& E) const;
  //! Returns the number of edges in the contour of index I in <br>
//! the internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns 0 if I is outside the bounds of the table of contours. <br>
  Standard_EXPORT     Standard_Integer NbEdges(const Standard_Integer I) const;
  //! Returns the edge of index J in the contour of index I in <br>
//! the internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns a null shape if: <br>
//! -   I is outside the bounds of the table of contours, or <br>
//! -   J is outside the bounds of the table of edges of the index I contour. <br>
  Standard_EXPORT    const TopoDS_Edge& Edge(const Standard_Integer I,const Standard_Integer J) const;
  //! Removes the contour in the internal data structure of <br>
//! this algorithm which contains the edge E of the shape. <br>
//! Warning <br>
//! Nothing is done if the edge E does not belong to the <br>
//! contour in the internal data structure of this algorithm. <br>
  Standard_EXPORT     void Remove(const TopoDS_Edge& E) ;
  //! Returns the length of the contour of index IC in the <br>
//! internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns -1. if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     Standard_Real Length(const Standard_Integer IC) const;
  //! Returns the first vertex of the contour of index IC <br>
//! in the internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns a null shape if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     TopoDS_Vertex FirstVertex(const Standard_Integer IC) const;
  //! Returns the  last vertex of the contour of index IC <br>
//! in the internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns a null shape if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     TopoDS_Vertex LastVertex(const Standard_Integer IC) const;
  //! Returns the curvilinear abscissa of the vertex V on the <br>
//! contour of index IC in the internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns -1. if: <br>
//! -   IC is outside the bounds of the table of contours, or <br>
//! -   V is not on the contour of index IC. <br>
  Standard_EXPORT     Standard_Real Abscissa(const Standard_Integer IC,const TopoDS_Vertex& V) const;
  //! Returns the relative curvilinear abscissa (i.e. between 0 <br>
//! and 1) of the vertex V on the contour of index IC in the <br>
//! internal data structure of this algorithm. <br>
//! Warning <br>
//! Returns -1. if: <br>
//! -   IC is outside the bounds of the table of contours, or <br>
//! -   V is not on the contour of index IC. <br>
  Standard_EXPORT     Standard_Real RelativeAbscissa(const Standard_Integer IC,const TopoDS_Vertex& V) const;
  //! Returns true if the contour of index IC in the internal <br>
//! data structure of this algorithm is closed and tangential <br>
//! at the point of closure. <br>
//! Warning <br>
//! Returns false if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     Standard_Boolean ClosedAndTangent(const Standard_Integer IC) const;
  //! Returns true if the contour of index IC in the internal <br>
//! data structure of this algorithm is closed. <br>
//! Warning <br>
//! Returns false if IC is outside the bounds of the table of contours. <br>
  Standard_EXPORT     Standard_Boolean Closed(const Standard_Integer IC) const;
  //! Builds the fillets on all the contours in the internal data <br>
//! structure of this algorithm and constructs the resulting shape. <br>
//! Use the function IsDone to verify that the filleted shape <br>
//! is built. Use the function Shape to retrieve the filleted shape. <br>
//! Warning <br>
//! The construction of fillets implements highly complex <br>
//! construction algorithms. Consequently, there may be <br>
//! instances where the algorithm fails, for example if the <br>
//! data defining the radius of the fillet is not compatible <br>
//! with the geometry of the initial shape. There is no initial <br>
//! analysis of errors and they only become evident at the <br>
//! construction stage. <br>
//! Additionally, in the current software release, the <br>
//! following cases are not handled: <br>
//! -   the end point of the contour is the point of <br>
//!   intersection of 4 or more edges of the shape, or <br>
//! -   the intersection of the fillet with a face which limits <br>
//!   the contour is not fully contained in this face. <br>
  Standard_EXPORT   virtual  void Build() ;
  //! Reinitializes this algorithm, thus canceling the effects of the Build function. <br>
//! This function allows modifications to be made to the <br>
//! contours and fillet parameters in order to rebuild the shape. <br>
  Standard_EXPORT     void Reset() ;
  //! Returns the internal topology building algorithm. <br>
  Standard_EXPORT     Handle_TopOpeBRepBuild_HBuilder Builder() const;
  //! Returns the  list   of shapes generated   from the <br>
//!          shape <EorV>. <br>
  Standard_EXPORT   virtual const TopTools_ListOfShape& Generated(const TopoDS_Shape& EorV) ;
  //! Returns the list  of shapes modified from the shape <br>
//!          <F>. <br>
  Standard_EXPORT   virtual const TopTools_ListOfShape& Modified(const TopoDS_Shape& F) ;
  
  Standard_EXPORT   virtual  Standard_Boolean IsDeleted(const TopoDS_Shape& F) ;
  //! returns the number of surfaces <br>
//!          after the shape creation. <br>
  Standard_EXPORT     Standard_Integer NbSurfaces() const;
  //! Return the faces created for surface <I>. <br>
  Standard_EXPORT    const TopTools_ListOfShape& NewFaces(const Standard_Integer I) ;
  
  Standard_EXPORT     void Simulate(const Standard_Integer IC) ;
  
  Standard_EXPORT     Standard_Integer NbSurf(const Standard_Integer IC) const;
  
  Standard_EXPORT     Handle_ChFiDS_SecHArray1 Sect(const Standard_Integer IC,const Standard_Integer IS) const;
  //! Returns the number of contours where the computation <br>
//! of the fillet failed <br>
  Standard_EXPORT     Standard_Integer NbFaultyContours() const;
  //! for each I in [1.. NbFaultyContours] returns the index IC of <br>
//! the contour where the computation of the fillet failed. <br>
//! the method NbEdges(IC) gives the number of edges in the contour IC <br>
//! the method Edge(IC,ie) gives the edge number ie of the contour IC <br>
  Standard_EXPORT     Standard_Integer FaultyContour(const Standard_Integer I) const;
  //! returns the number of surfaces which have been <br>
//!          computed on the contour IC <br>
  Standard_EXPORT     Standard_Integer NbComputedSurfaces(const Standard_Integer IC) const;
  //! returns the surface number IS concerning the contour IC <br>
  Standard_EXPORT     Handle_Geom_Surface ComputedSurface(const Standard_Integer IC,const Standard_Integer IS) const;
  //! returns the number of vertices where the computation failed <br>
  Standard_EXPORT     Standard_Integer NbFaultyVertices() const;
  //! returns the vertex where the computation failed <br>
  Standard_EXPORT     TopoDS_Vertex FaultyVertex(const Standard_Integer IV) const;
  //! returns true if a part of the result has been computed <br>
//! if the filling in a corner failed a shape with a hole is returned <br>
  Standard_EXPORT     Standard_Boolean HasResult() const;
  //! if (HasResult()) returns the partial result <br>
  Standard_EXPORT     TopoDS_Shape BadShape() const;
  //! returns the status concerning the contour IC in case of error <br>
//! ChFiDS_Ok : the computation is Ok <br>
//! ChFiDS_StartsolFailure : the computation can't start, perhaps the <br>
//!                          the radius is too big <br>
//! ChFiDS_TwistedSurface : the computation failed because of a twisted <br>
//!                         surface <br>
//! ChFiDS_WalkingFailure : there is a problem in the walking <br>
//! ChFiDS_Error:  other error different from above <br>
  Standard_EXPORT     ChFiDS_ErrorStatus StripeStatus(const Standard_Integer IC) const;





protected:





private:



ChFi3d_FilBuilder myBuilder;
TopTools_MapOfShape myMap;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif