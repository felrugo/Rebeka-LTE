#include "RebEntitySystem.h"






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



RebEntitySystem::RebEntitySystem(RebGDC * sgd)
{
	ents.clear();
	gdc = sgd;
}

RebEntity * RebEntitySystem::CreateEntity(std::string type, std::string name)
{

}

RebEntity * RebEntitySystem::GetByName(std::string name)
{

}

void RebEntitySystem::DeleteEntity(RebEntity* todel)
{

}

void RebEntitySystem::UpdateAll()
{

}

RebEntitySystem::~RebEntitySystem()
{

}