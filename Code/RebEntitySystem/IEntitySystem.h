#ifndef IENTITYSYSTEM_H
#define IENTITYSYSTEM_H

#ifdef REBENTITYSYSTEM_H
#define REBENTITYSYSTEMAPI __declspec(dllexport)
#else
#define REBENTITYSYSTEMAPI __declspec(dllimport)
#endif


#include <string>
#include <vector>
#include "..\RebSupport\RebGDC.h"

class IEntity
{
public:

};


class IEntitySystem
{
public:


	
	virtual IEntity * GetEntity(std::string name) = 0;

	virtual void Update() = 0;

	virtual void Release() = 0;

	~IEntitySystem() {}
};

REBENTITYSYSTEMAPI void CreateEntitySystem(IEntitySystem **IES, RebGDC * data);

REBENTITYSYSTEMAPI void ReleaseEntitySystem(IEntitySystem **IES);

#endif