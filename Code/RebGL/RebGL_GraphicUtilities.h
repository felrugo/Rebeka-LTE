#ifndef RGL_GU_H
#define RGL_GU_H

#include "RebGL_LightSystem.h"
#include "RebGL_SS.h"
#include <assert.h>
#include <memory>
#include "../Rimba/IRenderDevice.h"
#include "../Rimba/IUISystem.h"
#include "../Rimba/IWAEM.h"







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

class RebOPCSM
{
	GLuint fbo, cma;
	
public:
	RebOPCSM();
	void Write(char to);
	void Read();
	~RebOPCSM();

};


class RebPostProcessor
{
	GLuint frame;
	GLuint * mbtexs;
	unsigned int mbl;
	int ntod;
	IShaderProgram * PostProcessProg;
	RebGDC * gdc;
	int w, h;
public:
	RebPostProcessor(RebShaderSystem * rss, RebGDC * gdc, unsigned int mblevel = 4);
	void BindToDraw();
	void RenderOut();
	~RebPostProcessor();
};



#endif // !RGL_GU_H