#include "RPM_Globals.h"

static RebGDC* ggdc = 0;

RebGDC* GetGlobalGDC()
{
	return ggdc;
}

void SetGlobalGDC(RebGDC* set)
{
	ggdc = set;
}

void RebPyDepends(const char* modulename)
{
	PyObject * mm = PyImport_AddModule("__main__");
	if (!PyObject_HasAttrString(mm, modulename))
	{
		std::string cmd = "import ";
		cmd.append(modulename);
		cmd.append("\n");
		PyRun_SimpleString(cmd.c_str());
	}
}



PyTypeObject * RebPyGetType(const char* tname)
{
	PyObject * mm = PyImport_AddModule("__main__");
	PyObject* ret = PyObject_GetAttrString(mm, tname);
	return (PyTypeObject*) ret;
}