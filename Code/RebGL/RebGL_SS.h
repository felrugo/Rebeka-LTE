#ifndef REBSHADERSYSTEM_H
#define REBSHADERSYSTEM_H

#include "..\Rimba\IRenderDevice.h"
#include "../Rimba/IFileSystem.h"
#include <fstream>
#include <map>
#include <streambuf>
#include "GL\glew.h"
#include <gl\GL.h>

enum ShaderType { RS_VERTEX, RS_FRAGMENT, RS_GEOMETRY };

class RebGLShaderProgram;

class RebGLShader
{
	friend class RebGLShaderProgram;
	IFile * shadfile;
	unsigned int pshader;
	ShaderType ty;
	bool compiled;
	bool error;
	std::string GetShaderData(std::string file);
	void operator =(RebGLShader e);
public:
	RebGLShader(const RebGLShader& cop);
	RebGLShader();
	bool IsCompiled();
	ShaderType GetType();
	void Source(IFile * file);
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

	void AddShaderFile(IFile * shad);

	void Link();

	void Use();

	void SetUniformValue(std::string uname, int i);

	void SetUniformValue(std::string uname, float f);

	void SetUniformValue(std::string uname, RebVector rv);

	void UseDefault();

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