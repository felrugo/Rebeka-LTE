#ifndef RPM_REB3D_H
#define RPM_REB3D_H
#include "../../Reb3D/Reb3d.h"
#include "..\..\RebSupport\RebGDC.h"

struct Reb3D_RebVector_CStruct {
	PyObject_HEAD
		RebVector rv;
};



PyTypeObject * GetRebVectorPyType();

struct Reb3D_RebMatrix_CStruct
{
	PyObject_HEAD
		RebMatrix rm;
};

PyTypeObject * GetRebMatrixPyType();


int RebPyLoad_Reb3D();





#endif