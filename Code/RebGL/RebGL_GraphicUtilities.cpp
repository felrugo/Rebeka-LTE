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

	//GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	//glDrawBuffersARB(3, DrawBuffers);



}


void RebGBuffer::Write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 1280, 720);
	// glMatrixMode( GL_PROJECTION );
	//    glLoadIdentity( );
	// 
	//	GLfloat ratio;
	//	ratio = ( GLfloat )1280 / ( GLfloat )720;
	//    /* Set our perspective */
	//    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, DrawBuffers);

}

void RebGBuffer::Read()
{
	//glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	//glViewport(0,0,1280,720);
	for (int i = 0; i < 3; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
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




RebOPCSM::RebOPCSM()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);


	glGenTextures(1, &cma);
	

		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cma);

		glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_RGBA32F, 128, 128, 6 * 64);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cma, 0);

	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RebOPCSM::Write(char to)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 128, 128);
	GLuint db = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &db);
}



void RebOPCSM::Read()
{
	glActiveTextureARB(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cma);
}


RebOPCSM::~RebOPCSM()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteTextures(1, &cma);
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