// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TopoDSToStep_MakeShellBasedSurfaceModel_HeaderFile
#define _TopoDSToStep_MakeShellBasedSurfaceModel_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_StepShape_ShellBasedSurfaceModel.hxx>
#include <TopoDSToStep_Root.hxx>
#include <Handle_Transfer_FinderProcess.hxx>
class StepShape_ShellBasedSurfaceModel;
class StdFail_NotDone;
class TopoDS_Face;
class Transfer_FinderProcess;
class TopoDS_Shell;
class TopoDS_Solid;


//! This class implements the mapping between classes
//! Face, Shell or Solid from TopoDS and ShellBasedSurfaceModel
//! from StepShape. All the topology and geometry comprised
//! into the shape are taken into account and translated.
class TopoDSToStep_MakeShellBasedSurfaceModel  : public TopoDSToStep_Root
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT TopoDSToStep_MakeShellBasedSurfaceModel(const TopoDS_Face& F, const Handle(Transfer_FinderProcess)& FP);
  
  Standard_EXPORT TopoDSToStep_MakeShellBasedSurfaceModel(const TopoDS_Shell& S, const Handle(Transfer_FinderProcess)& FP);
  
  Standard_EXPORT TopoDSToStep_MakeShellBasedSurfaceModel(const TopoDS_Solid& S, const Handle(Transfer_FinderProcess)& FP);
  
  Standard_EXPORT  const  Handle(StepShape_ShellBasedSurfaceModel)& Value()  const;




protected:





private:



  Handle(StepShape_ShellBasedSurfaceModel) theShellBasedSurfaceModel;


};







#endif // _TopoDSToStep_MakeShellBasedSurfaceModel_HeaderFile
