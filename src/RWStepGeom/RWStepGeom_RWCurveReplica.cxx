// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.


#include <RWStepGeom_RWCurveReplica.ixx>
#include <StepGeom_Curve.hxx>
#include <StepGeom_CartesianTransformationOperator.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepGeom_CurveReplica.hxx>


RWStepGeom_RWCurveReplica::RWStepGeom_RWCurveReplica () {}

void RWStepGeom_RWCurveReplica::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepGeom_CurveReplica)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,3,ach,"curve_replica")) return;

	// --- inherited field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	// --- own field : parentCurve ---

	Handle(StepGeom_Curve) aParentCurve;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	data->ReadEntity(num, 2,"parent_curve", ach, STANDARD_TYPE(StepGeom_Curve), aParentCurve);

	// --- own field : transformation ---

	Handle(StepGeom_CartesianTransformationOperator) aTransformation;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat3 =` not needed
	data->ReadEntity(num, 3,"transformation", ach, STANDARD_TYPE(StepGeom_CartesianTransformationOperator), aTransformation);

	//--- Initialisation of the read entity ---


	ent->Init(aName, aParentCurve, aTransformation);
}


void RWStepGeom_RWCurveReplica::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepGeom_CurveReplica)& ent) const
{

	// --- inherited field name ---

	SW.Send(ent->Name());

	// --- own field : parentCurve ---

	SW.Send(ent->ParentCurve());

	// --- own field : transformation ---

	SW.Send(ent->Transformation());
}


void RWStepGeom_RWCurveReplica::Share(const Handle(StepGeom_CurveReplica)& ent, Interface_EntityIterator& iter) const
{

	iter.GetOneItem(ent->ParentCurve());


	iter.GetOneItem(ent->Transformation());
}

