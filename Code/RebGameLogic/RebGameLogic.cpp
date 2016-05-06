#include "RebGameLogic.h"

extern "C"
{
	void _declspec(dllexport) CreateGameLogic(RebGDC * gdc)
	{
		gdc->rlogic = new RebGameLogic(gdc);
	}

	void _declspec(dllexport) ReleaseGameLogic(RebGDC * gdc)
	{
		delete gdc->rlogic;
		gdc->rlogic = 0;
	}
}


RebGameLogic::RebGameLogic(RebGDC * set)
{
	data = set;
	rsm = new RebScriptManager(data);
}

RebGameLogic::~RebGameLogic()
{
	delete rsm;
}