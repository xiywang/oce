// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESBasic_HArray1OfHArray1OfXY_HeaderFile
#define _IGESBasic_HArray1OfHArray1OfXY_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_IGESBasic_HArray1OfHArray1OfXY.hxx>

#include <TColStd_Array1OfTransient.hxx>
#include <MMgt_TShared.hxx>
#include <Handle_TColgp_HArray1OfXY.hxx>
#include <Standard_Integer.hxx>
class TColgp_HArray1OfXY;



class IGESBasic_HArray1OfHArray1OfXY : public MMgt_TShared
{

public:

  
  Standard_EXPORT IGESBasic_HArray1OfHArray1OfXY(const Standard_Integer low, const Standard_Integer up);
  
  Standard_EXPORT   Standard_Integer Lower()  const;
  
  Standard_EXPORT   Standard_Integer Upper()  const;
  
  Standard_EXPORT   Standard_Integer Length()  const;
  
  Standard_EXPORT   void SetValue (const Standard_Integer num, const Handle(TColgp_HArray1OfXY)& val) ;
  
  Standard_EXPORT   Handle(TColgp_HArray1OfXY) Value (const Standard_Integer num)  const;




  DEFINE_STANDARD_RTTI(IGESBasic_HArray1OfHArray1OfXY)

protected:




private: 


  TColStd_Array1OfTransient thelist;


};







#endif // _IGESBasic_HArray1OfHArray1OfXY_HeaderFile
