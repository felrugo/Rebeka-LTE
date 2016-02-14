
#ifndef SKINMAN_H
#define SKINMAN_H


#include "..\Rimba\IRenderDevice.h"
#include "..\RebSupport\RebFileSystem.h"
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
	unsigned int w, h;

	GLuint th;

	RebFile * source;

	RebTexture(RebFile * file);
	~RebTexture();
public:
	void LoadIntoGL();
	void UnLoadFromGL();

	GLuint GetHandle();

	RebFile * GetFile();
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
	RebFileSystem * rfs;


	RebTexture * GetFromBank(RebFile * file);
   public:
	   RebGLSkinManager(RebFileSystem * srfs);
      ~RebGLSkinManager(void);

	  ITexture * GetTextureFromFile(RebFile * file);

};

#endif