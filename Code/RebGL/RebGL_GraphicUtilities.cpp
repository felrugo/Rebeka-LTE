#include "RebGL_GraphicUtilities.h"


RebGBuffer::RebGBuffer()
{


	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(3, texts);
	for (int i = 0; i < 3; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texts[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, 1280, 720, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTextureARB(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, texts[i], 0);
	}

	GLuint depthrenderbuffer;
	glGenRenderbuffersEXT(1, &depthrenderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffersARB(3, DrawBuffers);



}


void RebGBuffer::Write()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 1280, 720);
	// glMatrixMode( GL_PROJECTION );
	//    glLoadIdentity( );
	// 
	//	GLfloat ratio;
	//	ratio = ( GLfloat )1280 / ( GLfloat )720;
	//    /* Set our perspective */
	//    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffersARB(3, DrawBuffers);

}

void RebGBuffer::Read()
{
	//glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	//glViewport(0,0,1280,720);
	for (int i = 0; i < 3; i++)
	{
		glActiveTextureARB(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texts[i]);
	}
}

int RebGBuffer::GetPostex()
{
	return texts[1];
}

void RebGBuffer::bind(GLuint handle)
{
	GLuint loc = glGetUniformLocationARB(handle, "color");
	glUniform1i(loc, 0);
	loc = glGetUniformLocationARB(handle, "pos");
	glUniform1i(loc, 1);
	loc = glGetUniformLocationARB(handle, "norm");
	glUniform1i(loc, 2);
}

RebGBuffer::~RebGBuffer()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	//glViewport(0,0,1280,720);
	// glMatrixMode( GL_PROJECTION );
	//    glLoadIdentity( );
	// 
	//	GLfloat ratio;
	//	ratio = ( GLfloat )1280 / ( GLfloat )720;
	//    /* Set our perspective */
	//    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	glDeleteTextures(3, texts);
	glDeleteFramebuffersEXT(1, &fbo);
}




ShadowSum::ShadowSum(RebGDC * rgdc)
{
	ls = (RebGLLightSystem*)rgdc->rd->GetLightSystem();

	ssum.AddShaderFile(rgdc->rfs->Search("ShadowSumV.rvs", "Shaders"));
	ssum.AddShaderFile(rgdc->rfs->Search("ShadowSum.rfs", "Shaders"));
	ssum.Link();

	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);



	glGenRenderbuffersEXT(1, &depthrenderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glGenTextures(2, shadsum);
	for (char a = 0; a < 2; a++)
	{

		glBindTexture(GL_TEXTURE_2D, shadsum[a]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 1280, 720, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + a, shadsum[a], 0);
	}

	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ShadowSum::Write(char to)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 1280, 720);
	GLuint db = GL_COLOR_ATTACHMENT0 + to;
	glDrawBuffers(1, &db);
}


void ShadowSum::PassRandomPCF()
{
	/*for (size_t i = 0; i < 15; i++)
	{
		srand(time(NULL));
		std::string name = "randseed[" + std::to_string(i) + "]";
		float rs[2];
		rs[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (float)Reb2PI;
		rs[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)* 0.005f;
		glUniform2fv(glGetUniformLocation(ssum.GetHandle(), name.c_str()), 1, rs);
	}*/
}


void ShadowSum::SumShadows(int postexid)
{

	ssum.Use();



	for (unsigned int i = 0; i < ls->GetLights()->size(); i++)
	{
		GLenum en = glGetError();

		RebGLLight * cur = (RebGLLight*)ls->GetLights()->at(i);
		cur->GetShadowMap()->ShadowPass();
		en = glGetError();

		ssum.Use();



		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "postex"), 0);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "shad2d"), 1);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "shadcube"), 2);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "prev"), 3);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, postexid);

		cur->GetShadowMap()->Read();

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, shadsum[!(bool)(i % 2)]);


		//PassRandomPCF();

		glUniform3f(glGetUniformLocation(ssum.GetHandle(), "lightpos"), cur->GetPos().x, cur->GetPos().y, cur->GetPos().z);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "first"), i < 1);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "sop"), cur->GetSop());

		Write(i % 2);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2f(1, -1);
		glVertex3f(1, -1, 0);
		glTexCoord2f(-1, -1);
		glVertex3f(-1, -1, 0);
		glTexCoord2f(-1, 1);
		glVertex3f(-1, 1, 0);
		glEnd();
	}
}

void ShadowSum::Read()
{
	glActiveTextureARB(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, shadsum[(ls->GetLights()->size() - 1) % 2]);
}


ShadowSum::~ShadowSum()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteTextures(2, shadsum);
	glDeleteRenderbuffers(1, &depthrenderbuffer);
	glDeleteFramebuffers(1, &fbo);
}



RebMotionBlur::RebMotionBlur()
{
	cur = 0;
	w = 1280;
	h = 720;

	glGenFramebuffersEXT(1, &mbfb);
	glBindFramebufferEXT(GL_FRAMEBUFFER, mbfb);

	glGenTextures(8, mbt);
	for (int i = 0; i < 8; i++)
	{
		glBindTexture(GL_TEXTURE_2D, mbt[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, w, h, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTextureARB(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, mbt[i], 0);
	}

	
}


void RebMotionBlur::SetRes(int sw, int sh)
{
	w = sw;
	h = sh;
}

void RebMotionBlur::SetLevel(unsigned short sl)
{
	level = sl;
}

void RebMotionBlur::GetAvailable()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, mbfb);
}

void RebMotionBlur::Bind(GLuint handle)
{

}

RebMotionBlur::~RebMotionBlur()
{

}