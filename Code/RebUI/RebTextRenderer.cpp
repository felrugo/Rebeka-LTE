#include "RebTextRenderer.h"
#include "../Reb3D/Reb3d.h"

RebCharacter::RebCharacter()
{
}

RebCharacter::RebCharacter(FT_Face& face, wchar_t c, size_t size)
{
	glGenTextures(1, &ctex);
	glBindTexture(GL_TEXTURE_2D, ctex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Set_Pixel_Sizes(face, 0, size);
	FT_Load_Char(face, c, FT_LOAD_RENDER);

	FT_GlyphSlot g = face->glyph;
	advx = g->advance.x;
	advy = g->advance.y;

	sizex = g->metrics.width;
	sizey = g->metrics.height;

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		g->bitmap.width,
		g->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		g->bitmap.buffer
	);


	glBindTexture(GL_TEXTURE_2D, 0);
}




void RebCharacter::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, ctex);
}

float RebCharacter::GetAdvanceX()
{
	return advx;
}

float RebCharacter::GetAdvanceY()
{
	return advy;
}

float RebCharacter::GetH()
{
	return sizey;
}

float RebCharacter::GetW()
{
	return sizex;
}

RebCharacter::~RebCharacter()
{
	glDeleteTextures(1, &ctex);
}







RebCharacterSet::RebCharacterSet(FT_Library& lib, IFile * file, size_t size) : size(size)
{
	name = file->GetName(false);

	FT_New_Face(lib, file->GetAPath().c_str(), 0, &face);
	//load basic chars
	for (wchar_t c = L'0'; c <= L'9'; c++)
	{
		chars[c] = RebCharacter(face, c, size);
	}

	for (wchar_t c = L'a'; c <= L'z'; c++)
	{
		chars[c] = RebCharacter(face, c, size);
	}

	for (wchar_t c = L'A'; c <= L'Z'; c++)
	{
		chars[c] = RebCharacter(face, c, size);
	}
}

RebCharacter * RebCharacterSet::GetChar(wchar_t c)
{
	std::map<wchar_t, RebCharacter>::iterator it = chars.find(c);

	if (it != chars.end())
		return &(it->second);
	chars[c] = RebCharacter(face, c, size);
	return &(chars[c]);
}

std::string RebCharacterSet::GetName()
{
	return name;
}




RebText::RebText(int resx, int resy, IShaderProgram * textshad) : w(resx), h(resy), textshad(textshad)
{
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RebText::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	glViewport(0, 0, w, h);
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);


	textshad->Use();
	glUniform1i(glGetUniformLocation(textshad->GetHandle(), "tex"), 0);
	glUniform3f(glGetUniformLocation(textshad->GetHandle(), "color"), r, g, b);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT);

	float penx = -1.0f;
	float peny = 1.0f;

	for (size_t i = 0; i < data.length(); i++)
	{
		switch (data[i])
		{
		default:
			glActiveTexture(GL_TEXTURE0);
			RebCharacter * ch = rcs->GetChar(data[i]);
			ch->BindTexture();

			glBegin(GL_QUADS);
			glVertex4f(penx, peny, 0, 0);
			glVertex4f(penx, peny - (ch->GetH() / (64.0 * float(h))), 0, 1);
			glVertex4f(penx + (ch->GetW() / (64.0 * float(w))), peny - (ch->GetH() / (64.0 * float(h))), 1, 1);
			glVertex4f(penx + (ch->GetW() / (64.0 * float(w))), peny, 1, 0);
			glEnd();

			penx += (ch->GetAdvanceX() / (64.0 * float(w)));
		}
	}


	glDisable(GL_BLEND);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	textshad->UseDefault();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void RebText::SetText(std::string t)
{
	data = t;
	Render();
}

void RebText::SetCharSet(RebCharacterSet * cs)
{
	rcs = cs;
	Render();
}

void RebText::SetColor(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	Render();
}



RebTextManager::RebTextManager(RebGDC * gdc) : gdc(gdc)
{
	FT_Init_FreeType(&lib);

	textshad = gdc->rd->GetShaderSystem()->GetFromBank("UIText");

	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//glUniform1i(uniform_tex, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenBuffers(1, &vbo);
	//glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

RebCharacterSet * RebTextManager::GetByName(std::string name)
{
	for (size_t i = 0; i < charsets.size(); i++)
	{
		if (charsets[i].GetName() == name)
			return &charsets[i];
	}

	return 0;
}


RebText * RebTextManager::CreateText(std::string font, std::string text, size_t size, float posx, float posy)
{
	RebCharacterSet * rcs = GetByName()

	IFile * f = gdc->rfs->Search(".*/fonts/" + name + "\\..*")[0];

	if (f == 0)
		return 0;

	RebCharacterSet cs();


}


RebTextManager::~RebTextManager()
{
	
}