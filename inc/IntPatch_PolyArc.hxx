// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntPatch_PolyArc_HeaderFile
#define _IntPatch_PolyArc_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TColgp_Array1OfPnt2d_HeaderFile
#include <TColgp_Array1OfPnt2d.hxx>
#endif
#ifndef _TColStd_Array1OfReal_HeaderFile
#include <TColStd_Array1OfReal.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _IntPatch_Polygo_HeaderFile
#include <IntPatch_Polygo.hxx>
#endif
#ifndef _Handle_Adaptor2d_HCurve2d_HeaderFile
#include <Handle_Adaptor2d_HCurve2d.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_ConstructionError;
class Adaptor2d_HCurve2d;
class Bnd_Box2d;
class gp_Pnt2d;



class IntPatch_PolyArc  : public IntPatch_Polygo {
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

  //! Creates the polygon of the arc A on the surface S. <br>
//!          The arc is limited by the parameters Pfirst and Plast. <br>
//!          None of these parameters can be infinite. <br>
  Standard_EXPORT   IntPatch_PolyArc(const Handle(Adaptor2d_HCurve2d)& A,const Standard_Integer NbSample,const Standard_Real Pfirst,const Standard_Real Plast,const Bnd_Box2d& BoxOtherPolygon);
  
  Standard_EXPORT   virtual  Standard_Boolean Closed() const;
  
  Standard_EXPORT     Standard_Integer NbPoints() const;
  
  Standard_EXPORT     gp_Pnt2d Point(const Standard_Integer Index) const;
  
  Standard_EXPORT     Standard_Real Parameter(const Standard_Integer Index) const;
  
  Standard_EXPORT     void SetOffset(const Standard_Real OffsetX,const Standard_Real OffsetY) ;





protected:





private:



TColgp_Array1OfPnt2d brise;
TColStd_Array1OfReal param;
Standard_Real offsetx;
Standard_Real offsety;
Standard_Boolean ferme;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
