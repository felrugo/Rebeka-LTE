#include "DefEnts.h"



TEntTerrain::TEntTerrain()
{
	name = "Terrain";
	TComponent * tc = new TCompVisTerrain();
	temps.push_back(tc);
}


TEntFreeLookCamera::TEntFreeLookCamera()
{
	name = "FreeLookCamera";
	TComponent * tc = new TCompVisViewport();
	temps.push_back(tc);
	tc = new TCompInpBasicControl();
	temps.push_back(tc);
}


