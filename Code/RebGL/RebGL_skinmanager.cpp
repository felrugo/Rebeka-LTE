#include "RebGL_skinmanager.h"
            
RebTexture::RebTexture(RebFile * file)
{
	source = file;

	th = 0;

	// elvalasz
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(file->GetAPath().c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	imagen = FreeImage_Load(formato, file->GetAPath().c_str());

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	w = FreeImage_GetWidth(imagen);
	h = FreeImage_GetHeight(imagen);

	conTexture = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).

	for (int j = 0; j<w*h; j++) {
		conTexture[j * 4 + 0] = pixeles[j * 4 + 2];
		conTexture[j * 4 + 1] = pixeles[j * 4 + 1];
		conTexture[j * 4 + 2] = pixeles[j * 4 + 0];
		conTexture[j * 4 + 3] = pixeles[j * 4 + 3];
	}


}

void RebTexture::Bind()
{
	if (th == NULL)
		LoadIntoGL();
	glBindTexture(GL_TEXTURE_2D, th);
}


void RebTexture::LoadIntoGL()
{
	if (th == NULL)
	{
		glGenTextures(1, &th);
		glBindTexture(GL_TEXTURE_2D, th);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)conTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void RebTexture::UnLoadFromGL()
{
	if (th != NULL)
	{
		glDeleteTextures(1, &th);
		th = 0;
	}
}


RebFile * RebTexture::GetFile()
{
	return source;
}



RebTexture::~RebTexture()
{
	UnLoadFromGL();
	delete conTexture;
	FreeImage_Unload(imagen);
}

RebMaterial::RebMaterial(ITexture * sdifftex, ITexture * sspectex, RebVector sdiffcol, RebVector sspeccol, float sspecmult)
{
	difftex = sdifftex;
	spectex = sspectex;
	diffcol = sdiffcol;
	speccol = sspeccol;
	specmult = sspecmult;
}

void RebMaterial::Bind()
{
	//TODO
	glActiveTexture(GL_TEXTURE0);
	if (difftex != NULL)
		difftex->Bind();

}




RebGLSkinManager::RebGLSkinManager(RebFileSystem * srfs)
{
	FreeImage_Initialise();
	rfs = srfs;
	textures.clear();
}

RebGLSkinManager::~RebGLSkinManager()
{

}

RebTexture * RebGLSkinManager::GetFromBank(RebFile * file)
{
	for (std::vector<RebTexture*>::iterator i = textures.begin(); i != textures.end(); i++)
	{
		if ((*i)->GetFile() == file)
			return (*i);
	}
	return NULL;
}


ITexture * RebGLSkinManager::GetTextureFromFile(RebFile * file)
{
	if (file == NULL)
		return NULL;

	RebTexture * ret = GetFromBank(file);
	if (ret != NULL)
		return ret;

	ret = new RebTexture(file);
	textures.push_back(ret);

	return ret;
}

