#ifndef REBENTITY_H
#define REBENTITY_H

#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "..\RebEntitySystem\IEntitySystem.h"
#include "..\RebSupport\RebString.h"
#include "..\Rimba\IRenderDevice.h"
#include "..\RebWindow\IMEH.h"
#include "..\RebSupport\RebParam.h"


class Entity;

class TemplateManager;

class Component
{
protected:
	Entity * parent;

	std::map<std::string, RebParam> Params;
public:
	virtual std::string GetType() = 0;

	Component() : parent(0) {};

	virtual std::string GetID()
	{
		return "BaseComponent";
	}

	virtual void update() {}

	void AddParams(std::map<std::string, RebParam> spars)
	{

		for(std::map<std::string, RebParam>::iterator it = spars.begin(); it != spars.end(); it++) {
			Params[it->first] = it->second;
		}
	}

	template <class T>
	void SetParam(std::string paramname, T paramvalue)
	{
		Params[paramname] = paramvalue;
	}

	RebParam GetParam(std::string paramname)
	{
		for(std::map<std::string, RebParam>::iterator it = Params.begin(); it != Params.end(); it++) {
			if(it->first == paramname)
			{
				return Params[paramname];
			}
		}
	}

	void SetOwner(Entity * so)
	{
		parent = so;
	}

	Entity * GetOwner()
	{
		return parent;
	}

	virtual ~Component() {}
};

class TComponent
{
public:

	std::map<std::string, RebString> TParams;

	virtual std::string GetID() = 0;


	virtual std::string GetType() = 0;

	virtual Component * MakeComponent(RebGDC * data) = 0;
};




class TEntity
{
	protected:
	std::string name;
	std::vector<TComponent*> temps;
	TEntity(std::string sname = "");
public:
	~TEntity();

	void SetName(std::string ID);

	std::string GetName();

	TComponent * GetTemplate(std::string ID);

	std::vector<TComponent*> * GetTComps();

	void AddTemplate(TComponent * atemp);

	void RemoveTemplate(TComponent * rtemp);

	virtual Entity * CastEntity(std::string ename, RebGDC * rgdc);

	void Clear();

	friend class TemplateManager;
};


class Entity : public IEntity
{
	friend class TEntity;
protected:

	TEntity * creator;

	RebVector pos;
	RebVector ori;
	std::string name;
	std::vector<Component*> comps;
	std::map<std::string, RebString> GParams;
public:
	Entity(std::string sname = "", RebVector spos = RebVector(0,0,0), RebVector sori = RebVector(0, 0, 0));

	void SetName(std::string sname);

	std::string GetName();

	void UpdateAllComps();

	RebVector GetPos();

	RebVector GetOri();

	void SetPos(RebVector spos);

	void SetOri(RebVector sori);

	~Entity();
};


#endif