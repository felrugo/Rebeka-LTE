#include "RebEntitySystem.h"


extern "C"
{
	void _declspec(dllexport) CreateEntitySystem(RebGDC * gdc)
	{
		gdc->res = new RebEntitySystem(gdc);
	}

	void _declspec(dllexport) ReleaseEntitySystem(RebGDC * gdc)
	{
		delete gdc->res;
		gdc->res = 0;
	}
}





//void TemplateManager::AddTamplate(TEntity * toadd)
//{
//	temps.push_back(toadd);
//}
//
//TEntity * TemplateManager::GetTemplate(std::string tname)
//{
//	for (unsigned int i = 0; i < temps.size(); i++)
//		{
//			if(temps[i]->GetName() == tname)
//			{
//				return temps[i];
//			}
//		}
//		return 0;
//}
//
//Entity * TemplateManager::CreateEntByTemp(std::string entname, std::string tempname)
//{
//	Entity * ret;
//	TEntity * te = GetTemplate(tempname);
//	if (te == 0)
//	{
//		return 0;
//	}
//	ret = te->CastEntity(entname, res->GameData);
//	res->AddEntity(ret);
//	return ret;
//}
//
//
//
//void TemplateManager::CreateEntTemp(std::string tname, std::vector<TComponent*> tcomps)
//{
//	TEntity* nte = new TEntity(tname);
//	nte->temps = tcomps;
//	temps.push_back(nte);
//}
//
//
//TComponent * TemplateManager::BuiltinComps(std::string cn, RebGDC * GameData)
//{
//	TComponent * ret = 0;
//	if(cn == "CompVisModel")
//		ret = new TCompVisModel();
//	if(cn == "CompVisTerrain")
//		ret = new TCompVisTerrain();
//		return ret;
//}
//
//TComponent * TemplateManager::TCFactory(std::string compname)
//{
//	TComponent * ret = 0;
//	for (unsigned int i = 0; i < CTFF.size(); i++)
//	{
//		ret = CTFF[i](compname, res->GameData);
//	}
//	return ret;
//}
//
//
//TemplateManager::TemplateManager(RebEntitySystem * sres)
//{
//	Loaded = false;
//	res = sres;
//	temps.clear();
//	CTFF.clear();
//	CTFF.push_back(BuiltinComps);
//	LoadDef();
//	LoadEntTemps();
//}
//
//
//
//void TemplateManager::LoadDef()
//{
//	TEntity * ter = new TEntTerrain();
//	temps.push_back(ter);
//	ter = new TEntFreeLookCamera();
//	temps.push_back(ter);
//	
//}
//
//void TemplateManager::LoadEntTemps()
//{
//	tinyxml2::XMLDocument xd;
//
//	RebDir * entdir = res->GameData->rfs->SearchDir("Entities")[0];
//	std::vector<RebFile*> entfiles = entdir->GetAllFiles();
//
//	for (unsigned int i = 0; i < entfiles.size(); i++)
//	{
//		if (entfiles[i]->GetExtension() == ".xml")
//		{
//			xd.LoadFile(entfiles[i]->GetAPath().c_str());
//			std::string name = xd.FirstChild()->ToElement()->Attribute("name");
//			TEntity * nt = new TEntity(name);
//			tinyxml2::XMLNode * xn = xd.FirstChild()->FirstChild();
//			while (xn->ToElement()->Name() == std::string("Component"))
//			{
//				tinyxml2::XMLElement * xe = xn->ToElement()->FirstChildElement();
//				std::string compn = xn->ToElement()->Attribute("name");
//				TComponent * tc = TCFactory(compn);
//				if (tc == 0) break;
//				while (xe->Name() == std::string("Param"))
//				{
//					tc->TParams[xe->Attribute("name")] = xe->Attribute("value");
//					xe = xe->NextSiblingElement();
//					if (xe == 0)
//						break;
//				}
//				nt->AddTemplate(tc);
//				xn = xn->NextSibling();
//				if (xn == 0)
//					break;
//			}
//			temps.push_back(nt);
//		}
//	}
//}
//
//
//TemplateManager::~TemplateManager()
//{
//	for (unsigned int i = 0; i < temps.size(); i++)
//	{
//		delete temps[i];
//	}
//	temps.clear();
//
//	CTFF.clear();
//}

#include "../RebSupport/RebMatcher.h"
RebEntitySystem::RebEntitySystem(RebGDC * sgd)
{
	ents.clear();
	gdc = sgd;
	RebEntity * nc = CreateEntity("RebPlayer", "Player1");

	std::string getn = nc->GetParam("name");

	bool res = AdvencedMatch("", "asdbcdsdf");

}

RebEntity * RebEntitySystem::CreateEntity(std::string type, std::string name, RebVector spos, RebVector sori, std::map<std::string, std::string> * initlist)
{
	for (size_t i = 0; i < ents.size(); i++)
	{
		if (ents[i]->GetName() == name)
		{
			throw "Name used";
		}
	}

	RebDir * entdir = gdc->rfs->SearchDir("Entities")[0];
	RebFile * rf = entdir->Search(type + ".py")[0];

	RebEntity * ne = new RebEntity(rf, name, spos, sori, initlist);
	ents.push_back(ne);
	return ne;
}

RebEntity * RebEntitySystem::GetByName(std::string name)
{
	for (size_t i = 0; i < ents.size(); i++)
	{
		if (ents[i]->GetName() == name)
		{
			return ents[i];
		}
	}
	return 0;
}

void RebEntitySystem::DeleteEntity(RebEntity* todel)
{
	for (size_t i = 0; i < ents.size(); i++)
	{
		if (ents[i] == todel)
		{
			delete ents[i];
			ents.erase(ents.begin() + i);
		}
	}
}

void RebEntitySystem::UpdateAll()
{
	for (size_t i = 0; i < ents.size(); i++)
	{
		ents[i]->Update();
	}
}

RebEntitySystem::~RebEntitySystem()
{
	for (size_t i = 0; i < ents.size(); i++)
	{
			delete ents[i];
	}
	ents.clear();
}