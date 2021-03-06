// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _OSD_Error_HeaderFile
#define _OSD_Error_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_AsciiString.hxx>
#include <Standard_Integer.hxx>
#include <OSD_WhoAmI.hxx>
#include <Standard_Boolean.hxx>
class OSD_OSDError;
class TCollection_AsciiString;


//! Accurate management of OSD specific errors.
class OSD_Error 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Initializes Error to be without any Error.
  //! This is only used by OSD, not by programmer.
  Standard_EXPORT OSD_Error();
  
  //! Raises OSD_Error with accurate error message.
  Standard_EXPORT   void Perror() ;
  
  //! Instantiates error
  //! This is only used by OSD methods to instantiates an error code.
  //! No description is done for the programmer.
  Standard_EXPORT   void SetValue (const Standard_Integer Errcode, const Standard_Integer From, const TCollection_AsciiString& Message) ;
  
  //! Returns an accurate error code.
  //! To test these values, you must include "OSD_ErrorList.hxx"
  Standard_EXPORT   Standard_Integer Error()  const;
  
  //! Returns TRUE if an error occurs
  //! This is a way to test if a system call succeeded or not.
  Standard_EXPORT   Standard_Boolean Failed()  const;
  
  //! Resets error counter to zero
  //! This allows the user to ignore an error (WARNING).
  Standard_EXPORT   void Reset() ;




protected:





private:



  TCollection_AsciiString myMessage;
  Standard_Integer myErrno;
  OSD_WhoAmI myCode;
  Standard_Integer extCode;


};







#endif // _OSD_Error_HeaderFile
