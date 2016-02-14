#ifndef REBGL_VCM_H
#define REBGL_VCM_H


#include <gl\glew.h>
#include <GL\GL.h>
#include "..\Rimba\IRenderDevice.h"
#include "assimp\Importer.hpp"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"
#include "..\RebSupport\RebFileSystem.h"
#include "rebgl_skinmanager.h"






class RebGLVertexBuffer : public IVertexBuffer
{
	std::vector<RebVector> vertices;
	std::vector<RebVector> normals;
	std::vector<RebVector> texturecoords;
	bool Renderable;
	RebMatrix trans;
	std::string name;
	UINT ID;
	IMaterial * material;

	bool loaded;
	GLuint vbo[3];

public:
	RebGLVertexBuffer();
	
	std::vector<RebVector> * GetVertices();

	std::vector<RebVector> * GetNormals();

	std::vector<RebVector> * GetTextureCoords();

	void SetRenderable(bool s);

	bool isRenderable();

	IMaterial * GetMaterial();

	RebMatrix * GetTrans();

	void SetName(std::string sname);

	void SetTrans(RebMatrix set);

	void SetMaterial(IMaterial * set);

	void LoadIntoGL();

	void Draw();

	void UnLoad();

	~RebGLVertexBuffer();
};

class RebGLVertexCache : public IVertexCache
{

	std::vector<IVertexBuffer*> RVBs;
	RebMatrix transf;
	std::string name;
	std::string filename;

public:
	RebGLVertexCache();

	void AddBuffer(IVertexBuffer * abuff);

	void SetName(std::string sname);

	std::string GetName();

	std::string GetFileName();

	RebMatrix * GetTrans();

	std::vector<IVertexBuffer*> * GetRVBs();

	void SetTrans(RebMatrix set);

	void SetFileName(std::string sfname);

	void DeleteBuffer(UINT VBID);

	
};







class RebVertexCacheManager : public IVertexCacheManager
{
	std::vector<IVertexCache*> RVCs;

	RebFileSystem * rfs;

	RebGLSkinManager * rsm;

	IMaterial * MaterialFromAssimp(aiMaterial * mate);

public:

	RebVertexCacheManager(RebFileSystem * srfs, RebGLSkinManager * srsm);

	void CreateCache(std::string name, std::vector<IVertexBuffer> RVB);

	void DeleteCache(IVertexCache* rvc);

	IVertexCache * GetVertexCache(std::string cname);

	IVertexCache * GetVCByFile(std::string filename); /* return 0 if VC doesn1t exists */

	void CreateCacheFromFile(std::string cname, RebFile * file);

	std::vector<IVertexCache*> * GetRVCs();

	void Release();

	~RebVertexCacheManager();
};

#endif