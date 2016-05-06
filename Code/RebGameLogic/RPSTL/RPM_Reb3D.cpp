
#include <Python.h>
#include "../../Reb3D/Reb3d.h"
#include "RPM_Reb3D.h"



struct Reb3D_RebVector_CStruct {
	PyObject_HEAD
		RebVector rv;
};



static void
Reb3D_RebVector_dealloc(Reb3D_RebVector_CStruct* self)
{
	Py_TYPE(self)->tp_free((PyObject*)self);
}



static PyObject *
Reb3D_RebVector_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	Reb3D_RebVector_CStruct *self = (Reb3D_RebVector_CStruct *)type->tp_alloc(type, 0);
	return (PyObject *)self;
}


static int
Reb3D_RebVector_init(Reb3D_RebVector_CStruct *self, PyObject *args, PyObject *kwds)
{
	float x, y, z;
	if (PyArg_ParseTuple(args, "fff", &x, &y, &z))
		self->rv = RebVector(x, y, z);
	else
		self->rv = RebVector();
	PyErr_Clear();
	return 0;
}




static PyObject *
Reb3D_RebVector_add(PyObject *self, PyObject * arg)
{
	Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, self->ob_type);
	ret->rv = RebVector(((Reb3D_RebVector_CStruct*)self)->rv + ((Reb3D_RebVector_CStruct*)arg)->rv);
	Py_DECREF(self);
	Py_DECREF(arg);
	return (PyObject*)ret;
}


static PyNumberMethods Reb3D_RebVector_NM =
{
Reb3D_RebVector_add
};




static PyTypeObject Reb3D_RebVector_PType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"Reb3D.RebVector",             /* tp_name */
	sizeof(Reb3D_RebVector_CStruct),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)Reb3D_RebVector_dealloc, /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	&Reb3D_RebVector_NM,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT |
	Py_TPFLAGS_BASETYPE,		/* tp_flags */
	"Vector from Reb3D library", /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	0,             /* tp_methods */
	0,							/* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)Reb3D_RebVector_init,      /* tp_init */
	0,                         /* tp_alloc */
	Reb3D_RebVector_new                 /* tp_new */
};



struct Reb3D_RebMatrix_CStruct
{
	PyObject_HEAD
	RebMatrix rm;
};


static PyObject*
Reb3D_RebMatrix_new(PyTypeObject *type, PyObject *args, PyObject *kws)
{
	Reb3D_RebMatrix_CStruct* ret = (Reb3D_RebMatrix_CStruct*)type->tp_alloc(type, 0);
	return (PyObject*)ret;
}

static int
Reb3D_RebMatrix_init(PyObject* self, PyObject* args)//NO_ARG
{
	Reb3D_RebMatrix_CStruct* pymat = (Reb3D_RebMatrix_CStruct*)self;
	pymat->rm.Identity();
	return 0;
}

static void
Reb3D_RebMatrix_dealloc(PyObject* self)
{
	self->ob_type->tp_free(self);
}

static PyObject*
Reb3D_RebMatrix_mul(PyObject* self, PyObject* arg)
{
	if (Py_TYPE(self) == Py_TYPE(arg)) // mat * mat
	{
		Reb3D_RebMatrix_CStruct *op1 = (Reb3D_RebMatrix_CStruct*)self, *op2 = (Reb3D_RebMatrix_CStruct*)arg, *ret = PyObject_New(Reb3D_RebMatrix_CStruct, self->ob_type);
		ret->rm = op1->rm * op2->rm;
		return (PyObject*)ret;
	}
	if (Py_TYPE(arg) == &Reb3D_RebVector_PType)
	{
		Reb3D_RebMatrix_CStruct *op1 = (Reb3D_RebMatrix_CStruct*)self;
		Reb3D_RebVector_CStruct * op2 = (Reb3D_RebVector_CStruct*)arg, *ret = PyObject_New(Reb3D_RebVector_CStruct, self->ob_type);
		ret->rv = op1->rm * op2->rv;
		return (PyObject*)ret;
	}

	return Py_NotImplemented;
}


static PyNumberMethods Reb3D_RebMatrix_NM =
{
0,0,
Reb3D_RebMatrix_mul
};




static PyTypeObject Reb3D_RebMatrix_PType = 
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"Reb3D.RebMatrix",             /* tp_name */
	sizeof(Reb3D_RebMatrix_CStruct),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)Reb3D_RebMatrix_dealloc, /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	&Reb3D_RebMatrix_NM,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT |
	Py_TPFLAGS_BASETYPE,		/* tp_flags */
	"Matrix from Reb3D library", /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	0,             /* tp_methods */
	0,							/* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)Reb3D_RebMatrix_init,      /* tp_init */
	0,                         /* tp_alloc */
	Reb3D_RebMatrix_new                 /* tp_new */
};


static PyModuleDef RPM_Reb3D = {
	PyModuleDef_HEAD_INIT,
	"Reb3D",
	"Module for 3d calculations",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

static PyObject *
PyInit_Reb3D(void)
{
	PyObject* m;

	if (PyType_Ready(&Reb3D_RebVector_PType) < 0)
		return NULL;

	if (PyType_Ready(&Reb3D_RebMatrix_PType) < 0)
		return NULL;

	m = PyModule_Create(&RPM_Reb3D);
	if (m == NULL)
		return NULL;

	//Py_INCREF(&Reb3D_RebVector_PType);
	PyModule_AddObject(m, "RebVector", (PyObject *)&Reb3D_RebVector_PType);
	PyModule_AddObject(m, "RebMatrix", (PyObject *)&Reb3D_RebMatrix_PType);
	return m;
}



int RebPyLoad_Reb3D()
{
	return PyImport_AppendInittab("Reb3D", PyInit_Reb3D);
}