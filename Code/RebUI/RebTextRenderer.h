#pragma once
#include <Windows.h>
#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "../Rimba/IRenderDevice.h"
#include "../Rimba/IFileSystem.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>



class RebCharacter
{
	GLuint ctex;
	float sizex, sizey;
	float advx, advy;
public:
	RebCharacter();
	RebCharacter(FT_Face& face, wchar_t c, size_t size);

	float GetAdvanceX();
	float GetAdvanceY();

	float GetH();
	float GetW();

	void BindTexture();

	~RebCharacter();
};

class RebCharacterSet
{
	std::string name;
	FT_Face face;
	size_t size;
	std::map<wchar_t, RebCharacter> chars;
public:
	RebCharacterSet(FT_Library& lib, IFile * file, size_t size);

	std::string GetName();

	RebCharacter * GetChar(wchar_t c);
};

class RebText
{
	RebCharacterSet * rcs;
	std::string data;
	int w, h;
	float r, g, b;
	GLuint fb, tex;
	IShaderProgram * textshad;

	void Render();
public:
	RebText(IFile * fontfile, std::string text = "", size_t sizepx = 12, RebVector color = RebVector(1.0, 1.0, 1.0));

	void SetText(std::string t);

	void SetCharSet(RebCharacterSet * cs);

	void SetColor(float r, float g, float b);
};



class RebTextManager
{
	RebGDC * gdc;

	FT_Library lib;
	GLuint tex, vbo;

	std::vector<RebCharacterSet> charsets;

	std::vector<RebText> texts;

	IShaderProgram * textshad;

	RebCharacterSet * GetByName(std::string name);

public:
	RebTextManager(RebGDC * gdc);


	RebText * CreateText(std::string font, std::string text, size_t size, float posx, float posy);
	

	~RebTextManager();
};