#ifndef REBUISYSTEM_H
#define REBUISYSTEM_H

#include "../Rimba/IWAEM.h"
#include "../Rimba/IUISystem.h"
#include "RebUIElements.h"
#include "RebUIComponents.h"




class RebUISystem : public IUISystem
{
	RebGDC * gdc;
	RebScreen screen;

public:
	RebUISystem(RebGDC * gdc);

	RebGDC * GetGDC();

	unsigned int RenderUI();
};





#endif