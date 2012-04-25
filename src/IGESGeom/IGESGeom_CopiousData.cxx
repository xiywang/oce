// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <IGESGeom_CopiousData.ixx>
#include <Standard_DimensionMismatch.hxx>
#include <gp_XY.hxx>
#include <gp_GTrsf.hxx>
#include <Standard_NullObject.hxx>

IGESGeom_CopiousData::IGESGeom_CopiousData ()
{
  theDataType = 0;  // to allow Setting Form Number before Init
}


    void IGESGeom_CopiousData::Init
  (const Standard_Integer aDataType,
   const Standard_Real aZPlane,
   const Handle(TColStd_HArray1OfReal)& allData)
{
  // PTV OCC386 crach application while reading So5771b.igs
  if (allData.IsNull())
    Standard_NullObject::Raise("IGESGeom_CopiousData : Init with null data");
  
  if (allData->Lower() != 1) Standard_DimensionMismatch::Raise("IGESGeom_CopiousData : Init");
  theDataType = aDataType;
  theZPlane   = aZPlane;
  theData     = allData;
// FormNumber = DataType + <N>  N=0 -> Set of Points. N=10 : PolyLine
//    or N=62 (DataType=1 only, gives FormNumber=63) : 2D closed path
  InitTypeAndForm(106,FormNumber());
}

    void  IGESGeom_CopiousData::SetPolyline (const Standard_Boolean F)
{
  Standard_Integer newfn = theDataType;
  if (F) newfn += 10;
  InitTypeAndForm(106,newfn);
}

    void  IGESGeom_CopiousData::SetClosedPath2D ()
{
  InitTypeAndForm(106,63);    // et verifier DataType !
}


    Standard_Boolean  IGESGeom_CopiousData::IsPointSet () const
{
  return (FormNumber() < 10);
}

    Standard_Boolean  IGESGeom_CopiousData::IsPolyline () const
{
  return (FormNumber()/10 == 1);
}

    Standard_Boolean  IGESGeom_CopiousData::IsClosedPath2D () const
{
  return (FormNumber() == 63);
}


    Standard_Integer IGESGeom_CopiousData::DataType () const
{
  return theDataType;
}

    Standard_Integer IGESGeom_CopiousData::NbPoints () const
{
  Standard_Integer nbtuples;
  // PTV OCC386 
  if (theData.IsNull())
    nbtuples = 0;
  else
    nbtuples = theData->Length();
  if      (theDataType == 1)    nbtuples /= 2;
  else if (theDataType == 2)    nbtuples /= 3;
  else if (theDataType == 3)    nbtuples /= 6;
  return nbtuples;
}

    Standard_Real  IGESGeom_CopiousData::Data
  (const Standard_Integer nump, const Standard_Integer numdata) const
{
  Standard_Integer numd = 0;
  if      (theDataType == 1) numd = 2*(nump - 1) + numdata;  // 1-2
  else if (theDataType == 2) numd = 3*(nump - 1) + numdata;  // 1-2-3
  else if (theDataType == 3) numd = 6*(nump - 1) + numdata;  // 1-2-3-4-5-6
  return theData->Value(numd);
}

    Standard_Real IGESGeom_CopiousData::ZPlane () const
{
  return theZPlane;
}

    gp_Pnt IGESGeom_CopiousData::Point (const Standard_Integer anIndex) const
{
  Standard_Integer lower = theData->Lower();
  Standard_Integer real_index;
  Standard_Real X=0.,Y=0.,Z=0. ;
  if (theDataType == 1) {
    real_index = lower + 2 * (anIndex-1);
    X = theData->Value(real_index);
    Y = theData->Value(real_index+1);
    Z = theZPlane;
  }

  if (theDataType == 2) {
    real_index = lower + 3 * (anIndex-1);
    X = theData->Value(real_index);
    Y = theData->Value(real_index+1);
    Z = theData->Value(real_index+2);
  }

  if (theDataType == 3) {
    real_index = lower + 6 * (anIndex-1);
    X = theData->Value(real_index);
    Y = theData->Value(real_index+1);
    Z = theData->Value(real_index+2);
  }

  gp_Pnt point(X,Y,Z);
  return point;
}

    gp_Pnt IGESGeom_CopiousData::TransformedPoint
  (const Standard_Integer anIndex) const
{
  if (!HasTransf()) return Point(anIndex);
  gp_XYZ xyz (Point(anIndex).XYZ());
  Location().Transforms(xyz);
  return gp_Pnt(xyz);
}

    gp_Vec IGESGeom_CopiousData::Vector (const Standard_Integer anIndex) const
{
  Standard_Integer lower = theData->Lower();
  Standard_Integer Real_Index;
  if (theDataType != 3) return gp_Vec(0.0, 0.0, 0.0);
  Real_Index = lower + 6*(anIndex-1) +3;
  Standard_Real I = theData->Value(Real_Index);
  Standard_Real J = theData->Value(Real_Index+1);
  Standard_Real K = theData->Value(Real_Index+2);
  return gp_Vec(I, J, K);
}

    gp_Vec IGESGeom_CopiousData::TransformedVector
  (const Standard_Integer anIndex) const
{
  if (!HasTransf()) return Vector (anIndex);
  gp_XYZ xyz (Vector(anIndex).XYZ());
  gp_GTrsf loc = Location();
  loc.SetTranslationPart(gp_XYZ(0.,0.,0.));
  loc.Transforms(xyz);
  return gp_Vec(xyz);
}
