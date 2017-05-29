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
	{ "GetPos", RebWAEM_RebMouseEvent_GetPos, METH_VARARGS, "Return the clip relative coord of mouse." },
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





struct RebWAEM_RebKeyEvent_CStruct
{
	PyObject_HEAD
	IKeyEvent * ke;
};


int
RebWAEM_RebKeyEvent_init(PyObject* self, PyObject * args, PyObject * kws)
{
	((RebWAEM_RebKeyEvent_CStruct*)self)->ke = NULL;
	return 0;
}


PyObject *
RebWAEM_RebKeyEvent_GetChar(PyObject * self, PyObject * args)
{
	return Py_BuildValue("s", ((RebWAEM_RebKeyEvent_CStruct*)self)->ke->GetReadable().c_str());
}

PyObject *
RebWAEM_RebKeyEvent_GetPOR(PyObject * self, PyObject * args)
{
	if (((RebWAEM_RebKeyEvent_CStruct*)self)->ke->POR())
		return Py_BuildValue("i", 1);
	return Py_BuildValue("i", 0);
}



static PyMethodDef RebWAEM_RebKeyEvent_mets[] =
{
	{ "GetChar", RebWAEM_RebKeyEvent_GetChar, METH_VARARGS, "Get readable character of the key"},
	{ "GetPOR", RebWAEM_RebKeyEvent_GetPOR, METH_VARARGS, " Get wether key pressed or released"},
	{ NULL }
};


static PyTypeObject RebWAEM_RebKeyEvent_PType =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"RebWAEM.RebKeyEvent",             /* tp_name */
	sizeof(RebWAEM_RebKeyEvent_CStruct), /* tp_basicsize */
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
	"Interface for key events",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	RebWAEM_RebKeyEvent_mets,             /* tp_methods */
	0,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	RebWAEM_RebKeyEvent_init,      /* tp_init */
	0,                         /* tp_alloc */
	0,                 /* tp_new */
};


class RebWAEM_RebMouseEventListener_PAdapter : public IMouseEventListener
{
	std::vector<PyObject*> pmel;

	PyObject * CreateMEvent(IMouseEvent * ev)
	{
		RebWAEM_RebMouseEvent_CStruct * ret = PyObject_New(RebWAEM_RebMouseEvent_CStruct, &RebWAEM_RebMouseEvent_PType);
		ret->me = ev;
		return ((PyObject*)ret);
	}

public:


	RebWAEM_RebMouseEventListener_PAdapter()
	{
		pmel.clear();
	}


	

	void onMouseEvent(IMouseEvent* e)
	{
		for (auto it : pmel)
		{
			PyObject_CallMethod(it, "onMouseEvent", "(O)", CreateMEvent(e));
		}
	}

	void AddMouseEventListener(PyObject* mel)
	{
		if (PyObject_HasAttrString(mel, "onMouseEvent") == 0)
			return;


		for (size_t i = 0; i < pmel.size(); i++)
			if (pmel[i] == mel)
				return;
		Py_INCREF(mel);
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



class RebWAEM_RebKeyEventListener_PAdapter : public IKeyEventListener
{
	std::vector<PyObject*> pkel;

	PyObject * CreateKEvent(IKeyEvent * ev)
	{
		RebWAEM_RebKeyEvent_CStruct * ret = PyObject_New(RebWAEM_RebKeyEvent_CStruct, &RebWAEM_RebKeyEvent_PType);
		ret->ke = ev;
		return ((PyObject*)ret);
	}

public:


	RebWAEM_RebKeyEventListener_PAdapter()
	{
		pkel.clear();
	}




	void onKeyEvent(IKeyEvent* e)
	{
		for (auto it : pkel)
		{

			PyObject_CallMethod(it, "onKeyEvent", "(O)", CreateKEvent(e));
		}
	}

	void AddKeyEventListener(PyObject* kel)
	{

		if (PyObject_HasAttrString(kel, "onKeyEvent") == 0)
			return;


		for (size_t i = 0; i < pkel.size(); i++)
			if (pkel[i] == kel)
				return;
		Py_INCREF(kel);
		pkel.push_back(kel);
	}

	void DropMouseEventListener(PyObject* kel)
	{
		for (size_t i = 0; i < pkel.size(); i++)
			if (pkel[i] == kel)
			{
				pkel.erase(pkel.begin() + i);
			}
	}


};



//struct RebWAEM_RebMouseEventListener_CStruct
//{
//	PyObject_HEAD
//};
//
//
//
//PyObject*
//RebWAEM_RebMouseEventListener_onMove(PyObject* self, PyObject* args)
//{
//	Py_RETURN_NONE;
//}
//
//PyObject*
//RebWAEM_RebMouseEventListener_onKeyPress(PyObject* self, PyObject* args)
//{
//	Py_RETURN_NONE;
//}
//
//static PyMethodDef RebWAEM_RebMouseEventListener_mets[] =
//{
//	{"onMove", RebWAEM_RebMouseEventListener_onMove, METH_VARARGS, "Called when mouse moves"},
//	{"onKeyPress", RebWAEM_RebMouseEventListener_onKeyPress, METH_VARARGS, "Calles when a mouse key pressed or released"},
//	{NULL}
//};
//
//static PyTypeObject RebWAEM_RebMouseEventListener_PType =
//{
//	PyVarObject_HEAD_INIT(NULL, 0)
//	"RebWAEM.RebMouseEventListener",             /* tp_name */
//	sizeof(RebWAEM_RebMouseEventListener_CStruct), /* tp_basicsize */
//	0,                         /* tp_itemsize */
//	0,                         /* tp_dealloc */
//	0,                         /* tp_print */
//	0,                         /* tp_getattr */
//	0,                         /* tp_setattr */
//	0,                         /* tp_as_async */
//	0,                         /* tp_repr */
//	0,                         /* tp_as_number */
//	0,                         /* tp_as_sequence */
//	0,                         /* tp_as_mapping */
//	0,                         /* tp_hash  */
//	0,                         /* tp_call */
//	0,                         /* tp_str */
//	0,                         /* tp_getattro */
//	0,                         /* tp_setattro */
//	0,                         /* tp_as_buffer */
//	Py_TPFLAGS_DEFAULT |
//	Py_TPFLAGS_BASETYPE,   /* tp_flags */
//	"Use to catch mouse events",           /* tp_doc */
//	0,                         /* tp_traverse */
//	0,                         /* tp_clear */
//	0,                         /* tp_richcompare */
//	0,                         /* tp_weaklistoffset */
//	0,                         /* tp_iter */
//	0,                         /* tp_iternext */
//	RebWAEM_RebMouseEventListener_mets,             /* tp_methods */
//	0,             /* tp_members */
//	0,                         /* tp_getset */
//	0,                         /* tp_base */
//	0,                         /* tp_dict */
//	0,                         /* tp_descr_get */
//	0,                         /* tp_descr_set */
//	0,                         /* tp_dictoffset */
//	0,      /* tp_init */
//	PyType_GenericAlloc,                         /* tp_alloc */
//	PyType_GenericNew,                 /* tp_new */
//};




struct RebWAEM_RebWAEM_CStruct
{
	PyObject_HEAD
	IWAEM * waem;
	RebWAEM_RebMouseEventListener_PAdapter * meadapt;
	RebWAEM_RebKeyEventListener_PAdapter * keadapt;
};

int RebWAEM_RebWAEM_Init(PyObject* self, PyObject* args, PyObject* kws)
{
	RebWAEM_RebWAEM_CStruct * cself = (RebWAEM_RebWAEM_CStruct*) self;
	cself->waem = ggdc->waem;
	cself->meadapt = new RebWAEM_RebMouseEventListener_PAdapter();
	cself->keadapt = new RebWAEM_RebKeyEventListener_PAdapter();
	cself->waem->RegisterMouseEventListener(cself->meadapt);
	cself->waem->RegisterKeyEventListener(cself->keadapt);
	return 0;
}

PyObject*
RebWAEM_RebWAEM_AddMouseEventListener(PyObject* self, PyObject* args)
{
	RebWAEM_RebWAEM_CStruct* cself = (RebWAEM_RebWAEM_CStruct*)self;
	PyObject* l = NULL;
	if (PyArg_ParseTuple(args, "O", &l))
	{
		cself->meadapt->AddMouseEventListener(l);
	}
	Py_RETURN_NONE;
}

PyObject*
RebWAEM_RebWAEM_AddKeyEventListener(PyObject* self, PyObject* args)
{
	RebWAEM_RebWAEM_CStruct* cself = (RebWAEM_RebWAEM_CStruct*)self;
	PyObject* l = NULL;
	if (PyArg_ParseTuple(args, "O", &l))
	{
		cself->keadapt->AddKeyEventListener(l);
	}
	Py_RETURN_NONE;
}

static PyMethodDef RebWAEM_RebWAEM_mets[] =
{
	{"AddMouseEventListener", RebWAEM_RebWAEM_AddMouseEventListener, METH_VARARGS, "Add a mouse event listener"},
	{ "AddKeyEventListener", RebWAEM_RebWAEM_AddKeyEventListener, METH_VARARGS, "Add a key event listener" },
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
	RebWAEM_RebWAEM_Init,      /* tp_init */
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
	if (PyType_Ready(&RebWAEM_RebKeyEvent_PType) < 0)
		return NULL;
	if (PyType_Ready(&RebWAEM_RebWAEM_PType) < 0)
		return NULL;

	m = PyModule_Create(&RPM_RebWAEM);
	if (m == NULL)
		return NULL;
	
	PyModule_AddObject(m, "RebMouseEvent", (PyObject *)&RebWAEM_RebMouseEvent_PType);
	PyModule_AddObject(m, "RebKeyEvent", (PyObject *)&RebWAEM_RebKeyEvent_PType);
	
	PyObject * et = Py_BuildValue("()");
	RebWAEM_RebWAEM_CStruct * waem = (RebWAEM_RebWAEM_CStruct *) PyObject_Call(((PyObject *)&RebWAEM_RebWAEM_PType), et, NULL);
	PyModule_AddObject(m, "rwaem", (PyObject *)waem);

	return m;
}


int RebPyLoad_RebWAEM()
{
	return PyImport_AppendInittab("RebWAEM", PyInit_RebWAEM);
}