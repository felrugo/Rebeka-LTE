#include <Python.h>
#include "..\..\Rimba\IRenderDevice.h"
#include "RPM_RebGL.h"


struct RebGL_RebRenderDevice_CStruct
{
	PyObject_HEAD
	IRenderDevice * ird;
};


PyObject *
RebGL_RebRenderDevice_new(PyTypeObject* type, PyObject * args, PyObject * kws)
{

}

int
RebGL_RebRenderDevice_init(PyObject * self, PyObject *args, PyObject *kws)
{

}

void
RebGL_RebRenderDevice_dealloc(PyObject * self)
{

}

PyObject *
RebGL_RebRenderDevice_clearcolor(PyObject * self, PyObject * args)
{

}



static PyMethodDef RebGL_RebRenderDevice_Mets[] = 
{
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
	0,             /* tp_methods */
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

