#ifndef REBENTITYSYSTEM_H
#define REBENTITYSYSTEM_H

#include <Python.h>
#include "RebEntity.h"
#include "..\RebSupport\RebGDC.h"
#include "../Rimba/IFileSystem.h"
#include "..\RebSupport\tinyxml2.h"
#include <map>





class RebEntitySystem : public IEntitySystem
{
	std::vector<RebEntity*> ents;
	RebGDC * gdc;

public:

	RebEntitySystem(RebGDC * sgd);

	RebEntity * CreateEntity(std::string type, std::string name, RebVector spos = RebVector(0, 0, 0), RebVector sori = RebVector(0, 0, 0), std::map<std::string, std::string> * initlist = 0);

	RebEntity * GetByName(std::string name);

	void DeleteEntity(RebEntity* todel);

	void UpdateAll();

	~RebEntitySystem();
};


#endif