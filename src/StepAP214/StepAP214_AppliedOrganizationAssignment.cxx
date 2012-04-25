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

#include <StepAP214_AppliedOrganizationAssignment.ixx>


StepAP214_AppliedOrganizationAssignment::StepAP214_AppliedOrganizationAssignment ()  {}

void StepAP214_AppliedOrganizationAssignment::Init(
	const Handle(StepBasic_Organization)& aAssignedOrganization,
	const Handle(StepBasic_OrganizationRole)& aRole)
{

	StepBasic_OrganizationAssignment::Init(aAssignedOrganization, aRole);
}

void StepAP214_AppliedOrganizationAssignment::Init(
	const Handle(StepBasic_Organization)& aAssignedOrganization,
	const Handle(StepBasic_OrganizationRole)& aRole,
	const Handle(StepAP214_HArray1OfOrganizationItem)& aItems)
{
	// --- classe own fields ---
	items = aItems;
	// --- classe inherited fields ---
	StepBasic_OrganizationAssignment::Init(aAssignedOrganization, aRole);
}


void StepAP214_AppliedOrganizationAssignment::SetItems(const Handle(StepAP214_HArray1OfOrganizationItem)& aItems)
{
	items = aItems;
}

Handle(StepAP214_HArray1OfOrganizationItem) StepAP214_AppliedOrganizationAssignment::Items() const
{
	return items;
}

StepAP214_OrganizationItem StepAP214_AppliedOrganizationAssignment::ItemsValue(const Standard_Integer num) const
{
	return items->Value(num);
}

Standard_Integer StepAP214_AppliedOrganizationAssignment::NbItems () const
{
	return items->Length();
}
