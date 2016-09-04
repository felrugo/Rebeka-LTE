#ifndef REBGAME_H
#define REBGAME_H




#include "..\Rimba\Rimba.h"
#include "../Rimba/IFileSystem.h"
#include "..\RebSupport\RebTimer.h"

class RebGame : public IGame
{

	Rimba rimba;
	RebGDC gdc;

public:
	IFileSystem * rfs;
	//bool gr;
	RebTimer rtimer;


void Init();

void GameLoop();

void Release();
};







#endif