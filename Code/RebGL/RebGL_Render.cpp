#include "RebGL.h"



void RebGL::FirstPassTest()
{
	gbuff->Write();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RebGLShaderProgram * FirstPassProg = rss->GetFromBank("FirstPass");
	FirstPassProg->Use();

	float mm[16];
	RebMatrix rm;
	rm.Identity();
	rm.glm(mm);
	GLuint mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "mmat");
	glUniformMatrix4fv(mmloc, 1, 0, mm);
	GetViewportMat().glm(mm);
	mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "viewmat");
	glUniformMatrix4fv(mmloc, 1, 0, mm);
	glUniform1i(glGetUniformLocation(FirstPassProg->GetHandle(), "difftext"), 0);
	projmat.glm(mm);
	mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "projmat");
	glUniformMatrix4fv(mmloc, 1, 0, mm);


	GLuint vai = glGetAttribLocation(FirstPassProg->GetHandle(), "vpos");



	glBegin(GL_TRIANGLES);
	glVertexAttrib3f(vai, -1.0f, -1.0f, 0.0f);
	glVertexAttrib3f(vai, 0.0f, 1.0f, 0.0f);
	glVertexAttrib3f(vai, 1.0f, -1.0f, 0.0f);
	glEnd();

	glDisable(GL_DEPTH_TEST);
}

//Geometry Pass stage
void RebGL::FirstPass()
{
	gbuff->Write();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TerrainRender();


	RebGLShaderProgram * FirstPassProg = rss->GetFromBank("FirstPass");
	FirstPassProg->Use();

	//Set Projection Matrix
	float mm[16];
	GLuint mmloc;
	projmat.glm(mm);
	mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "projmat");
	glUniformMatrix4fv(mmloc, 1, 0, mm);


	for (std::vector<IVertexCache*>::iterator vit = rvcm->GetRVCs()->begin(); vit != rvcm->GetRVCs()->end(); vit++)
	{
		

		for (std::vector<IVertexBuffer*>::iterator bit = (*vit)->GetRVBs()->begin(); bit != (*vit)->GetRVBs()->end(); bit++)
		{
			if ((*bit)->isRenderable())
			{
			
				//SETUP UNIFORMS

				float mm[16];
				(*(*vit)->GetTrans() * *(*bit)->GetTrans()).glm(mm);

				GLuint mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "mmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);
				GetViewportMat().glm(mm);
				mmloc = glGetUniformLocation(FirstPassProg->GetHandle(), "viewmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);
				glUniform1i(glGetUniformLocation(FirstPassProg->GetHandle(), "difftext"), 0);

				//SETUP MATERIAL
				(*bit)->GetMaterial()->Bind();
				//DRAW
				RebDrawInfo di;
				di.vai = glGetAttribLocation(FirstPassProg->GetHandle(), "vpos");
				di.nai = glGetAttribLocation(FirstPassProg->GetHandle(), "vnor");
				di.tai = glGetAttribLocation(FirstPassProg->GetHandle(), "vtex");
				for (int i = 0; i < 3; i++)
					di.enabled[i] = true;

				dynamic_cast<RebGLVertexBuffer*>(*bit)->Draw(di);
			}
		}
	}

	glDisable(GL_DEPTH_TEST);
}




void RebGL::ShadowPass()
{
	RebGLShaderProgram * ShadowPass = rss->GetFromBank("ShadowPass");
	ShadowPass->Use();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	for (std::vector<ILight*>::iterator it = rls->GetLights()->begin(); it < rls->GetLights()->end(); it++)
	{
		((RebGLLight*)(*it))->GetShadowMap()->Write();
		((RebGLLight*)(*it))->GetShadowMap()->SetSParams(ShadowPass->GetHandle());

		glClear(GL_COLOR_BUFFER_BIT);
		glCullFace(GL_FRONT);



		for (std::vector<IVertexCache*>::iterator vit = rvcm->GetRVCs()->begin(); vit != rvcm->GetRVCs()->end(); vit++)
		{

			for (std::vector<IVertexBuffer*>::iterator bit = (*vit)->GetRVBs()->begin(); bit != (*vit)->GetRVBs()->end(); bit++)
			{
				if ((*bit)->isRenderable())
				{
					float mm[16];
					(*(*vit)->GetTrans() * *(*bit)->GetTrans()).glm(mm);

					GLuint mmloc = glGetUniformLocation(ShadowPass->GetHandle(), "mmat");
					glUniformMatrix4fv(mmloc, 1, 0, mm);
					RebDrawInfo di;
					di.vai = glGetAttribLocation(ShadowPass->GetHandle(), "vpos");
					di.enabled[0] = true;
					dynamic_cast<RebGLVertexBuffer*>(*bit)->Draw(di);
				}
			}
		}
	}

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

}

//LightPass
void RebGL::LightPass()
{
	rpp->BindToDraw();

	RebGLShaderProgram * LightPassProg = rss->GetFromBank("LightPass");
	LightPassProg->Use();
	glUniform1i(glGetUniformLocationARB(LightPassProg->GetHandle(), "color"), 0);
	glUniform1i(glGetUniformLocationARB(LightPassProg->GetHandle(), "pos"), 1);
	glUniform1i(glGetUniformLocationARB(LightPassProg->GetHandle(), "norm"), 2);
	glUniform1i(glGetUniformLocationARB(LightPassProg->GetHandle(), "csm"), 3);
	
	gbuff->Read();
	

	/*glBindFramebuffer(GL_FRAMEBUFFER, ppfb);
	glViewport(0, 0, 1280, 720);
	GLuint db = GL_COLOR_ATTACHMENT0 + mbi;
	glDrawBuffers(1, &db);*/

	


	/*RebMatrix shadowmat, sha, res, bias;
	shadowmat.Identity();
	shadowmat.Translate(0, -10, 0);

	sha.Identity();
	sha.RotyByDeg(90, 0, 0);

	bias.Identity();
	bias.Perspective(90, 1, 1, 1000);


	res = shadowmat * sha;

	glUniform1i(glGetUniformLocationARB(lightProgram.GetHandle(), "shadowsum"), 3);

	ss.Read();*/


	/*float mm[16];
	res.glm(mm);
	glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "sm"), 1, 0, mm);

	bias.glm(mm);

	glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "cm"), 1, 0, mm);*/
	

	((RebGLLight*)rls->GetLights()->at(0))->GetShadowMap()->Read();
	((RebGLLight*)rls->GetLights()->at(0))->SetSParam(LightPassProg->GetHandle());
	

	//gbuff->bind(LightPassProg->GetHandle());

	/*GLuint nl = glGetUniformLocation(lightProgram.GetHandle(), "num_lights");
	glUniform1ui(nl, ls->GetLights()->size());

	for (unsigned int i = 0; i < ls->GetLights()->size(); i++)
	{
	GLuint nl2 = glGetUniformLocation(lightProgram.GetHandle(), std::string("light[" + std::to_string(i) + "].position").c_str());
	RebVector lpos;
	glUniform3f(nl2, ls->GetLights()->at(i)->GetPos().x, ls->GetLights()->at(i)->GetPos().y, ls->GetLights()->at(i)->GetPos().z);
	GLuint nl3 = glGetUniformLocation(lightProgram.GetHandle(), std::string("light[" + std::to_string(i) + "].color").c_str());
	glUniform3f(nl3, ls->GetLights()->at(i)->GetColor().x, ls->GetLights()->at(i)->GetColor().y, ls->GetLights()->at(i)->GetColor().z);
	}*/

	//rls->SendLDtoShader(LightPassProg->GetHandle());




	RebVector mmv(0, 0, 0);
	RebMatrix test;
	test.InverseOf(GetViewportMat());
	mmv = mmv * test;

	glUniform3f(glGetUniformLocation(LightPassProg->GetHandle(), "mmv"), mmv.x, mmv.y, mmv.z);

	//glUniform1i(glGetUniformLocation(ppprog.GetHandle(), "mbi"), mbi);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 1280, 720);

	GLuint vai = glGetAttribLocation(LightPassProg->GetHandle(), "vpos");

	glColor4f(1, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertexAttrib3f(vai, -1.0f, -1.0f, 0.0f);
	glVertexAttrib3f(vai, -1.0f, 1.0f, 0.0f);
	glVertexAttrib3f(vai, 1.0f, 1.0f, 0.0f);
	glVertexAttrib3f(vai, 1.0f, -1.0f, 0.0f);
	glEnd();


	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RebGL::PostProcess()
{
	rpp->RenderOut();
}