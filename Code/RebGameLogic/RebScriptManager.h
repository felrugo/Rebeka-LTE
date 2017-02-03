#pragma once
#include "../Rimba/IFileSystem.h"
#include "../RebSupport/RebGDC.h"


extern RebGDC * ggdc;

class RebScript
{
	IFile * file;
public:
};


class RebScriptManager
{
	RebGDC * gdc;
	void LoadBIF();
public:
	RebScriptManager(RebGDC * sgdc);
};
