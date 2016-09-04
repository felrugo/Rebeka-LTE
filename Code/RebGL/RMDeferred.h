#ifndef RMDEFERRED
#define RMDEFERRED

#include "RebRenderTechnic.h"
#include "RebGL_LightSystem.h"
#include <assert.h>
#include <memory>
#include <stdlib.h>
#include <time.h>


class RTT
{
	GLuint fbo;
	GLuint texts[3];
public:
	RTT();
	~RTT();
	void Write();
	void bind(GLuint handle);
	int GetPostex();
	void Read();
};

class ShadowSum
{
	GLuint fbo, shadsum[2];
	GLuint depthrenderbuffer;
	RebGLShaderProgram ssum;
	RebGLLightSystem * ls;
public:
	ShadowSum(RebGDC * rgdc);
	void PassRandomPCF();
	void Write(char to);
	void SumShadows(int postexid);
	void Read();
	~ShadowSum();

};



class RMDeferred : public IRenderModel
{
	IRenderDevice * ird;
	IFileSystem * rfs;
	RebGLLightSystem * ls;
	
	float * tris;
	std::vector<IVertexCache*> * RVCs;
	/*RayTraceBuffer rtb;*/
	unsigned int width;
unsigned int height, mbi;

RTT tt;
ShadowSum ss;
RebGLShaderProgram geoProgram ;
RebGLShaderProgram lightProgram;
RebGLShaderProgram terrProgram;
RebGLShaderProgram ppprog;
GLuint mainObjectID;
GLuint lightVolumeID;
GLuint ppfb, ppt;
GLuint mbt[4];
RebMatrix lvm;

unsigned long int nof, last;
unsigned long int nott;

GLuint ssbo[2];
float mo;

unsigned long int gettriang();

public:
	RMDeferred(RebGDC * data);
	~RMDeferred();
	void PassGeom();
	void TerrainRender();
	void PostProc();
	RebGLShaderProgram * GetCSMP();
	void Shade();
	unsigned long int getFloats();
	void copy();
void Render();
};





#endif