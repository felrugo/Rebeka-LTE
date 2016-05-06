#ifndef REBENTITY_H
#define REBENTITY_H

#include <Python.h>
#include <map>
#include "../Reb3D/Reb3d.h"
#include "../RebSupport/RebFileSystem.h"


class RebEntity
{
	PyObject * pep, *pmp;

public:
	RebEntity(RebFile * sf, std::string name, RebVector spos = RebVector(0, 0, 0), std::map<std::string, std::string> * initlist = 0);

	void SetPos(RebVector spos);
	void SetParam(std::string key, std::string value);
	
	void Update();

	RebVector GetPos();
	std::string GetParam(std::string key);
};


#endif