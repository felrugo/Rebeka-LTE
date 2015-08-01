#include "RebGL_LightSystem.h"


RebGLLight::RebGLLight(RebColor col, RebVector spos, LightType slt, RebVector spotlookat, RebGDC * gdc, float dp, float sp)
{
	view.Identity();
	color = col;
	pos = spos;
	diffpower = dp;
	specpower = sp;
	lt = slt;
	if (lt == LT_POINT)
	{
		sm = new ShadowMapCube(gdc);
	}
	else
	{
		sm = new ShadowMap2D(gdc);
	}
	sm->SetPos(pos);
}




void RebGLLight::SetPos(RebVector spos)
{
	pos = spos;
	sm->SetPos(pos);
}

RebVector RebGLLight::GetPos()
{
	return pos;
}

RebVector RebGLLight::GetColor()
{
	return color;
}

RebMatrix * RebGLLight::GetViewm()
{
	return &view;
}

bool RebGLLight::GetSop()
{
	return (bool)lt;
}

ShadowMap * RebGLLight::GetShadowMap()
{
	return sm;
}

RebGLLightSystem::RebGLLightSystem(RebGDC * sgdc)
{
	lights.clear();
	gdc = sgdc;
	
}


ILight * RebGLLightSystem::AddLight(RebColor col, RebVector spos, LightType lt, RebVector spotlookat)
{
	ILight * rl = new RebGLLight(col, spos, lt, spotlookat, gdc);
	lights.push_back(rl);
	return rl;
}

void RebGLLightSystem::DeleteLight(ILight * todel)
{
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		if (lights[i] == todel)
		delete lights[i];
	}
}

std::vector<ILight*> * RebGLLightSystem::GetLights()
{
	return &lights;
}

void RebGLLightSystem::SendLDtoShader(unsigned int handle)
{
	GLuint loc;
	loc = glGetUniformLocation(handle, "num_lights");
	glUniform1ui(loc, lights.size());
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		loc = glGetUniformLocation(handle, std::string("light[" + std::to_string(i) + "].position").c_str());
		glUniform3f(loc, lights[i]->GetPos().x, lights[i]->GetPos().y, lights[i]->GetPos().z);
		loc = glGetUniformLocation(handle, std::string("light[" + std::to_string(i) + "].color").c_str());
		glUniform3f(loc, lights[i]->GetColor().x, lights[i]->GetColor().y, lights[i]->GetColor().z);

	}
}


RebGLLightSystem::~RebGLLightSystem()
{
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		delete lights[i];
	}
	lights.clear();
}