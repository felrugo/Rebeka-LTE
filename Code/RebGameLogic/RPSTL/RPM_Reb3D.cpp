
#include "RPM_Globals.h"
#include "RPM_Reb3D.h"





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




PyObject *
Reb3D_RebVector_add(PyObject *self, PyObject * arg)
{
	Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, self->ob_type);
	ret->rv = RebVector(((Reb3D_RebVector_CStruct*)self)->rv + ((Reb3D_RebVector_CStruct*)arg)->rv);
	return (PyObject*)ret;
}

PyObject *
Reb3D_RebVector_mul(PyObject *self, PyObject * arg)
{

	if (self->ob_type == GetRebVectorPyType())
	{
		if (strcmp(Py_TYPE(arg)->tp_name, "Reb3D.RebVector") == 0)
		{
			float ret = ((Reb3D_RebVector_CStruct*)self)->rv * ((Reb3D_RebVector_CStruct*)arg)->rv;
			return Py_BuildValue("f", ret);
		}
		float f;
		if (PyArg_Parse(arg, "f", &f))
		{
			Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, self->ob_type);
			ret->rv = RebVector(((Reb3D_RebVector_CStruct*)self)->rv * f);
			return (PyObject*)ret;
		}
	}
	if (PyFloat_Check(self))
	{
		PyFloatObject * fo = (PyFloatObject*)self;
		Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, arg->ob_type);
		ret->rv = RebVector(((Reb3D_RebVector_CStruct*)arg)->rv * fo->ob_fval);
		return (PyObject*)ret;
	}
	int im;
	if (PyArg_Parse(self, "i", &im))
	{
		Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, arg->ob_type);
		ret->rv = RebVector(((Reb3D_RebVector_CStruct*)arg)->rv * im);
		return (PyObject*)ret;
	}
	return Py_NotImplemented;
}

PyObject *
Reb3D_RebVector_neg(PyObject *self)
{
	Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, self->ob_type);
	ret->rv = RebVector(((Reb3D_RebVector_CStruct*)self)->rv * -1.0f);
	return (PyObject*)ret;
}


static PyNumberMethods Reb3D_RebVector_NM =
{
Reb3D_RebVector_add,
NULL,
Reb3D_RebVector_mul,
NULL, NULL, NULL,
Reb3D_RebVector_neg
};


PyObject*
Reb3D_RebVector_cross(PyObject* self, PyObject* args)
{
	PyObject* a1 = NULL;
	PyObject *a2 = NULL;
	if (PyArg_ParseTuple(args, "OO", &a1, &a2))
	{
		Reb3D_RebVector_CStruct* cself = (Reb3D_RebVector_CStruct*)self;
		cself->rv.Cross(((Reb3D_RebVector_CStruct*)a1)->rv, ((Reb3D_RebVector_CStruct*)a2)->rv);
	}
	return Py_BuildValue("s", 0);
}


static PyMethodDef Reb3D_RebVector_mets[] =
{
	//{"Dot", Reb3D_RebVector_dot, METH_VARARGS, "Dot function of RebVector"},
	{"Cross", Reb3D_RebVector_cross, METH_VARARGS, "Cross function of RebVector"},
	{NULL}
};


 PyTypeObject Reb3D_RebVector_PType = {
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
	Reb3D_RebVector_mets,             /* tp_methods */
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

PyTypeObject * GetRebVectorPyType()
{
	return &Reb3D_RebVector_PType;
}




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

PyObject*
Reb3D_RebMatrix_RotX(PyObject* self, PyObject* args)
{
	float f;
	if (PyArg_ParseTuple(args, "f", &f))
	{
		Reb3D_RebMatrix_CStruct* cself = (Reb3D_RebMatrix_CStruct*)self;
		cself->rm.RotaX(f);
	}
	return Py_BuildValue("s", 0);
}

PyObject*
Reb3D_RebMatrix_RotY(PyObject* self, PyObject* args)
{
	float f;
	if (PyArg_ParseTuple(args, "f", &f))
	{
		Reb3D_RebMatrix_CStruct* cself = (Reb3D_RebMatrix_CStruct*)self;
		cself->rm.RotaY(f);
	}
	return Py_BuildValue("s", 0);
}
PyObject*
Reb3D_RebMatrix_RotZ(PyObject* self, PyObject* args)
{
	float f;
	if (PyArg_ParseTuple(args, "f", &f))
	{
		Reb3D_RebMatrix_CStruct* cself = (Reb3D_RebMatrix_CStruct*)self;
		cself->rm.RotaZ(f);
	}
	return Py_BuildValue("s", 0);
}

PyObject*
Reb3D_RebMatrix_RotOri(PyObject* self, PyObject* args)
{
	PyObject* arg = NULL;
	if (PyArg_ParseTuple(args, "O", &arg))
	{
		if (Py_TYPE(arg) == &Reb3D_RebVector_PType)
		{
			Reb3D_RebVector_CStruct* carg = (Reb3D_RebVector_CStruct*)arg;
			((Reb3D_RebMatrix_CStruct*)self)->rm.RotaWorld(carg->rv.x, carg->rv.y, carg->rv.z);
		}
	}
	return Py_BuildValue("s", 0);
}

PyObject*
Reb3D_RebMatrix_Translate(PyObject* self, PyObject* args)
{
	PyObject* arg = NULL;
	if (PyArg_ParseTuple(args, "O", &arg))
	{
		if (Py_TYPE(arg) == &Reb3D_RebVector_PType)
		{
			Reb3D_RebVector_CStruct* carg = (Reb3D_RebVector_CStruct*)arg;
			((Reb3D_RebMatrix_CStruct*)self)->rm.Translate(carg->rv.x, carg->rv.y, carg->rv.z);
		}
	}
	return Py_BuildValue("s", 0);
}

PyMethodDef Reb3D_RebMatrix_mets[] =
{
	{"RotX", Reb3D_RebMatrix_RotX, METH_VARARGS, "Rotation around x axis."},
	{ "RotY", Reb3D_RebMatrix_RotY, METH_VARARGS, "Rotation around y axis." },
	{ "RotZ", Reb3D_RebMatrix_RotZ, METH_VARARGS, "Rotation around z axis." },
	{ "RotOri", Reb3D_RebMatrix_RotOri, METH_VARARGS, "Rotation with Orientation." },
	{ "Translate", Reb3D_RebMatrix_Translate, METH_VARARGS, "Translate with RebVector." },
	{NULL}
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


PyTypeObject * GetRebMatrixPyType()
{
	return &Reb3D_RebMatrix_PType;
}


PyObject*
Reb3D_deg(PyObject* self, PyObject* args)
{
	PyObject* arg = NULL;
	if (PyArg_ParseTuple(args, "O", &arg))
	{
		if (Py_TYPE(arg) == &Reb3D_RebVector_PType)
		{
			Reb3D_RebVector_CStruct * ret = PyObject_New(Reb3D_RebVector_CStruct, &Reb3D_RebVector_PType);
			Reb3D_RebVector_CStruct * carg = (Reb3D_RebVector_CStruct*)arg;
			ret->rv.x = carg->rv.x * PI / 180.0f;
			ret->rv.y = carg->rv.y * PI / 180.0f;
			ret->rv.z = carg->rv.z * PI / 180.0f;
			return (PyObject*)ret;
		}
	}
	float f;
	if (PyArg_ParseTuple(args, "f", &f))
	{
		f = f * PI / 180.0f;
		return Py_BuildValue("f", f);
	}
	return Py_NotImplemented;
}

PyMethodDef Reb3D_mets[] =
{
	{"deg", Reb3D_deg, METH_VARARGS, "Converts deg to rad"},
	{NULL}
};

static PyModuleDef RPM_Reb3D = {
	PyModuleDef_HEAD_INIT,
	"Reb3D",
	"Module for 3d calculations",
	-1,
	Reb3D_mets, NULL, NULL, NULL, NULL
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

	PyModule_AddObject(m, "RebVector", (PyObject *)&Reb3D_RebVector_PType);
	PyModule_AddObject(m, "RebMatrix", (PyObject *)&Reb3D_RebMatrix_PType);
	return m;
}



int RebPyLoad_Reb3D()
{
	return PyImport_AppendInittab("Reb3D", PyInit_Reb3D);
}