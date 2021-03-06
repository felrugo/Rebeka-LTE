#include "CompVisual.h"


CompVisModel::CompVisModel(IRenderDevice * sird, RebFileSystem * srfs)
	{
		IRD = sird;
		rfs = srfs;
	}


void CompVisModel::LoadModel(std::string filename)
	{
		RebFile * mf = 
		IRD->GetVertexCacheManager()->CreateCacheFromFile(GetOwner()->GetID(), filename);
		rvc = IRD->GetVertexCacheManager()->GetVertexCache(GetOwner()->GetID());
	}

void CompVisModel::update()
{
	if(Params["isModelChanged"] == 1)
	{
		IRD->GetVertexCacheManager()->DeleteCache(rvc);
		LoadModel(Params["Model"]);
		Params["isModelChanged"] = 0;
	}
}


TCompVisModel::TCompVisModel()
	{
	}

CompVisViewport::CompVisViewport(IRenderDevice * SIRD)
{
	IRD = SIRD;
}

void CompVisViewport::update()
{
	if((CompVisViewport*)*IRD->GetViewportID() == this)
	{
		RebMatrix mt, mrx;
		mt.Identity();
		mrx.Identity();
		mt.Translate(-GetOwner()->GetPos().x, -GetOwner()->GetPos().y, -GetOwner()->GetPos().z);
		mrx.RotaWorld(-GetOwner()->GetOri().x, -GetOwner()->GetOri().y, -GetOwner()->GetOri().z);
		IRD->SetViewportMat(mt * mrx);
	}

}

void CompVisViewport::SetActiveViewport()
{
	*IRD->GetViewportID() = this;
}

TCompVisViewport::TCompVisViewport()
{
}