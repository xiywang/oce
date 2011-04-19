// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _PGeom_Axis1Placement_HeaderFile
#define _PGeom_Axis1Placement_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_PGeom_Axis1Placement_HeaderFile
#include <Handle_PGeom_Axis1Placement.hxx>
#endif

#ifndef _PGeom_AxisPlacement_HeaderFile
#include <PGeom_AxisPlacement.hxx>
#endif
class gp_Ax1;


class PGeom_Axis1Placement : public PGeom_AxisPlacement {

public:

  //! Creates an Axis1Placement with Ax1 default value. <br>
  Standard_EXPORT   PGeom_Axis1Placement();
  //! Creates an Axis1Placement with <aAxis>. <br>
  Standard_EXPORT   PGeom_Axis1Placement(const gp_Ax1& aAxis);

PGeom_Axis1Placement(const Storage_stCONSTclCOM& a) : PGeom_AxisPlacement(a)
{
  
}



  DEFINE_STANDARD_RTTI(PGeom_Axis1Placement)

protected:




private: 




};





// other Inline functions and methods (like "C++: function call" methods)


#endif