#include "RebScriptManager.h"
#include "RPSTL\RPM_Globals.h"
#include "RPSTL\RPM_Reb3D.h"
#include "RPSTL\RPM_RebGL.h"
#include "RPSTL\RPM_RebWAEM.h"


RebScriptManager::RebScriptManager(RebGDC * sgdc)
{
	SetGlobalGDC(sgdc);
	RebPyLoad_Reb3D();
	RebPyLoad_RebGL();
	RebPyLoad_RebWAEM();
	Py_Initialize();
	gdc = sgdc;

	/*err = PyRun_SimpleString("import Reb3D\n");
	err = PyRun_SimpleString("import RebGL\n");
	err = PyRun_SimpleString("rv1 = Reb3D.RebVector(1.0,0.0,0.0)\n");
	err = PyRun_SimpleString("\n");
*/
	//int err = PyRun_SimpleString("import RebGL\n");

	

	/*PyObject * mm = PyImport_AddModule("__main__");
	PyObject* rv3 = PyObject_GetAttrString(mm, "rv2");
	Reb3D_RebVector_CStruct* crv3 = (Reb3D_RebVector_CStruct*)rv3;*/


	/*FILE * fp = 0;
	std::string ap = gdc->rfs->Search("onEngineStart.py").at(0)->GetAPath();
	fopen_s(&fp, ap.c_str(), "r");
	PyRun_SimpleFile(fp, "onEngineStart.py");
	fclose(fp);*/
	
}