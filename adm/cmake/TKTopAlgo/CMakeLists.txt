set(TOOLKIT TKTopAlgo)

set(TOOLKIT_MODULES
	IntCurvesFace
	MAT
	MAT2d
	Bisector
	BRepMAT2d
	BRepCheck
	BRepBndLib
	BRepExtrema
	BRepClass
	BRepClass3d
	BRepLib
	BRepGProp
	BRepIntCurveSurface
	BRepTopAdaptor
	BRepBuilderAPI
	BRepApprox
)
set(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKGeomBase
	TKBRep
	TKGeomAlgo
)

include(../BuildToolkit.cmake)

