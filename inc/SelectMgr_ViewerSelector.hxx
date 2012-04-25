// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _SelectMgr_ViewerSelector_HeaderFile
#define _SelectMgr_ViewerSelector_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_SelectMgr_ViewerSelector_HeaderFile
#include <Handle_SelectMgr_ViewerSelector.hxx>
#endif

#ifndef _SelectMgr_DataMapOfIntegerSensitive_HeaderFile
#include <SelectMgr_DataMapOfIntegerSensitive.hxx>
#endif
#ifndef _SelectMgr_DataMapOfSelectionActivation_HeaderFile
#include <SelectMgr_DataMapOfSelectionActivation.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _SelectBasics_SortAlgo_HeaderFile
#include <SelectBasics_SortAlgo.hxx>
#endif
#ifndef _Bnd_Box2d_HeaderFile
#include <Bnd_Box2d.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _SelectMgr_IndexedDataMapOfOwnerCriterion_HeaderFile
#include <SelectMgr_IndexedDataMapOfOwnerCriterion.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfInteger_HeaderFile
#include <Handle_TColStd_HArray1OfInteger.hxx>
#endif
#ifndef _TColStd_SequenceOfInteger_HeaderFile
#include <TColStd_SequenceOfInteger.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Handle_SelectMgr_Selection_HeaderFile
#include <Handle_SelectMgr_Selection.hxx>
#endif
#ifndef _Handle_SelectMgr_SelectableObject_HeaderFile
#include <Handle_SelectMgr_SelectableObject.hxx>
#endif
#ifndef _Handle_SelectMgr_EntityOwner_HeaderFile
#include <Handle_SelectMgr_EntityOwner.hxx>
#endif
#ifndef _SelectMgr_StateOfSelection_HeaderFile
#include <SelectMgr_StateOfSelection.hxx>
#endif
#ifndef _Standard_OStream_HeaderFile
#include <Standard_OStream.hxx>
#endif
#ifndef _Handle_SelectBasics_SensitiveEntity_HeaderFile
#include <Handle_SelectBasics_SensitiveEntity.hxx>
#endif
class TColStd_HArray1OfInteger;
class SelectMgr_SelectionManager;
class SelectMgr_Selection;
class SelectMgr_SelectableObject;
class Bnd_Box2d;
class TColgp_Array1OfPnt2d;
class SelectMgr_EntityOwner;
class TColStd_ListOfInteger;
class TCollection_AsciiString;
class SelectBasics_SensitiveEntity;
class SelectMgr_DataMapOfIntegerSensitive;


//! A framework to define finding, sorting the sensitive <br>
//! primitives in a view. Services are also provided to <br>
//! define the return of the owners of those primitives <br>
//! selected. The primitives are sorted by criteria such <br>
//! as priority of the primitive or its depth in the view <br>
//! relative to that of other primitives. <br>
//! This framework is undefined for either 2D or 3D, <br>
//! and is consequently used by both <br>
//! StdSelect_ViewerSelector2d and <br>
//! StdSelect_ViewerSelector3d, which inherit it, and <br>
//! which in turn, return 2D and 3D owners of sensitive <br>
//! primitives respectively. <br>
//! Note that in 3D, the inheriting framework <br>
//! StdSelect_ViewerSelector3d   is only to be used <br>
//! if you do not want to use the services provided by <br>
//! AIS. In 2D, you will, however, need the services <br>
//! provided by the StdSelect_ViewerSelector2d. <br>
//! Two tools are available to find and select objects <br>
//! found at a given position in the view. If you want to <br>
//! select the owners of all the objects detected at <br>
//! point x,y, you use the Init - More - Next - Picked <br>
//! loop. If, on the other hand, you want to select only <br>
//! one object detected at that point, you use the Init - <br>
//! More - OnePicked loop. In this iteration, More is <br>
//! used to see if an object was picked and <br>
//! OnePicked, to get the object closest to the pick position. <br>
//! Viewer selectors are driven by <br>
//! SelectMgr_SelectionManager, and manipulate <br>
//! the SelectMgr_Selection objects given to them by <br>
//! the selection manager. <br>
class SelectMgr_ViewerSelector : public MMgt_TShared {

public:

  //! to be redefined if conversion is necessary for SensitiveEntities... <br>
  Standard_EXPORT   virtual  void Convert(const Handle(SelectMgr_Selection)& aSelection) ;
  //! Empties all the tables, removes all selections... <br>
  Standard_EXPORT     void Clear() ;
  //! converts all the sensitive entities ; <br>
  Standard_EXPORT     void UpdateConversion() ;
  //! changes the Sensitivity of picking <br>
//!          Input value is Real. <br>
  Standard_EXPORT     void SetSensitivity(const Standard_Real aTol) ;
  //! returns the Sensitivity of picking <br>
        Standard_Real Sensitivity() const;
  //! sets the clipping limits of dynamic picking <br>
//!          input value are Real <br>
  Standard_EXPORT     void SetClipping(const Standard_Real Xc,const Standard_Real Yc,const Standard_Real Height,const Standard_Real Width) ;
  //! sets the clipping limits of dynamic picking <br>
//!          input value are Real <br>
  Standard_EXPORT     void SetClipping(const Bnd_Box2d& aRectangle) ;
  //! Performs a pick action. Xr, Yr   are the real 2D mouse <br>
//! coordinates in the view. The selector looks for areas <br>
//! and owners that are touched. <br>
  Standard_EXPORT     void InitSelect(const Standard_Real Xr,const Standard_Real Yr) ;
  //! Performs a pick action. aRect is a Box2d (real <br>
//! coordinates) for the selection. The selector looks for <br>
//! areas and owners that are touched. <br>
  Standard_EXPORT     void InitSelect(const Bnd_Box2d& aRect) ;
  //! Performs a pick action <br>
//! -   Xmin, Ymin define the coordinates of the minimum <br>
//!   point in the lower left hand corner of the selection <br>
//!   box, and XMax, YMax define the coordinates of <br>
//!   the maximum point in the upper right hand corner <br>
//!   of the selection box. The selector looks for areas <br>
//!   and owners that are touched. <br>
  Standard_EXPORT     void InitSelect(const Standard_Real Xmin,const Standard_Real Ymin,const Standard_Real Xmax,const Standard_Real Ymax) ;
  //! pick action  - input  values of a polyline selection for selection. <br>
  Standard_EXPORT     void InitSelect(const TColgp_Array1OfPnt2d& Polyline) ;
  //! Sorts the detected entites by priority and distance. <br>
//!          to be redefined if other criterion are used... <br>
  Standard_EXPORT   virtual  void SortResult() ;
  //! Begins an iteration scanning for the owners detected at a position in the view. <br>
        void Init() ;
  //!  Continues the interation scanning for the owners <br>
//!   detected at a position in the view, or <br>
//! -   continues the iteration scanning for the owner <br>
//!   closest to the position in the view. <br>
  Standard_EXPORT     Standard_Boolean More() ;
  //! Returns the next owner found in the iteration. This is <br>
//! a scan for the owners detected at a position in the view. <br>
        void Next() ;
  //! Returns the current selected entity detected by the selector; <br>
  Standard_EXPORT     Handle_SelectMgr_EntityOwner Picked() const;
  //! Returns the picked element with the highest priority, <br>
//! and which is the closest to the last successful mouse position. <br>
  Standard_EXPORT     Handle_SelectMgr_EntityOwner OnePicked() ;
  //! Set preference of selecting one object for OnePicked() method: <br>
//! - If True, objects with less depth (distance fron the view plane) are <br>
//!   preferred regardless of priority (priority is used then to choose among <br>
//!   objects with similar depth), <br>
//! - If False, objects with higher priority are preferred regardless of the <br>
//!   depth which is used to choose among objects of the same priority. <br>
        void SetPickClosest(const Standard_Boolean preferClosest) ;
  //! Returns the number of owners found at a position in <br>
//! the view by the Init - More - Next - Picked iteration. <br>
  Standard_EXPORT     Standard_Integer NbPicked() const;
  //! Returns the  entity which is at rank <aRank> <br>
//!          in the list of stored ones. <br>
  Standard_EXPORT     Handle_SelectMgr_EntityOwner Picked(const Standard_Integer aRank) const;
  //! Returns True if a successful pick was stored, <br>
//!          i.e. LastPosition method means something... <br>
  Standard_EXPORT     Standard_Boolean HasStored() ;
  //! Gives the last successful pick position; <br>
//!          is useful to get objects really picked <br>
  Standard_EXPORT     void LastPosition(Standard_Real& Xr,Standard_Real& Yr) const;
  
  Standard_EXPORT     Standard_Boolean Contains(const Handle(SelectMgr_SelectableObject)& aSelectableObject) const;
  //! Returns the list of selection modes ModeList found in <br>
//! this selector for the selectable object aSelectableObject. <br>
//! Returns true if aSelectableObject is referenced inside <br>
//! this selector; returns false if the object is not present <br>
//! in this selector. <br>
  Standard_EXPORT     Standard_Boolean Modes(const Handle(SelectMgr_SelectableObject)& aSelectableObject,TColStd_ListOfInteger& ModeList,const SelectMgr_StateOfSelection WantedState = SelectMgr_SOS_Any) const;
  //! Returns true if the selectable object <br>
//! aSelectableObject having the selection mode aMode <br>
//! is active in this selector. <br>
  Standard_EXPORT     Standard_Boolean IsActive(const Handle(SelectMgr_SelectableObject)& aSelectableObject,const Standard_Integer aMode) const;
  //! Returns true if the selectable object <br>
//! aSelectableObject having the selection mode aMode <br>
//! is in this selector. <br>
  Standard_EXPORT     Standard_Boolean IsInside(const Handle(SelectMgr_SelectableObject)& aSelectableObject,const Standard_Integer aMode) const;
  //! Returns the selection status Status of the selection aSelection. <br>
  Standard_EXPORT     SelectMgr_StateOfSelection Status(const Handle(SelectMgr_Selection)& aSelection) const;
  
  Standard_EXPORT     void Dump(Standard_OStream& S) const;
  
  Standard_EXPORT     TCollection_AsciiString Status(const Handle(SelectMgr_SelectableObject)& aSelectableObject) const;
  //! gives general information about the Selector <br>
  Standard_EXPORT     TCollection_AsciiString Status() const;
  
  Standard_EXPORT     void UpdateSort() ;
  
  Standard_EXPORT     Handle_SelectBasics_SensitiveEntity Primitive(const Standard_Integer Rank) const;
  
       const SelectMgr_DataMapOfIntegerSensitive& Primitives() const;
  
  Standard_EXPORT     void SetUpdateSortPossible(const Standard_Boolean possible) ;
  
  Standard_EXPORT     Standard_Boolean IsUpdateSortPossible() const;


friend class SelectMgr_SelectionManager;


  DEFINE_STANDARD_RTTI(SelectMgr_ViewerSelector)

protected:

  
  Standard_EXPORT   SelectMgr_ViewerSelector();
  
  Standard_EXPORT   virtual  void LoadResult() ;
  
  Standard_EXPORT   virtual  void LoadResult(const Bnd_Box2d& aBox) ;
  
  Standard_EXPORT   virtual  void LoadResult(const TColgp_Array1OfPnt2d& Polyline) ;

SelectMgr_DataMapOfIntegerSensitive myentities;
SelectMgr_DataMapOfSelectionActivation myselections;
Standard_Boolean toupdate;
Standard_Boolean tosort;
Standard_Boolean preferclosest;
Standard_Real mytolerance;
SelectBasics_SortAlgo myselector;
Bnd_Box2d myclip;
SelectMgr_IndexedDataMapOfOwnerCriterion mystored;


private: 

  
  Standard_EXPORT     void Activate(const Handle(SelectMgr_Selection)& aSelection,const Standard_Boolean AutomaticProj = Standard_True) ;
  
  Standard_EXPORT     void Deactivate(const Handle(SelectMgr_Selection)& aSelection) ;
  //! Desactivates all the objects of the view; <br>
//!          no object in this view will be selectable; <br>
  Standard_EXPORT     void Sleep() ;
  //! reactivates all the selection which were sleeping.... <br>
  Standard_EXPORT     void Awake(const Standard_Boolean AutomaticProj = Standard_True) ;
  
  Standard_EXPORT     void Sleep(const Handle(SelectMgr_SelectableObject)& anObject) ;
  
  Standard_EXPORT     void Awake(const Handle(SelectMgr_SelectableObject)& anObject,const Standard_Boolean AutomaticProj = Standard_True) ;
  //! removes a Selection from the Selector <br>
  Standard_EXPORT     void Remove(const Handle(SelectMgr_Selection)& aSelection) ;
  
  Standard_EXPORT     Standard_Integer NbBoxes() ;

Standard_Integer myactivenb;
Handle_TColStd_HArray1OfInteger myIndexes;
TColStd_SequenceOfInteger myprim;
Standard_Integer myCurRank;
Standard_Real lastx;
Standard_Real lasty;
Standard_Boolean myUpdateSortPossible;


};


#include <SelectMgr_ViewerSelector.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
