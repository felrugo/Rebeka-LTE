#ifndef REBSHADERSYSTEM_H
#define REBSHADERSYSTEM_H

#include "..\Rimba\IRenderDevice.h"
#include "..\RebSupport\RebFileSystem.h"
#include <fstream>
#include <map>
#include <streambuf>
#include "GL\glew.h"
#include <gl\GL.h>


class RebGLShaderProgram;

class RebGLShader
{
	friend class RebGLShaderProgram;
	enum ShaderType {RS_VERTEX, RS_FRAGMENT, RS_GEOMETRY};
	unsigned int pshader;
	ShaderType ty;
	bool * compiled;
	bool * error;
	unsigned int * copied;
	std::string GetShaderData(std::string file);
	void operator =(RebGLShader e);
	RebGLShader(const RebGLShader& cop);
	RebGLShader();
	bool IsCompiled();
	ShaderType GetType();
	void Source(RebFile * file);
	void Compile();
	unsigned int GetHandle();
	~RebGLShader();
};

class RebGLShaderProgram : public IShaderProgram
{
	unsigned int phandle;
	bool linked;
	RebGLShader * vs;
	RebGLShader * fs;
	RebGLShader * gs;

public:
	RebGLShaderProgram();

	void AddShaderFile(RebFile * shad);

	void Link();

	void Use();

	static void UseDefault();

	unsigned int GetHandle();

	~RebGLShaderProgram();
};


struct LMStruct
{
	GLuint D, A, S;
};




class RebShaderSystem : public IShaderSystem
{
	std::map<std::string, RebGLShaderProgram *> Bank;
	RebGDC * gdc;
	void LoadIntoBank();


public:
	RebShaderSystem(RebGDC * data);

	RebGLShaderProgram * GetFromBank(std::string name);

	~RebShaderSystem();
};



#endif