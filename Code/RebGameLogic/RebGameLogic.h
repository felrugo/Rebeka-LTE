#ifndef REBGAMELOGIC_H
#define REBGAMELOGIC_H

#include "..\Rimba\IGameLogic.h"
#include "RebScriptManager.h"





class RebGameLogic : public IGameLogic
{
	RebGDC * data;
	RebScriptManager * rsm;
public:
	RebGameLogic(RebGDC * set);
	IScriptManager * GetISM();
	
	void Update();


	~RebGameLogic();
};






#endif