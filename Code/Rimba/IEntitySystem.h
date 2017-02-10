#ifndef IENTITYSYSTEM_H
#define IENTITYSYSTEM_H




#include <string>
#include <vector>
#include "..\RebSupport\RebGDC.h"

class IEntity
{
public:
	virtual std::string GetName() = 0;

	virtual void Update() = 0;
};


class IEntitySystem
{
public:
	virtual void UpdateAll() = 0;
};
#endif