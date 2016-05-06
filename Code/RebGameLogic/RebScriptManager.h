#pragma once
#include "../RebSupport/RebFileSystem.h"
#include "RSBIF.h"


class RebScript
{
	RebFile * file;
public:
};


class RebScriptManager
{
	RebGDC * gdc;
	void LoadBIF();
public:
	RebScriptManager(RebGDC * sgdc);
};
