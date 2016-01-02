#include "RebGL_LightSystem.h"



void ShadowMap::SetPos(RebVector set)
{
	lpos = set;
}



CSM::CSM()
{
	glGenFramebuffers(1, &sfbo);
	glBindFramebuffer(GL_FRAMEBUFFER, sfbo);

	
	glGenTextures(1, &st);

	glBindTexture(GL_TEXTURE_CUBE_MAP, st);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RG32F, 256, 256);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, st, 0);

	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void CSM::Write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, sfbo);
	glViewport(0, 0, 256, 256);
	GLuint db = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &db);
}

void CSM::Read()
{
	glActiveTextureARB(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, st);
	//GLenum en = glGetError();
}

void my_PerspectiveFOV(double fov, double aspect, double nears, double fars, float* mret) {
	double D2R = PI / 180.0;
	double yScale = 1.0 / tan(D2R * fov / 2);
	double xScale = yScale / aspect;
	double nearmfar = nears - fars;
	double m[] = {
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, (fars + nears) / nearmfar, -1,
		0, 0, 2 * fars*nears / nearmfar, 0
	};
	for (unsigned int i = 0; i < 16; i++)
	{
		mret[i] = (float)m[i];
	}
}

void CSM::ShadowPass()
{

	//shadowProgram.Use();
	//Write();
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//shadowProgram.Use();

	//glUniform3f(glGetUniformLocation(shadowProgram.GetHandle(), "ep"), lpos.x, lpos.y, lpos.z);

	//RebMatrix shadowmat, bias;
	//shadowmat.Identity();
	//shadowmat.Translate(-lpos.x, -lpos.y, -lpos.z);




	//bias.Identity();
	//bias.Perspective(90, 1, 1, 1000);


	///*	shadowmat.InverseOf(shadowmat);*/
	//float mm[16];
	//float bia[16];
	//SetCUBE(shadowProgram.GetHandle());


	//GLuint mmloc;

	//shadowmat.glm(mm);
	//mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "sm");
	//glUniformMatrix4fv(mmloc, 1, 0, mm);
	//bias.glm(mm);

	//my_PerspectiveFOV(90, 1, 1, 1000, bia);
	//mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "cm");
	//GLenum en = glGetError();
	//glUniformMatrix4fv(mmloc, 1, 0, bia);
	//en = glGetError();


	//for (UINT i3 = 0; i3 < ird->GetVertexCacheManager()->GetRVCs()->size(); i3++)
	//{


	//	for (UINT i = 0; i < ird->GetVertexCacheManager()->GetRVCs()->at(i3)->GetRVBs()->size(); i++)
	//	{
	//		if (ird->GetVertexCacheManager()->GetRVCs()->at(i3)->GetRVBs()->at(i)->isRenderable())
	//		{
	//			(*ird->GetVertexCacheManager()->GetRVCs()->at(i3)->GetRVBs()->at(i)->GetTrans() * *ird->GetVertexCacheManager()->GetRVCs()->at(i3)->GetTrans()).glm(mm);
	//			mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "mmat");
	//			glUniformMatrix4fv(mmloc, 1, 0, mm);
	//			ird->GetVertexCacheManager()->GetRVCs()->at(i3)->GetRVBs()->at(i)->Draw();
	//		}
	//	}
	//}



	//glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
}

CSM::~CSM()
{
	glDeleteTextures(1, &st);
	glDeleteFramebuffers(1, &sfbo);
}




void CSM::SetSParams(GLuint handle)
{
	RebMatrix pos;
	pos.Identity();
	pos.Translate(-lpos.x, -lpos.y, -lpos.z);

	GLuint locat = glGetUniformLocation(handle, "ep");
	glUniform3f(locat,lpos.x, lpos.y, lpos.z);


	RebMatrix cms[6];
	for (short i = 0; i < 6; i++)
	{
		cms[i].Identity();
	}
	cms[0]._13 = -1;
	cms[0]._22 = -1;
	cms[0]._31 = -1;
	cms[0]._11 = 0;
	cms[0]._33 = 0;
	cms[0] = pos * cms[0];

	cms[1]._13 = 1;
	cms[1]._22 = -1;
	cms[1]._31 = 1;
	cms[1]._11 = 0;
	cms[1]._33 = 0;
	cms[1] = pos * cms[1];

	cms[3]._11 = 1;
	cms[3]._23 = 1;
	cms[3]._32 = -1;
	cms[3]._22 = 0;
	cms[3]._33 = 0;
	cms[3] = pos * cms[3];

	cms[2]._11 = 1;
	cms[2]._23 = -1;
	cms[2]._32 = 1;
	cms[2]._22 = 0;
	cms[2]._33 = 0;
	cms[2] = pos * cms[2];

	cms[4]._11 = 1;
	cms[4]._22 = -1;
	cms[4]._33 = -1;
	cms[4] = pos * cms[4];

	cms[5]._11 = -1;
	cms[5]._22 = -1;
	cms[5]._33 = 1;
	cms[5] = pos * cms[5];

	for (short i = 0; i < 6; i++)
	{
		std::string cmname = "cm_mat[" + std::to_string(i) + "]";
		float mm[16];
		cms[i].glm(mm);
		GLuint locat = glGetUniformLocation(handle, cmname.c_str());
		glUniformMatrix4fv(locat, 1, 0, mm);
		GLenum en = glGetError();
	}

	for (short i = 0; i < 4; i++)
	{
		std::string cmname = "PProj";
		float mm[16];
		
		my_PerspectiveFOV(90.0, 1.0, 0.01, 1000.0, mm);

		GLuint locat = glGetUniformLocation(handle, cmname.c_str());
		glUniformMatrix4fv(locat, 1, 0, mm);
		GLenum en = glGetError();
	}


}



RebGLLight::RebGLLight(RebColor col, RebVector spos, float dp, float sp)
{
	color = col;
	pos = spos;
	diffpower = dp;
	specpower = sp;
	sm = new CSM();
	sm->SetPos(pos);
}


void RebGLLight::SetSParam(GLuint handle)
{
	GLuint loc = glGetUniformLocation(handle, "light.position");
	glUniform3f(loc, pos.x, pos.y, pos.z);

	loc = glGetUniformLocation(handle, "light.color");
	glUniform3f(loc, color.x, color.y, color.z);
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

CSM * RebGLLight::GetShadowMap()
{
	return sm;
}

RebGLLightSystem::RebGLLightSystem(RebGDC * sgdc)
{
	lights.clear();
	gdc = sgdc;
	
}


ILight * RebGLLightSystem::AddLight(RebColor col, RebVector spos)
{
	ILight * rl = new RebGLLight(col, spos);
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