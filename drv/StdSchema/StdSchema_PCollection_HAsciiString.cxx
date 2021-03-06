#ifndef _StdSchema_PCollection_HAsciiString_HeaderFile
#include <StdSchema_PCollection_HAsciiString.hxx>
#endif
#ifndef _PCollection_HAsciiString_HeaderFile
#include <PCollection_HAsciiString.hxx>
#endif
#include <StdSchema_PCollection_HAsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PCollection_HAsciiString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PCollection_HAsciiString,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PCollection_HAsciiString::New() const
{
  return new PCollection_HAsciiString(Storage_stCONSTclCOM());
}

void StdSchema_PCollection_HAsciiString::SAdd(const Handle(PCollection_HAsciiString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCollection_HAsciiString")) {
      
    }
  }
}

void StdSchema_PCollection_HAsciiString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PCollection_HAsciiString::SAdd((Handle(PCollection_HAsciiString)&)p,theSchema);
}

void StdSchema_PCollection_HAsciiString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    StdSchema_DBC_VArrayOfCharacter::SWrite(pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PCollection_HAsciiString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PCollection_HAsciiString::SWrite(p,f,theSchema);
}


void StdSchema_PCollection_HAsciiString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdSchema_DBC_VArrayOfCharacter::SRead((DBC_VArrayOfCharacter&)pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PCollection_HAsciiString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PCollection_HAsciiString::SRead(p,f,theSchema);
}
