#ifndef REBGAME_H
#define REBGAME_H



#include "IGame.h"
#include "../RebGL/IRenderDevice.h"
#include "..\RebWindow\IWindowManager.h"
#include "..\RebWindow\IMEH.h"
#include "..\RebAudio\IAudioDevice.h"
#include "..\RebEntitySystem\IEntitySystem.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebTimer.h"
#include "..\RebSupport\RebString.h"
#include "..\RebSupport\RebVL.h"

class RebGame : public IGame
{
public:
	
	IAudioDevice * iad;
	IWindowManager * winm;
	IMEH * meh;
	IRenderDevice * rd;
	IEntitySystem * ies;
	RebFileSystem * rfs;
	void * window;
	bool gr;
	RebTimer rtimer;

RebGDC * mGDC;


void Init();

void GameLoop();

void Release();
};







#endif