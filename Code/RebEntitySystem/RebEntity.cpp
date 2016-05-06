#include "RebEntity.h"

RebEntity::RebEntity(RebFile * sf, std::string name, RebVector spos, std::map<std::string, std::string> * initlists)
{

	//WCHAR WARNING
	std::wstring ws(sf->GetParent()->GetAPath().begin(), sf->GetParent()->GetAPath().end());
	PySys_SetPath(ws.c_str());
	//Path set -> Import

	pmp = PyImport_ImportModule(sf->GetName(false).c_str());
	
	//create instance

	//create init list
	PyObject * initdict = PyDict_New();

	//pass name pos and addr
	PyObject * val = Py_BuildValue("s", name.c_str());
	PyDict_SetItemString(initdict, "name", val);
	Py_DECREF(val);
	val = Py_BuildValue("k", this);
	PyDict_SetItemString(initdict, "cad", val);
	Py_DECREF(val);
	//val = Py_BuildValue("O", );

	//pass additional vars
	/*if (initlist != 0)
	{

	}*/


	pep = PyObject_CallMethod(pmp, sf->GetName(false).c_str(), "O");
	
}