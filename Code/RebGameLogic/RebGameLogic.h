#ifndef REBGAMELOGIC_H
#define REBGAMELOGIC_H

#include "..\RebSupport\RebGDC.h"


class RebGameLogic
{
	RebGDC * data;
public:
	void Init(RebGDC * set);
	void Release();
};






#endif