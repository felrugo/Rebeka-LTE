#ifndef RGL_GU_H
#define RGL_GU_H

#include "RebGL_LightSystem.h"
#include "RebGL_SS.h"
#include <assert.h>
#include <memory>







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


class RebMotionBlur
{
	unsigned short level, cur;
	int w, h;
	GLuint mbfb;
	GLuint mbt[8];
public:
	RebMotionBlur();

	void SetRes(int sw, int sh);

	void SetLevel(unsigned short sl);

	void GetAvailable();

	void Bind(GLuint handle);

	~RebMotionBlur();
};




#endif // !RGL_GU_H