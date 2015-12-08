#ifndef REBGL_LS
#define REBGL_LS

#include "IRenderDevice.h"
#include "RebGL_SS.h"



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


class RebGLLight : public ILight
{
	RebVector pos;
	RebColor color;
	LightType lt;
	RebMatrix view;
	ShadowMap * sm;
	float diffpower;
	float specpower;
public:
	RebGLLight(RebColor col, RebVector spos, LightType slt, RebVector spotlookat, RebGDC * gdc, float dp = 1.0f, float sp = 1.0f);
	void SetPos(RebVector spos);
	RebVector GetPos();
	RebVector GetColor();
	RebMatrix * GetViewm();
	ShadowMap * GetShadowMap();
	bool GetSop();

};

class RebGLLightSystem : public ILightSystem
{

	std::vector<ILight*> lights;
	RebGDC * gdc;

public:
	RebGLLightSystem(RebGDC * sgdc);

	ILight * AddLight(RebColor col, RebVector spos, LightType lt, RebVector spotlookat);
	void DeleteLight(ILight * todel);
	std::vector<ILight*> * GetLights();
	void SendLDtoShader(unsigned int handle);
	void Update();

	~RebGLLightSystem();
};







#endif