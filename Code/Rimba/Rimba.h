#pragma once
#include <Windows.h>
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"

#include "IGame.h"
#include "IWAEM.h"
#include "IRenderDevice.h"
#include "IGameLogic.h"


class Rimba
{
	HMODULE gamedll, glogicdll, waemdll, renderdll;

public:

	void LoadGameDLL(IGame ** game);

	void LoadModules(RebGDC * gdc);

	void ReleaseModules(RebGDC * gdc);

	void ReleaseGameDLL(IGame ** game);
};