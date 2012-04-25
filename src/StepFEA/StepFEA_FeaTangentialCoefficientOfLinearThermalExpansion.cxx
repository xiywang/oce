// Created on: 2002-12-12
// Created by: data exchange team
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.2

#include <StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.ixx>

//=======================================================================
//function : StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion
//purpose  : 
//=======================================================================

StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion ()
{
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::Init (const Handle(TCollection_HAsciiString) &aRepresentationItem_Name,
                                                                     const StepFEA_SymmetricTensor23d &aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=======================================================================
//function : FeaConstants
//purpose  : 
//=======================================================================

StepFEA_SymmetricTensor23d StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::FeaConstants () const
{
  return theFeaConstants;
}

//=======================================================================
//function : SetFeaConstants
//purpose  : 
//=======================================================================

void StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::SetFeaConstants (const StepFEA_SymmetricTensor23d &aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
