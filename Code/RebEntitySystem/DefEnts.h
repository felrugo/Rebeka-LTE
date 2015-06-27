#ifndef DEFENTS
#define DEFENTS

#include "RebEntity.h"
#include "CompVisual.h"
#include "CompInput.h"


class TEntTerrain : public TEntity
{

public:
	TEntTerrain();

	~TEntTerrain();
};



class TEntFreeLookCamera : public TEntity
{
public:
	TEntFreeLookCamera();
};

#endif