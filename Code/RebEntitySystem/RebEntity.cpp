#include "RebEntity.h"

RebEntity::RebEntity(RebFile * sf, std::string name, RebVector spos, RebVector sori, std::map<std::string, std::string> * initlist)
{

	//determine if import needed
	
	PyObject * mm = PyImport_AddModule("__main__");
	PyObject * et = PyObject_GetAttrString(mm, sf->GetName(false).c_str());

	std::string test = sf->GetName(false);
	if (et == NULL)
	{
		/*PyErr_Clear();
		std::string exs = "with open(\"" + sf->GetAPath() +"\") as f:\n";
		exs = exs + "\tcode = compile(f.read(), \"" + sf->GetName() + "\", 'exec')\n";
		exs = exs + "\texec(code)\n";
		int err = PyRun_SimpleString(exs.c_str());*/
		PyErr_Clear();
		FILE * fp = fopen(sf->GetAPath().c_str(), "r");
		int err = PyRun_SimpleFile(fp, sf->GetName().c_str());
		fclose(fp);
	}
	et = PyObject_GetAttrString(mm, sf->GetName(false).c_str());

	this->name = name;
	
	//create instance

	//create init list
	PyObject * initdict = PyDict_New();

	//pass name
	PyObject * val = Py_BuildValue("s", name.c_str());
	PyDict_SetItemString(initdict, "name", val);
	Py_DECREF(val);

	//pos and ori
	//Reb3D module
	PyObject * rvtype, * r3dm = PyImport_ImportModule("Reb3D");
	rvtype = PyObject_GetAttrString(r3dm, "RebVector");

	PyObject * args = Py_BuildValue("fff", spos.x, spos.y, spos.z);
	val = PyObject_CallObject(rvtype, args);
	PyDict_SetItemString(initdict, "pos", val);
	Py_DECREF(val);
	Py_DECREF(args);

	args = Py_BuildValue("fff", sori.x, sori.y, sori.z);
	val = PyObject_CallObject(rvtype, args);
	PyDict_SetItemString(initdict, "ori", val);
	Py_DECREF(val);
	Py_DECREF(args);
	Py_DECREF(rvtype);
	Py_DECREF(r3dm);

	//pass additional vars
	if (initlist != 0)
	{
		for (std::map<std::string, std::string>::iterator it = initlist->begin(); it != initlist->end(); it++)
		{
			val = Py_BuildValue("s", it->second.c_str());
			PyDict_SetItemString(initdict, it->first.c_str(), val);
			Py_DECREF(val);
		}
	}


	PyObject * argt = Py_BuildValue("(O)", initdict);
	pep = PyObject_CallObject(et, argt);
	Py_DECREF(argt);
	Py_DECREF(initdict);
}


void RebEntity::SetPos(RebVector spos)
{
	PyObject * val, * rvtype, *r3dm = PyImport_ImportModule("Reb3D");
	rvtype = PyObject_GetAttrString(r3dm, "RebVector");

	val = PyObject_CallObject(rvtype, Py_BuildValue("fff", spos.x, spos.y, spos.z));
	PyObject_CallMethod(pep, "SetPos", "O", val);
	Py_DECREF(val);
	Py_DECREF(rvtype);
	Py_DECREF(r3dm);
}

void RebEntity::SetOri(RebVector sori)
{
	PyObject * val, *rvtype, *r3dm = PyImport_ImportModule("Reb3D");
	rvtype = PyObject_GetAttrString(r3dm, "RebVector");

	val = PyObject_CallObject(rvtype, Py_BuildValue("fff", sori.x, sori.y, sori.z));
	PyObject_CallMethod(pep, "SetOri", "O", val);
	Py_DECREF(val);
	Py_DECREF(rvtype);
	Py_DECREF(r3dm);
}

void RebEntity::SetParam(std::string key, std::string value)
{
	PyObject_CallMethod(pep, "SetParam", "(ss)", key.c_str(), value.c_str());
}

void RebEntity::Update()
{
	PyObject_CallMethod(pep, "Update", "");
}

std::string RebEntity::GetName()
{
	return name;
}

RebVector RebEntity::GetPos()
{
	return RebVector();
}

std::string RebEntity::GetParam(std::string key)
{
	PyObject * ret;
	ret = PyObject_CallMethod(pep, "GetParam", "(s)", key.c_str());
	char * str;
	PyObject * toa = PyUnicode_AsASCIIString(ret);
	str = PyBytes_AsString(toa);
	std::string sret = str;
	Py_DECREF(ret);
	Py_DECREF(toa);
	return sret;
}

