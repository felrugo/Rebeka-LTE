#include "RebTextRenderer.h"
#include "../Reb3D/Reb3d.h"


void RebText::Render()
{

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, fw, fh);
	GLenum dbs[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, dbs);

	textprog->Use();
	glUniform1i(glGetUniformLocation(textprog->GetHandle(), "tex"), 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glyptex);

	glClear(GL_COLOR_BUFFER_BIT);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	float linespace = float(face->size->metrics.height) / float(fh * 64.0);

	float penx, peny;
	penx = -1.0f;
	peny = 1.0 - linespace;
	for (auto c : data)
	{

		switch (c)
		{


		case '\n':
			penx = -1.0f;
			peny -= linespace;
			break;

		default:
			FT_Load_Char(face, c, FT_LOAD_RENDER);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

			FT_GlyphSlot g = face->glyph;

			GLfloat xpos = penx + g->bitmap_left / float(fw);
			GLfloat ypos = peny - (g->bitmap.rows - g->bitmap_top) / float(fh);

			GLfloat w = g->bitmap.width / float(fw);
			GLfloat h = g->bitmap.rows / float(fh);

			glBegin(GL_QUADS);
			glVertex4f(xpos, ypos + h, 0.0, 0.0);
			glVertex4f(xpos, ypos, 0.0, 1.0);
			glVertex4f(xpos + w, ypos, 1.0, 1.0);
			glVertex4f(xpos + w, ypos + h, 1.0, 0.0);
			glEnd();

			float diff = 1.0 - (ypos + h);
			

			penx += (face->glyph->advance.x / (64.0 * fw));
			break;

		}

		

	}

	int err = glGetError();

	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RebText::TestRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, fw, fh);
	GLenum dbs[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, dbs);

	textprog->Use();
	glUniform1i(glGetUniformLocation(textprog->GetHandle(), "tex"), 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glyptex);

	glClear(GL_COLOR_BUFFER_BIT);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	FT_Load_Char(face, 'A', FT_LOAD_RENDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

	glBegin(GL_QUADS);
	glVertex4f(-1.0f, 1.0f, 0.0f, 0.0f);
	glVertex4f(-1.0f, -1.0f, 0.0f, 1.0f);
	glVertex4f(1.0f, -1.0f, 1.0f, 1.0f);
	glVertex4f(1.0f, 1.0f, 1.0f, 0.0f);
	glEnd();

	//float penx, peny;
	//penx = -1.0f;
	//peny = 1.0f;
	//for (auto c : data)
	//{
	//	FT_Load_Char(face, c, FT_LOAD_RENDER);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

	//	//Draw
	//	glBegin(GL_QUADS);
	//	glVertex4f(penx, peny, 0.0, 0.0);
	//	glVertex4f(penx + (face->glyph->bitmap.width / fw), peny, 1.0, 0.0);
	//	glVertex4f(penx + (face->glyph->bitmap.width / fw), peny - (face->glyph->bitmap.rows / fh), 1.0, 1.0);
	//	glVertex4f(penx, peny - (face->glyph->bitmap.rows / fh), 0.0, 1.0);
	//	glEnd();


	//	penx += (face->glyph->advance.x / (64.0 * fw));

	//}

	int err = glGetError();

	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


RebText::RebText(RebGDC * gdc, IFile * font, size_t fsize, size_t bbx, size_t bby, std::string text) : data(text), fw(bbx), fh(bby), fsize(fsize)
{

	textprog = gdc->rd->GetShaderSystem()->GetFromBank("UIText");

	FT_Init_FreeType(&lib);
	FT_New_Face(lib, font->GetAPath().c_str(), 0, &face);
	//FT_Set_Char_Size(face, fsize * 64, fsize * 64, 96, 96);
	FT_Set_Pixel_Sizes(face, fsize, fsize);

	glGenTextures(1, &glyptex);
	glBindTexture(GL_TEXTURE_2D, glyptex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fw, fh, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw "FAIL";

	int err = glGetError();

	Render();

}


GLuint RebText::GetHandle()
{
	return tex;
}