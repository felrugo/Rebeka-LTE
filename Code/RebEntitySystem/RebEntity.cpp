#include "RebEntity.h"


TEntity::TEntity(std::string sname)
{
	temps.clear();
	name = sname;
}

	TEntity::~TEntity()
	{
			Clear();
	}

	void TEntity::SetName(std::string ID)
	{
		name = ID;
	}

	std::string TEntity::GetName()
	{
		return name;
	}

	TComponent * TEntity::GetTemplate(std::string ID)
	{
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			if(temps[i]->GetID() == ID)
			{
				return temps[i];
			}
		}
		return 0;
	}

	void TEntity::AddTemplate(TComponent * atemp)
	{
		temps.push_back(atemp);
	}


	void TEntity::RemoveTemplate(TComponent * rtemp)
	{
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			if (temps[i] == rtemp)
				delete temps[i];
		}
	}

	Entity * TEntity::CastEntity(std::string ename, RebGDC * rgdc)
	{
		Entity * ent = new Entity(ename);
		ent->creator = this;
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			ent->comps.push_back(temps[i]->MakeComponent(rgdc));
		}
		return ent;
	}



	void TEntity::Clear()
	{
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			delete temps[i];
		}
		temps.clear();
	}
	
	std::vector<TComponent*> * TEntity::GetTComps()
	{
		return &temps;
	}



	Entity::Entity(std::string sname, RebVector spos, RebVector sori)
	{
		name = sname;
		pos = spos;
		ori = sori;
		creator = NULL;
		comps.clear();
	}

	void Entity::SetName(std::string sname)
	{
		name = sname;
	}

	std::string Entity::GetName()
	{
		return name;
	}

	void Entity::UpdateAllComps()
	{
		for(unsigned int i = 0; i < comps.size(); i++)
		{
			comps[i]->update();
		}
	}

	RebVector Entity::GetPos()
	{
		return pos;
	}

	RebVector Entity::GetOri()
	{
		return ori;
	}

	void Entity::SetPos(RebVector spos)
	{
		pos = spos;
	}

	void Entity::SetOri(RebVector sori)
	{
		ori.x = std::fmod(sori.x, 360);
		ori.y = std::fmod(sori.y, 360);
		ori.z = std::fmod(sori.z, 360);
	}

	Entity::~Entity()
	{
		for (unsigned int i = 0; i < comps.size(); i++)
		{
			delete comps[i];
		}
		comps.clear();
	}