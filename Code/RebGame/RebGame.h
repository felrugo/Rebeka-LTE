#ifndef REBGAME_H
#define REBGAME_H




#include "..\Rimba\Rimba.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebTimer.h"
#include "..\RebSupport\RebString.h"
#include "..\RebSupport\RebVL.h"

class RebGame : public IGame
{

	Rimba rimba;
	RebGDC gdc;

public:
	RebFileSystem * rfs;
	//bool gr;
	RebTimer rtimer;


void Init();

void GameLoop();

void Release();
};







#endif