#include "RPM_RebWAEM.h"

struct RebWAEM_RebMouseEvent_CStruct
{
	PyObject_HEAD
	IMouseEvent * me;
};

PyObject *
RebWAEM_RebMouseEvent_new(PyTypeObject* type, PyObject * args, PyObject * kws)
{
	RebWAEM_RebMouseEvent_CStruct * ret = (RebWAEM_RebMouseEvent_CStruct*) type->tp_alloc(type, 0);
	ret->me = NULL;
	return (PyObject*)ret;
}

int
RebWAEM_RebMouseEvent_init(PyObject* self, PyObject * args, PyObject * kws)
{
	PyObject * carg = NULL;
	if (PyArg_ParseTuple(args, "O", carg))
	{
		if (carg->ob_type == self->ob_type)
		{
			((RebWAEM_RebMouseEvent_CStruct*)self)->me = ((RebWAEM_RebMouseEvent_CStruct*)carg)->me;
		}
		return 0;
	}
	return 0;
}

PyObject*
RebWAEM_RebMouseEvent_GetPos(PyObject* self, PyObject * args)
{
	Reb3D_RebVector_CStruct* ret = (Reb3D_RebVector_CStruct*)GetRebVectorPyType()->tp_new(GetRebVectorPyType(), NULL, NULL);
	ret->rv = ((RebWAEM_RebMouseEvent_CStruct*)self)->me->GetPos();
	return (PyObject*)ret;
}

PyObject*
RebWAEM_RebMouseEvent_GetRel(PyObject* self, PyObject * args)
{
	Reb3D_RebVector_CStruct* ret = (Reb3D_RebVector_CStruct*)GetRebVectorPyType()->tp_new(GetRebVectorPyType(), NULL, NULL);
	ret->rv = ((RebWAEM_RebMouseEvent_CStruct*)self)->me->GetRel();
	return (PyObject*)ret;
}



static PyMethodDef RebWAEM_RebMouseEvent_mets[] =
{
	{"GetPos", RebWAEM_RebMouseEvent_GetPos, METH_VARARGS, "Return the clip relative coord of mouse."},
	{ "GetRel", RebWAEM_RebMouseEvent_GetRel, METH_VARARGS, "Return the relative moovement of mouse normalized by the client size." },
	{NULL}
};


static PyTypeObject RebWAEM_RebMouseEvent_PType =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"RebWAEM.RebMouseEvent",             /* tp_name */
	sizeof(RebWAEM_RebMouseEvent_CStruct), /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
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
	RebWAEM_RebMouseEvent_mets,             /* tp_methods */
	0,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	RebWAEM_RebMouseEvent_init,      /* tp_init */
	0,                         /* tp_alloc */
	RebWAEM_RebMouseEvent_new,                 /* tp_new */
};



class RebWAEM_RebMouseEventListener_PAdapter : public IMouseEventListener
{
	std::vector<PyObject*> pmel;
public:
	void onMouseMove(IMouseEvent* me)
	{
		RebWAEM_RebMouseEvent_CStruct * pme = PyObject_New(RebWAEM_RebMouseEvent_CStruct, &RebWAEM_RebMouseEvent_PType);
		pme->me = me;
		for (size_t i = 0; i < pmel.size(); i++)
		{
			PyObject_CallMethod(pmel[i], "onMouseMove", "O", (PyObject*)pme);
		}
	}
	void onMouseKeyPress(IMouseEvent* me)
	{
		RebWAEM_RebMouseEvent_CStruct * pme = PyObject_New(RebWAEM_RebMouseEvent_CStruct, &RebWAEM_RebMouseEvent_PType);
		pme->me = me;
		for (size_t i = 0; i < pmel.size(); i++)
		{
			PyObject_CallMethod(pmel[i], "onMouseKeyPress", "O", (PyObject*)pme);
		}
	}
	void onEvent(IEvent* e)
	{

	}

	void AddMouseEventListener(PyObject* mel)
	{
		for (size_t i = 0; i < pmel.size(); i++)
			if (pmel[i] == mel)
				return;
		pmel.push_back(mel);
	}

	void DropMouseEventListener(PyObject* mel)
	{
		for (size_t i = 0; i < pmel.size(); i++)
			if (pmel[i] == mel)
			{
				pmel.erase(pmel.begin() + i);
			}
	}


};


struct RebWAEM_RebMouseEventListener_CStruct
{
	PyObject_HEAD
};



PyObject*
RebWAEM_RebMouseEventListener_onMove(PyObject* self, PyObject* args)
{
	return NULL;
}

PyObject*
RebWAEM_RebMouseEventListener_onKeyPress(PyObject* self, PyObject* args)
{
	return NULL;
}

static PyMethodDef RebWAEM_RebMouseEventListener_mets[] =
{
	{"onMove", RebWAEM_RebMouseEventListener_onMove, METH_VARARGS, "Called when mouse moves"},
	{"onKeyPress", RebWAEM_RebMouseEventListener_onKeyPress, METH_VARARGS, "Calles when a mouse key pressed or released"},
	{NULL}
};

static PyTypeObject RebWAEM_RebMouseEventListener_PType =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"RebWAEM.RebMouseEventListener",             /* tp_name */
	sizeof(RebWAEM_RebMouseEventListener_CStruct), /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
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
	"Use to catch mouse events",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	RebWAEM_RebMouseEventListener_mets,             /* tp_methods */
	0,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	0,      /* tp_init */
	PyType_GenericAlloc,                         /* tp_alloc */
	PyType_GenericNew,                 /* tp_new */
};




struct RebWAEM_RebWAEM_CStruct
{
	PyObject_HEAD
	IWAEM * waem;
	RebWAEM_RebMouseEventListener_PAdapter meadapt;
};



PyObject*
RebWAEM_RebWAEM_AddMouseEventListener(PyObject* self, PyObject* args)
{
	RebWAEM_RebWAEM_CStruct* cself = (RebWAEM_RebWAEM_CStruct*)self;
	PyObject* l = NULL;
	if (PyArg_ParseTuple(args, "O", l))
	{
		cself->meadapt.AddMouseEventListener(l);
	}
	return NULL;
}

static PyMethodDef RebWAEM_RebWAEM_mets[] =
{
	{"AddMouseEventListener", RebWAEM_RebWAEM_AddMouseEventListener, METH_VARARGS, "Add a mouse event listener"},
	{NULL}
};

static PyTypeObject RebWAEM_RebWAEM_PType = 
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"RebWAEM.RebWAEM",             /* tp_name */
	sizeof(RebWAEM_RebWAEM_CStruct), /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
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
	"The window and event manager",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	RebWAEM_RebWAEM_mets,             /* tp_methods */
	0,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	0,      /* tp_init */
	PyType_GenericAlloc,                         /* tp_alloc */
	PyType_GenericNew,                 /* tp_new */
};


static PyModuleDef RPM_RebWAEM = {
	PyModuleDef_HEAD_INIT,
	"RebWAEM",
	"Module for window and event management",
	-1,
	NULL, NULL, NULL, NULL, NULL
};


static PyObject *
PyInit_RebWAEM()
{
	PyObject* m;

	if (PyType_Ready(&RebWAEM_RebMouseEvent_PType) < 0)
		return NULL;
	if (PyType_Ready(&RebWAEM_RebMouseEventListener_PType) < 0)
		return NULL;
	if (PyType_Ready(&RebWAEM_RebWAEM_PType) < 0)
		return NULL;

	m = PyModule_Create(&RPM_RebWAEM);
	if (m == NULL)
		return NULL;

	
	PyModule_AddObject(m, "RebMouseEvent", (PyObject *)&RebWAEM_RebMouseEvent_PType);
	PyModule_AddObject(m, "RebMouseEventListener", (PyObject *)&RebWAEM_RebMouseEventListener_PType);
	PyModule_AddObject(m, "RebWAEM", (PyObject *)&RebWAEM_RebWAEM_PType);
	
	RebWAEM_RebWAEM_CStruct * waem = PyObject_New(RebWAEM_RebWAEM_CStruct, &RebWAEM_RebWAEM_PType);
	waem->waem = GetGlobalGDC()->waem;
	PyModule_AddObject(m, "rwaem", (PyObject *)waem);

	return m;
}


int RebPyLoad_RebWAEM()
{
	return PyImport_AppendInittab("RebWAEM", PyInit_RebWAEM);
}