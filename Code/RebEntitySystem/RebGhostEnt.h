#pragma once
#include "../Rimba/IEntitySystem.h"
#include "../Rimba/IRenderDevice.h"
#include "../Rimba/IWAEM.h"
#include "../Reb3D/Reb3d.h"

class RebGhostEnt : public IEntity, public IMouseEventListener
{
	RebVector pos;
	RebVector ori;
	RebGDC * gdc;

public:
	RebGhostEnt(RebGDC * gdc)
	{
		this->gdc = gdc;
		pos = ori = RebVector(0, 0, 0);
		gdc->waem->RegisterMouseEventListener(this);
	}

	void Update()
	{
		RebMatrix rm;
		rm.RotaWorld(ori.x, ori.y, ori.z);
		gdc->rd->SetViewportMat(rm);
	}

	std::string GetName()
	{
		return "Ghost1";
	}

	void onEvent(IMouseEvent * ev)
	{
		ori += RebVector(ev->GetRel().y, ev->GetRel().x, 0.0);
	}
};