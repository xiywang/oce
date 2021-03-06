// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColgp_Array1OfDir2d_HeaderFile
#define _TColgp_Array1OfDir2d_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_Integer.hxx>
#include <Standard_Address.hxx>
#include <Standard_Boolean.hxx>
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class gp_Dir2d;



class TColgp_Array1OfDir2d 
{
public:

  DEFINE_STANDARD_ALLOC

  
    TColgp_Array1OfDir2d(const Standard_Integer Low, const Standard_Integer Up);
  
    TColgp_Array1OfDir2d(const gp_Dir2d& Item, const Standard_Integer Low, const Standard_Integer Up);
  
  Standard_EXPORT   void Init (const gp_Dir2d& V) ;
  
      void Destroy() ;
~TColgp_Array1OfDir2d()
{
  Destroy();
}
  
      Standard_Boolean IsAllocated()  const;
  
  Standard_EXPORT  const  TColgp_Array1OfDir2d& Assign (const TColgp_Array1OfDir2d& Other) ;
 const  TColgp_Array1OfDir2d& operator = (const TColgp_Array1OfDir2d& Other) 
{
  return Assign(Other);
}
  
      Standard_Integer Length()  const;
  
      Standard_Integer Lower()  const;
  
      Standard_Integer Upper()  const;
  
      void SetValue (const Standard_Integer Index, const gp_Dir2d& Value) ;
  
     const  gp_Dir2d& Value (const Standard_Integer Index)  const;
   const  gp_Dir2d& operator () (const Standard_Integer Index)  const
{
  return Value(Index);
}
  
      gp_Dir2d& ChangeValue (const Standard_Integer Index) ;
    gp_Dir2d& operator () (const Standard_Integer Index) 
{
  return ChangeValue(Index);
}




protected:





private:

  
  Standard_EXPORT TColgp_Array1OfDir2d(const TColgp_Array1OfDir2d& AnArray);


  Standard_Integer myLowerBound;
  Standard_Integer myUpperBound;
  Standard_Address myStart;
  Standard_Boolean isAllocated;


};

#define Array1Item gp_Dir2d
#define Array1Item_hxx <gp_Dir2d.hxx>
#define TCollection_Array1 TColgp_Array1OfDir2d
#define TCollection_Array1_hxx <TColgp_Array1OfDir2d.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx




#endif // _TColgp_Array1OfDir2d_HeaderFile
