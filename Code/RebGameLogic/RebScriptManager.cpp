#include "RebScriptManager.h"

RebScriptManager::RebScriptManager(RebGDC * sgdc)
{
	Py_Initialize();
	gdc = sgdc;
}