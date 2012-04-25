// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _QANewBRepNaming_Gluing_HeaderFile
#define _QANewBRepNaming_Gluing_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopTools_IndexedDataMapOfShapeListOfShape_HeaderFile
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#endif
#ifndef _TopoDS_Shape_HeaderFile
#include <TopoDS_Shape.hxx>
#endif
#ifndef _TDF_LabelMap_HeaderFile
#include <TDF_LabelMap.hxx>
#endif
#ifndef _QANewBRepNaming_TopNaming_HeaderFile
#include <QANewBRepNaming_TopNaming.hxx>
#endif
#ifndef _TopAbs_ShapeEnum_HeaderFile
#include <TopAbs_ShapeEnum.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NullObject;
class TDF_Label;
class QANewModTopOpe_Glue;
class TopoDS_Shape;
class TDF_LabelMap;
class TopTools_DataMapOfShapeInteger;


//! Loads a result of Gluing operation in  Data Framework <br>
class QANewBRepNaming_Gluing  : public QANewBRepNaming_TopNaming {
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

  
  Standard_EXPORT   QANewBRepNaming_Gluing();
  
  Standard_EXPORT   QANewBRepNaming_Gluing(const TDF_Label& theResultLabel);
  
  Standard_EXPORT     void Init(const TDF_Label& theResultLabel) ;
  //! Loads a Gluing in a data framework <br>
  Standard_EXPORT     void Load(QANewModTopOpe_Glue& theMkGluing) ;
  
  Standard_EXPORT     TDF_Label Content() const;
  
  Standard_EXPORT     void SetContext(const TopoDS_Shape& theObject,const TopoDS_Shape& theTool) ;
  
  Standard_EXPORT     void SetLog(const TDF_LabelMap& theLog) ;





protected:





private:

  //! If the shape is a compound the method <br>
//!          returns the underlying shape type. <br>
  Standard_EXPORT     TopAbs_ShapeEnum ShapeType(const TopoDS_Shape& theShape) const;
  //! If the shape is a compound the method <br>
//!          returns the underlying shape. <br>
  Standard_EXPORT     TopoDS_Shape GetShape(const TopoDS_Shape& theShape) const;
  //! A default implementation for naming of modified shapes of the operation <br>
  Standard_EXPORT     void LoadModifiedShapes(QANewModTopOpe_Glue& theMakeShape) const;
  //! A default implementation for naming of modified shapes of the operation <br>
  Standard_EXPORT     void LoadDeletedShapes(QANewModTopOpe_Glue& theMakeShape) const;
  //! Loads the content of the result. <br>
  Standard_EXPORT     void LoadContent(QANewModTopOpe_Glue& theMakeShape) const;
  //! Loads the result. <br>
  Standard_EXPORT     void LoadResult(QANewModTopOpe_Glue& theMakeShape) const;
  //! Returns true if the result is not the same as the object shape. <br>
  Standard_EXPORT     Standard_Boolean IsResultChanged(QANewModTopOpe_Glue& theMakeShape) const;
  //! Loads the deletion of the degenerated edges. <br>
  Standard_EXPORT     void LoadSectionEdges(QANewModTopOpe_Glue& theMakeShape) const;
  
  Standard_EXPORT     void AddToTheUnique(const TopoDS_Shape& theUnique,const TopoDS_Shape& theIdentifier) ;
  //! Reset myShared map - shapes, which are modified by both object and tool. <br>
  Standard_EXPORT     void RecomputeUnique(QANewModTopOpe_Glue& theMakeShape) ;
  
  Standard_EXPORT     void LoadSourceShapes(TopTools_DataMapOfShapeInteger& theSources) const;
  //! A default implementation for naming of generated  shapes of the operation <br>
  Standard_EXPORT     void LoadUniqueShapes(QANewModTopOpe_Glue& theMakeShape,const TopTools_DataMapOfShapeInteger& theSources) ;


TopTools_IndexedDataMapOfShapeListOfShape myUnique;
TopoDS_Shape myContext;
TDF_LabelMap myLog;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
