#include "RebGL.h"

extern "C"
{

	__declspec(dllexport) void CreateRebGL(RebGDC * gdc)
	{
		gdc->rd = new RebGL(gdc);
	}

	__declspec(dllexport) void ReleaseRebGL(RebGDC * gdc)
	{
		delete gdc->rd;
		gdc->rd = NULL;
	}

}



RebGL::RebGL(RebGDC * gd)
{
	gdc = gd;

	skinman = new RebGLSkinManager(gdc->rfs);

	rvcm = new RebVertexCacheManager(gd->rfs, skinman);

	rss = new RebShaderSystem(gdc);

	rls = new RebGLLightSystem(gdc);

	rge = new RebEnv();

	//Init utis

	int w, h;
	gdc->window->GetClientSize(&w, &h);

	gbuff = new RebGBuffer();
	ropcsm = new RebOPCSM();
	rpp = new RebPostProcessor(rss, gdc, 4, w, h);

	




	rls->AddLight(RebColor(1, 1, 1), RebVector(0.0, 10.0, 0.0));



	glShadeModel(GL_SMOOTH);
	/* Set the background black */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Depth buffer setup */
	glClearDepth(1.0f);

	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	projmat.Identity();
	projmat.Perspective(45.0, float(w) / float(h), 0.1, 1000.0);

	MatViewport.Identity();

	glClear(GL_COLOR_BUFFER_BIT);

	gdc->window->SwapBuff();
}



void RebGL::SetResolution(unsigned int w, unsigned int h)
{
	

	glShadeModel(GL_SMOOTH);
	/* Set the background black */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Depth buffer setup */
	glClearDepth(1.0f);

	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio;


	/* Protect against a divide by zero */
	if (h == 0) {
		h = 1;
	}

	/*w = width;

	h = height;*/
	ratio = (GLfloat)w / (GLfloat)h;
	/* Set our perspective */
	projmat.Perspective(45.0, ratio, 0.1, 1000.0);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode(GL_MODELVIEW);

	/* Reset The View */
	glLoadIdentity();


}

void RebGL::GetViewportSize(unsigned int * sw, unsigned int * sh)
{
	
}



RebGL::~RebGL()
{
	delete skinman;
	delete rls;
	delete rvcm;
	delete rss;


}

void RebGL::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
glClear(GL_COLOR_BUFFER_BIT);
}

void RebGL::Clear(bool color, bool depth)
{
	if (color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	if (depth)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}


ISkinManager * RebGL::GetSkinManager()
{
	return skinman;
}

IVertexCacheManager * RebGL::GetVertexCacheManager()
{
	return rvcm;
}

ILightSystem * RebGL::GetLightSystem()
{
	return rls;
}

IShaderSystem * RebGL::GetShaderSystem()
{
	return rss;
}


RebMatrix RebGL::GetViewportMat()
{
	return MatViewport;
}

void RebGL::SetViewportMat(RebMatrix svm)
{
	MatViewport = svm;
}

void ** RebGL::GetViewportID()
{
	return &ViewportID;
}


IGameEnv * RebGL::GetEnv()
{
	return rge;
}