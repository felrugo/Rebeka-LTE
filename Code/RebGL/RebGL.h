
#ifndef REBGL_H
#define REBGL_H
#include "GL\glew.h"
#include <Windows.h>
#include <fstream>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "..\Rimba\IRenderDevice.h"
#include "../Rimba/IUISystem.h"
#include "RebGL_skinmanager.h"
#include "RebGL_VCM.h"
#include "RebGL_SS.h"
#include "RebGL_LightSystem.h"
#include "RebEnv.h"
#include "RebGL_GraphicUtilities.h"
#include "..\RebSupport\RebGDC.h"
#include "..\Rimba\IWAEM.h"







class RebGL : public IRenderDevice
{

	RebGDC * gdc;

	RebGLSkinManager * skinman;

	RebVertexCacheManager * rvcm;

	//RebFileSystem * rfs;

	RebGLLightSystem * rls;

	RebShaderSystem * rss;

	//IWindowManager * iwm;

	RebEnv * rge;

	RebMatrix MatViewport;

	void * ViewportID;

	//Graphic Utilities

	RebGBuffer * gbuff;

	RebOPCSM * ropcsm;

	RebPostProcessor * rpp;


	//inner stages

	void FirstPass();

	void ShadowPass();

	void LightPass();

	void PostProcess();
	

public:

	
	RebGL(RebGDC * gdc);

	void SetResolution(unsigned int w, unsigned int h);

	void ClearColor(float r, float g, float b, float a);

	void StartDraw(Methold met);

	void Vertex3(float x, float y, float z);

	void Vertex3(RebVector RV);

	void Normal(RebVector RV);

	void MaterialSetup(RebMaterial rm);

	void TextCoord2(float s, float t);

	void BindTexture(UINT id);

	void Color(float r, float g, float b);

	void EndDraw();

	RebMatrix GetViewportMat();

	void SetViewportMat(RebMatrix svm);

	void ** GetViewportID();

	void GetViewportSize(unsigned int * w, unsigned int * h);

	ISkinManager * GetSkinManager();

	IVertexCacheManager * GetVertexCacheManager();

	IGameEnv * GetEnv();

	ILightSystem * GetLightSystem();

	IShaderSystem * GetShaderSystem();

	void Swap(void * window);

	void Flush();

	void ChangeMatrixMode(MatrixMode mm);

	void Clear(bool color, bool depth);

	void ResetMatrix();

	void PushMatrix();

	void PopMatrix();

	void Translate(float x, float y, float z);

	void Rotate(float a, float x, float y, float z);

	void Scale(float x, float y, float z);

	void TransformMatrix(RebMatrix trans);

	void Render();

	~RebGL();
};




#endif