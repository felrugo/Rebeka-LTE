#include "RebGL.h"



void CreateRenderDevice(IRenderDevice **LPRenderDevice)
{
	if(*LPRenderDevice == 0)
	*LPRenderDevice = new RebGL();
}

void ReleaseRenderDevice(IRenderDevice **LPRenderDevice)
{
	if(*LPRenderDevice != 0)
	delete *LPRenderDevice;
}



void * RebGL::tm()
{

	return 0;
}

void RebGL::Init(RebGDC * gd)
{
gd->rd = this;
	iwm = gd->winm;

	glewInit();

	skinman = new RebGLSkinManager;
	skinmanruning = true;

	rvcm = new RebVertexCacheManager(this, gd);
	VCMRunning = true;

	rss = new RebShaderSystem(gd);

	rls = new RebGLLightSystem(gd);

	rge = new RebEnv();
	MatViewport.Identity();

	//Init programs

	FirstPassProg = rss->GetFromBank("FirstPass");
	LightPassProg = rss->GetFromBank("LightPass");
	PostProcessProg = rss->GetFromBank("PostProcess");
	
	//Init utis

	gbuff = new RebGBuffer();



	//FOR TEST 

	rls->AddLight(RebColor(1, 1, 1), RebVector(0, 10.0, 0), LT_POINT, RebVector(0, 0, 0));

}

void RebGL::SetVP(int width, int height)
{
	glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
 
    /* Depth buffer setup */
    glClearDepth( 1.0f );
 
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
 
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
 
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	 glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
 
	GLfloat ratio;

 
    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    }
 
	w = width;

	h = height;
	ratio = ( GLfloat )width / ( GLfloat )height;
    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 1000.0f );
 
    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );
 
    /* Reset The View */
    glLoadIdentity( );


}

void RebGL::GetViewportSize(unsigned int * sw, unsigned int * sh)
{
	*sw = w;
	*sh = h;
}



void RebGL::Release()
{

	if(skinmanruning)
	{
	delete skinman;
	delete rls;
	skinmanruning = false;
	}

	if(VCMRunning)
	{
	delete rvcm;
	delete rss;
	VCMRunning = false;
	}
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

RebGL::~RebGL()
{
	//Release();
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