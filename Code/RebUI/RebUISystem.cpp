#include "RebUISystem.h"


extern "C"
{
	void _declspec(dllexport) CreateUISystem(RebGDC * gdc)
	{
		gdc->uis = new RebUISystem(gdc);
	}

	void _declspec(dllexport) ReleaseUISystem(RebGDC * gdc)
	{
		delete gdc->uis;
		gdc->uis = 0;
	}
}


RebUISystem::RebUISystem(RebGDC * gdc) : gdc(gdc), screen(this)
{
	
}


RebGDC * RebUISystem::GetGDC()
{
	return gdc;
}



unsigned int RebUISystem::RenderUI()
{

	return 0;
}