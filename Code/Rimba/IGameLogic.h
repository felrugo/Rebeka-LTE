#pragma once

#include "..\RebSupport\RebGDC.h"

class RebScriptImplementer
{
public:
	virtual int LoadModule() = 0;
};

class IScriptManager
{
public:
};

class IGameLogic
{
public:
	virtual void Update() = 0;
};


