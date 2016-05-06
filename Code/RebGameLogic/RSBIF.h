#pragma once
#include "..\SDKs\Python35-32\include\Python.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"



//RebRenderer


//RebAudioSystem

//RebFileSystem
//RebFile

PyObject * RF_GetName(PyObject * self, PyObject *args);
PyObject * RF_GetAPath(PyObject * self, PyObject *args);
//PyObject * RF_GetRPath(PyObject * self, PyObject *args);
PyObject * RF_GetExtension(PyObject * self, PyObject *args);

//RebDir

PyObject * RD_GetAPath(PyObject * self, PyObject *args);
PyObject * RD_GetRPath(PyObject * self, PyObject *args);
PyObject * RD_GetName(PyObject * self, PyObject *args);

PyObject * RD_Search(PyObject * self, PyObject *args);
PyObject * RD_SearchDir(PyObject * self, PyObject *args);

PyObject * RD_GetAllFiles(PyObject * self, PyObject *args);

PyObject * RD_GetDirs(PyObject * self, PyObject *args);
PyObject * RD_GetFiles(PyObject * self, PyObject *args);

