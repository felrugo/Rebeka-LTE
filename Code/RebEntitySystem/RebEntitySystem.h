#ifndef REBENTITYSYSTEM_H
#define REBENTITYSYSTEM_H

#include "RebEntity.h"
#include "DefEnts.h"
#include "CompVisual.h"
#include "CompPhysics.h"
#include "CompInput.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\tinyxml2.h"
#include <map>
#include <thread>

class RebEntitySystem;

class TemplateManager
{
	std::vector<TEntity*> temps;
	std::vector<TComponent* (*)(std::string, RebGDC*)> CTFF;
	RebEntitySystem * res;
	bool Loaded;
public:
	TemplateManager(RebEntitySystem * sres);

	void LoadEntTemps();

	void LoadDef();

	static TComponent * BuiltinComps(std::string cn, RebGDC * GameData);

	TComponent * TCFactory(std::string compname);

	void AddTamplate(TEntity * toadd);

	TEntity * GetTemplate(std::string tname);

	Entity * CreateEntByTemp(std::string entname, std::string tempname);

	void CreateEntTemp(std::string tname, std::vector<TComponent*> tcomps); 

	~TemplateManager();

};



class RebEntitySystem : public IEntitySystem
{
	std::vector<Entity*> ents;
	TemplateManager * tm;
	bool runing;
	std::thread ut;
public:
	RebGDC * GameData;
	RebEntitySystem(RebGDC * sgd);

	void AddEntity(Entity * ent);
	
	TemplateManager * GetTemplateManager();

	Entity * GetEntity(std::string name);

	void Update();

	void Release();

	~RebEntitySystem();
};


#endif