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


#include <Xw_Extension.h>

/* ifdef then trace on */
#ifdef TRACE
#define TRACE_ISDEFINE_TYPE
#endif

/*
   XW_STATUS Xw_isdefine_type (atypemap,index):
   XW_EXT_TYPEMAP *atypemap
   int index			Line type index


	Returns XW_ERROR if BadType Index or type is not defined
	Returns XW_SUCCESS if Successful      

*/

#ifdef XW_PROTOTYPE
XW_STATUS Xw_isdefine_type (void *atypemap,int index)
#else
XW_STATUS Xw_isdefine_type (atypemap,index)
void *atypemap;
int index ;
#endif /*XW_PROTOTYPE*/
{
XW_EXT_TYPEMAP *ptypemap = (XW_EXT_TYPEMAP*)atypemap;
XW_STATUS status = XW_ERROR ;

	if ( index ) {
	   if ( ptypemap && (index < ptypemap->maxtype) &&
				ptypemap->types[index] ) {
	       status = XW_SUCCESS ;
	   } 
	} else status = XW_SUCCESS ;


#ifdef  TRACE_ISDEFINE_TYPE
if( Xw_get_trace() > 2 ) {
    printf (" %d = Xw_isdefine_type(%lx,%d)\n",status,(long ) ptypemap,index) ;
}
#endif

	return (status);
}

#ifdef XW_PROTOTYPE
XW_STATUS Xw_isdefine_typeindex (XW_EXT_TYPEMAP *atypemap,int index)
#else
XW_STATUS Xw_isdefine_typeindex (atypemap,index)
XW_EXT_TYPEMAP *atypemap;
int index ;
#endif /*XW_PROTOTYPE*/
/*
	Verify type index range Only
*/
{
XW_EXT_TYPEMAP *ptypemap = (XW_EXT_TYPEMAP*)atypemap;
XW_STATUS status = XW_ERROR ;

	if( ptypemap && (index > 0) && (index < ptypemap->maxtype) ) {
	   status = XW_SUCCESS ;
	}

#ifdef  TRACE_ISDEFINE_TYPE
if( Xw_get_trace() > 2 ) {
    printf (" %d = Xw_isdefine_typeindex(%lx,%d)\n",status,(long ) ptypemap,index) ;
}
#endif

	return (status) ;
}
