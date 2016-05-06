#ifndef REBENTITYSYSTEM_H
#define REBENTITYSYSTEM_H

#include "RebEntity.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\tinyxml2.h"
#include <map>





class RebEntitySystem
{
	std::vector<RebEntity*> ents;
	RebGDC * gdc;

public:

	RebEntitySystem(RebGDC * sgd);

	RebEntity * CreateEntity(std::string type, std::string name);

	RebEntity * GetByName(std::string name);

	void DeleteEntity(RebEntity* todel);

	void UpdateAll();

	~RebEntitySystem();
};


#endif