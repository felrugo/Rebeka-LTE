#include "RSBIF.h"

//RebFile

PyObject * RF_GetName(PyObject * self, PyObject *args)
{
	RebFile * rf;
	if (PyArg_ParseTuple(args, "k", &rf))
	{
		return Py_BuildValue("s", rf->GetName().c_str());
	}
	return NULL;
}
PyObject * RF_GetAPath(PyObject * self, PyObject *args)
{
	RebFile * rf;
	if (PyArg_ParseTuple(args, "k", &rf))
	{
		return Py_BuildValue("s", rf->GetAPath().c_str());
	}
	return NULL;
}
//PyObject * RF_GetRPath(PyObject * self, PyObject *args);

PyObject * RF_GetExtension(PyObject * self, PyObject *args)
{
	RebFile * rf;
	if (PyArg_ParseTuple(args, "k", &rf))
	{
		return Py_BuildValue("s", rf->GetExtension().c_str());
	}
	return NULL;
}

//RebDir

PyObject * RD_GetAPath(PyObject * self, PyObject *args);
PyObject * RD_GetRPath(PyObject * self, PyObject *args);
PyObject * RD_GetName(PyObject * self, PyObject *args);

PyObject * RD_Search(PyObject * self, PyObject *args);
PyObject * RD_SearchDir(PyObject * self, PyObject *args);

PyObject * RD_GetAllFiles(PyObject * self, PyObject *args);

PyObject * RD_GetDirs(PyObject * self, PyObject *args);
PyObject * RD_GetFiles(PyObject * self, PyObject *args);

//RebFileSystem