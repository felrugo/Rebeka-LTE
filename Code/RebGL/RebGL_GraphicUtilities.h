#pragma once

#include "RebGL.h"
#include "RebGL_SS.h"
#include <assert.h>
#include <memory>





class ShadowMap
{
protected:
	RebVector lpos;
public:
	virtual void Write() = 0;
	virtual void SetPos(RebVector set);
	virtual void Read() = 0;
	virtual void ShadowPass() = 0;
};

class ShadowMap2D : public ShadowMap
{
	GLuint sfbo, st, post;
	unsigned int w, h;
	IRenderDevice* ird;
	RebGLShaderProgram shadowProgram;

public:
	ShadowMap2D(RebGDC * rgdc);
	void Write();
	void Read();
	void ShadowPass();
	~ShadowMap2D();
};

class ShadowMapCube : public ShadowMap
{
	GLuint sfbo, st, post;
	unsigned int w, h;
	IRenderDevice* ird;
	RebGLShaderProgram shadowProgram;
public:
	ShadowMapCube(RebGDC * rgdc);
	void SetCUBE(GLuint handle);
	void Write();
	void Read();
	void ShadowPass();
	~ShadowMapCube();
};

class RebGBuffer
{
	GLuint fbo;
	GLuint texts[3];
public:
	RebGBuffer();
	~RebGBuffer();
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
