#include "RebGameLogic.h"
#include "../Rimba/IEntitySystem.h"

extern "C"
{
	void _declspec(dllexport) CreateGameLogic(RebGDC * gdc)
	{
		gdc->gl = new RebGameLogic(gdc);
	}

	void _declspec(dllexport) ReleaseGameLogic(RebGDC * gdc)
	{
		delete gdc->gl;
		gdc->gl = 0;
	}
}


RebGameLogic::RebGameLogic(RebGDC * set)
{
	data = set;
	rsm = new RebScriptManager(data);
}


void RebGameLogic::Update()
{
	data->res->UpdateAll();
}


RebGameLogic::~RebGameLogic()
{
	delete rsm;
}