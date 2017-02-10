#include "RebScriptManager.h"
//#include "RPSTL\RPM_Globals.h"
#include "RPSTL\RPM_Reb3D.h"
#include "RPSTL\RPM_RebGL.h"
#include "RPSTL\RPM_RebWAEM.h"

#pragma warning(disable:4996)

RebGDC * ggdc = NULL;

PyObject * PyUnicode_FromCString(std::string from)
{

	std::wstring wc(from.length(), L'#');
	mbstowcs(&wc[0], from.c_str(), from.size());

	return PyUnicode_FromWideChar(wc.c_str(), wc.size());
}


std::string PyUnicode_AsCString(PyObject* o)
{
	wchar_t * buff;

	Py_ssize_t s;
	buff = PyUnicode_AsWideCharString(o, &s);

	return std::string(buff, buff + s);

}

RebScriptManager::RebScriptManager(RebGDC * sgdc)
{
	//SetGlobalGDC(sgdc);
	ggdc = sgdc;
	RebPyLoad_Reb3D();
	RebPyLoad_RebGL();
	RebPyLoad_RebWAEM();
	Py_SetPythonHome(L"./");
	Py_Initialize();
	gdc = sgdc;

	IDir * edir = gdc->rfs->SearchDir(".*/Entities")[0];
	IDir * sdir = gdc->rfs->SearchDir(".*/Scripts")[0];

	int err = 0;
	err = PyRun_SimpleString("import sys\n");
	err = PyRun_SimpleString(("sys.path.append('" + edir->GetAPath() + "')\n").c_str());
	err = PyRun_SimpleString(("sys.path.append('" + sdir->GetAPath() + "')\n").c_str());

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