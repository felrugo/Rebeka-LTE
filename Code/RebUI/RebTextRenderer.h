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




class RebText
{
	GLuint fbo, tex, glyptex;
	size_t fw, fh, fsize;
	FT_Library lib;
	FT_Face face;
	std::string data;

	IShaderProgram * textprog;

	void Render();

	void TestRender();

public:
	RebText(RebGDC * gdc, IFile * font, size_t fsize, size_t bbx, size_t bby, std::string text = "");

	GLuint GetHandle();
};