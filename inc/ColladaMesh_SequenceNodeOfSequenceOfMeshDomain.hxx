// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ColladaMesh_SequenceNodeOfSequenceOfMeshDomain_HeaderFile
#define _ColladaMesh_SequenceNodeOfSequenceOfMeshDomain_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_ColladaMesh_SequenceNodeOfSequenceOfMeshDomain_HeaderFile
#include <Handle_ColladaMesh_SequenceNodeOfSequenceOfMeshDomain.hxx>
#endif

#ifndef _Handle_ColladaMesh_MeshDomain_HeaderFile
#include <Handle_ColladaMesh_MeshDomain.hxx>
#endif
#ifndef _TCollection_SeqNode_HeaderFile
#include <TCollection_SeqNode.hxx>
#endif
#ifndef _TCollection_SeqNodePtr_HeaderFile
#include <TCollection_SeqNodePtr.hxx>
#endif
class ColladaMesh_MeshDomain;
class ColladaMesh_SequenceOfMeshDomain;



class ColladaMesh_SequenceNodeOfSequenceOfMeshDomain : public TCollection_SeqNode {

public:

  
      ColladaMesh_SequenceNodeOfSequenceOfMeshDomain(const Handle(ColladaMesh_MeshDomain)& I,const TCollection_SeqNodePtr& n,const TCollection_SeqNodePtr& p);
  
        Handle_ColladaMesh_MeshDomain& Value() const;




  DEFINE_STANDARD_RTTI(ColladaMesh_SequenceNodeOfSequenceOfMeshDomain)

protected:




private: 


Handle_ColladaMesh_MeshDomain myValue;


};

#define SeqItem Handle_ColladaMesh_MeshDomain
#define SeqItem_hxx <ColladaMesh_MeshDomain.hxx>
#define TCollection_SequenceNode ColladaMesh_SequenceNodeOfSequenceOfMeshDomain
#define TCollection_SequenceNode_hxx <ColladaMesh_SequenceNodeOfSequenceOfMeshDomain.hxx>
#define Handle_TCollection_SequenceNode Handle_ColladaMesh_SequenceNodeOfSequenceOfMeshDomain
#define TCollection_SequenceNode_Type_() ColladaMesh_SequenceNodeOfSequenceOfMeshDomain_Type_()
#define TCollection_Sequence ColladaMesh_SequenceOfMeshDomain
#define TCollection_Sequence_hxx <ColladaMesh_SequenceOfMeshDomain.hxx>

#include <TCollection_SequenceNode.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
