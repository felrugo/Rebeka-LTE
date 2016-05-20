#include "RebScriptManager.h"
#include "RPSTL\RPM_Reb3D.h"
#include "RPSTL\RPM_RebGL.h"

RebScriptManager::RebScriptManager(RebGDC * sgdc)
{
	RebPyLoad_Reb3D();
	RebPyLoad_RebGL(sgdc);
	Py_Initialize();
	gdc = sgdc;

	int err;

	err = PyRun_SimpleString("import Reb3D\n");
	//err = PyRun_SimpleString("import RebGL\n");
	
	err = PyRun_SimpleString("a = Reb3D.RebVector(1.0, 0.0, 0.0)\n");

	err = PyRun_SimpleString("RebGL.rrd.ClearColor(a)\n");


	PyObject * mm = PyImport_AddModule("__main__");
	err = PyModule_AddObject(mm, "Added", Py_BuildValue("l", 12));

	err = PyRun_SimpleString("print(Added)\n");

	/*FILE * fp = 0;
	std::string ap = gdc->rfs->Search("onEngineStart.py").at(0)->GetAPath();
	fopen_s(&fp, ap.c_str(), "r");
	PyRun_SimpleFile(fp, "onEngineStart.py");
	fclose(fp);*/
	
}