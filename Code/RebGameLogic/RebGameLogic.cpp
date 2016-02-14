#include "RebGameLogic.h"


void _declspec(dllexport) CreateGameLogic(RebGDC * gdc)
{
	gdc->rlogic = new RebGameLogic(gdc);
}

void _declspec(dllexport) ReleaseGameLogic(RebGDC * gdc)
{
	delete gdc->rlogic;
}



RebGameLogic::RebGameLogic(RebGDC * set)
{
	data = set;
}