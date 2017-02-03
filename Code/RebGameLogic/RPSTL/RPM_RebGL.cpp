#include "..\..\Rimba\IRenderDevice.h"
#include "RPM_Reb3D.h"
#include "RPM_RebGL.h"


struct RebGL_RebRenderDevice_CStruct
{
	PyObject_HEAD
	IRenderDevice * ird;
};


PyObject *
RebGL_RebRenderDevice_new(PyTypeObject* type, PyObject * args, PyObject * kws)
{
	RebGL_RebRenderDevice_CStruct * ret = (RebGL_RebRenderDevice_CStruct *) type->tp_alloc(type, 0);
	return (PyObject*)ret;
}

int
RebGL_RebRenderDevice_init(PyObject * self, PyObject *args, PyObject *kws)
{
	RebGL_RebRenderDevice_CStruct * cself = ((RebGL_RebRenderDevice_CStruct*)self);
	cself->ird = ggdc->rd;
	return 0;
}

void
RebGL_RebRenderDevice_dealloc(PyObject * self)
{
	self->ob_type->tp_free(self);
}

PyObject *
RebGL_RebRenderDevice_setviewportmat(PyObject * self, PyObject * args)
{
	Reb3D_RebMatrix_CStruct* toset;
	if (PyArg_ParseTuple(args, "O", &toset))
	{
		if (Py_TYPE(toset) == RebPyGetType("Reb3D.RebMatrix"))
		{
			((RebGL_RebRenderDevice_CStruct*)self)->ird->SetViewportMat(toset->rm);
		}
		return Py_NotImplemented;
	}
	return Py_NotImplemented;
}

PyObject *
RebGL_RebRenderDevice_clearcolor(PyObject * self, PyObject * args)
{
	
	PyObject* vec;
	if (PyArg_ParseTuple(args, "O", &vec))
	{
		PyObject* err = PyErr_Occurred();
		if (Py_TYPE(vec) == GetRebVectorPyType())
		{
			Reb3D_RebVector_CStruct* rvec3 = (Reb3D_RebVector_CStruct*)vec;
			((RebGL_RebRenderDevice_CStruct*)self)->ird->ClearColor(rvec3->rv.x, rvec3->rv.y, rvec3->rv.z, 1.0f);
		}
	}
	PyObject* err = PyErr_Occurred();
	return Py_BuildValue("s", 0);
}



static PyMethodDef RebGL_RebRenderDevice_Mets[] = 
{
	{"ClearColor", RebGL_RebRenderDevice_clearcolor, METH_VARARGS, "Clear color of the screen"},
	{"SetViewportMat", RebGL_RebRenderDevice_setviewportmat, METH_VARARGS, "Change the view matrix"},
	{NULL}
};

static PyTypeObject RebGL_RebRenderDevice_PType =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"RebGL.RebRenderDevice",             /* tp_name */
	sizeof(RebGL_RebRenderDevice_CStruct), /* tp_basicsize */
	0,                         /* tp_itemsize */
	RebGL_RebRenderDevice_dealloc,                         /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_as_async */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT |
	Py_TPFLAGS_BASETYPE,   /* tp_flags */
	"The main rendering module",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	RebGL_RebRenderDevice_Mets,             /* tp_methods */
	0,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	RebGL_RebRenderDevice_init,      /* tp_init */
	0,                         /* tp_alloc */
	RebGL_RebRenderDevice_new,                 /* tp_new */
};




static PyModuleDef RPM_RebGL = {
	PyModuleDef_HEAD_INIT,
	"RebGL",
	"Module for graphic library",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

static PyObject *
PyInit_RebGL()
{
	RebPyDepends("Reb3D");


	PyObject* m;

	if (PyType_Ready(&RebGL_RebRenderDevice_PType) < 0)
		return NULL;

	m = PyModule_Create(&RPM_RebGL);
	if (m == NULL)
		return NULL;

	PyObject * earg = Py_BuildValue("()");
	
	PyObject * rrd = PyObject_Call((PyObject *)&RebGL_RebRenderDevice_PType, earg, NULL);
	//rrd->ird = GetGlobalGDC()->rd;
	PyModule_AddObject(m, "rrd", rrd);

	return m;
}


int RebPyLoad_RebGL()
{
	return PyImport_AppendInittab("RebGL", PyInit_RebGL);
}