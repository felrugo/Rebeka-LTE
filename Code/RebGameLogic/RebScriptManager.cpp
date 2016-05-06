#include "RebScriptManager.h"
#include "RPSTL\RPM_Reb3D.h"

RebScriptManager::RebScriptManager(RebGDC * sgdc)
{
	RebPyLoad_Reb3D();
	Py_Initialize();
	gdc = sgdc;

	int err;

	err = PyRun_SimpleString("import Reb3D\n");
	
	err = PyRun_SimpleString("a = Reb3D.RebVector(1.0, 0.0, 0.0)\n");
	
	err = PyRun_SimpleString("b = Reb3D.RebMatrix()\n");
	err = PyRun_SimpleString("c = b * a\n");
	PyRun_SimpleString("print(c)\n");

	PyObject * mm = PyImport_AddModule("__main__");
	PyObject * veca = PyObject_GetAttrString(mm, "c");

	/*FILE * fp = 0;
	std::string ap = gdc->rfs->Search("onEngineStart.py").at(0)->GetAPath();
	fopen_s(&fp, ap.c_str(), "r");
	PyRun_SimpleFile(fp, "onEngineStart.py");
	fclose(fp);*/
	
}