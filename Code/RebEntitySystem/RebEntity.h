#ifndef REBENTITY_H
#define REBENTITY_H

#include <Python.h>
#include <map>
#include <fstream>
#include "../Rimba/IEntitySystem.h"
#include "../RebSupport/RebGDC.h"
#include "../Reb3D/Reb3d.h"
#include "../RebSupport/RebFileSystem.h"


class RebEntity : public IEntity
{
	PyObject * pep;
	std::string name;

public:
	RebEntity(RebFile * sf, std::string name, RebVector spos, RebVector sori, std::map<std::string, std::string> * initlist);

	void SetPos(RebVector spos);
	void SetOri(RebVector sori);
	void SetParam(std::string key, std::string value);
	
	void Update();

	RebVector GetPos();
	std::string GetName();
	std::string GetParam(std::string key);
};


#endif