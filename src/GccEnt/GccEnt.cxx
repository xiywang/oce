// Copyright (c) 1995-1999 Matra Datavision
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


//=========================================================================
//   Methods of packing allowing to qualify  objects.              +
//                                                                        +
//=========================================================================

#include <GccEnt.ixx>

GccEnt_QualifiedLin
  GccEnt::Unqualified(const gp_Lin2d& Line) {
    return GccEnt_QualifiedLin(Line,GccEnt_unqualified);
  }

GccEnt_QualifiedCirc
  GccEnt::Unqualified(const gp_Circ2d& Circle) {
    return GccEnt_QualifiedCirc(Circle,GccEnt_unqualified);
  }

GccEnt_QualifiedCirc
  GccEnt::Enclosing(const gp_Circ2d& Circle) {
    return GccEnt_QualifiedCirc(Circle,GccEnt_enclosing);
  }

GccEnt_QualifiedLin
  GccEnt::Enclosed(const gp_Lin2d& Line) {
    return GccEnt_QualifiedLin(Line,GccEnt_enclosed);
  }

GccEnt_QualifiedCirc
  GccEnt::Enclosed(const gp_Circ2d& Circle) {
    return GccEnt_QualifiedCirc(Circle,GccEnt_enclosed);
  }

GccEnt_QualifiedCirc
  GccEnt::Outside(const gp_Circ2d& Circle) {
    return GccEnt_QualifiedCirc(Circle,GccEnt_outside);
  }

GccEnt_QualifiedLin
  GccEnt::Outside(const gp_Lin2d& Line) {
    return GccEnt_QualifiedLin(Line,GccEnt_outside);
  }
