
#ifndef SKINMAN_H
#define SKINMAN_H


#include "..\Rimba\IRenderDevice.h"
#include "../Rimba/IFileSystem.h"
#include <GL\glew.h>
#include <gl\GL.h>
#include <vector>
#include <string>
#include "FreeImage.h"
#include "assimp\scene.h"
#include "RebIH.h"


class RebTexture : public ITexture
{
	friend class RebGLSkinManager;
protected:
	FIBITMAP* imagen;
	GLubyte * conTexture;
	unsigned int w, h;

	GLuint th;

	IFile * source;

	RebTexture(IFile * file);
	~RebTexture();
public:
	void LoadIntoGL();
	void UnLoadFromGL();

	void Bind();

	IFile * GetFile();
};

class RebMaterial : public IMaterial
{
	ITexture *difftex, *spectex;
	RebVector diffcol, speccol;
	float specmult;

public:
	RebMaterial(ITexture * sdifftex = NULL, ITexture * sspectex = NULL,
				RebVector sdiffcol = RebVector(0.8f, 0.8f, 0.8f), RebVector sspeccol = RebVector(0.8f, 0.8f, 0.8f),
				float sspecmult = 1.0f);

	void Bind();


};



class RebGLSkinManager : public ISkinManager {
	 
	std::vector<RebTexture*> textures;
	IFileSystem * rfs;


	RebTexture * GetFromBank(IFile * file);
   public:
	   RebGLSkinManager(IFileSystem * srfs);
      ~RebGLSkinManager(void);

	  ITexture * GetTextureFromFile(IFile * file);

};

#endif