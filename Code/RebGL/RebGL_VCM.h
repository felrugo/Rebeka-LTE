#ifndef REBGL_VCM_H
#define REBGL_VCM_H


#include <gl\glew.h>
#include <GL\GL.h>
#include "IRenderDevice.h"
#include "assimp\Importer.hpp"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"



class RebAssimpMH : public IModelHandler
{
IVertexCache * RVC;
IRenderDevice * prd;
public:
RebAssimpMH(IRenderDevice * srd);
bool LoadModel(std::string file);
IVertexCache * GetRVC();
};





class RebGLVertexBuffer : public IVertexBuffer
{
	std::vector<RebVector> vertices;
	std::vector<RebVector> normals;
	std::vector<RebVector> texturecoords;
	bool Renderable;
	RebMatrix trans;
	std::string name;
	UINT ID;
	UINT materialid;


	bool loaded;
	GLuint vbo[3];

public:
	RebGLVertexBuffer();
	
	std::vector<RebVector> * GetVertices();

	std::vector<RebVector> * GetNormals();

	std::vector<RebVector> * GetTextureCoords();

	void SetRenderable(bool s);

	bool isRenderable();

	UINT GetMaterialID();

	RebMatrix * GetTrans();

	void SetName(std::string sname);

	void SetTrans(RebMatrix set);

	void SetMaterialID(UINT set);

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
	RebSkin skin;
	std::string filename;

public:
	RebGLVertexCache();

	void AddBuffer(IVertexBuffer * abuff);

	void SetName(std::string sname);

	std::string GetName();

	std::string GetFileName();

	RebSkin GetSkin();

	RebMatrix * GetTrans();

	std::vector<IVertexBuffer*> * GetRVBs();

	void SetTrans(RebMatrix set);

	void SetSkin(RebSkin sskin);

	void SetFileName(std::string sfname);

	void DeleteBuffer(UINT VBID);

	
};







class RebVertexCacheManager : public IVertexCacheManager
{
	std::vector<IVertexCache*> RVCs;

	IRenderDevice * prd;

public:

	RebVertexCacheManager(IRenderDevice * srd);

	void CreateCache(std::string name, std::vector<IVertexBuffer> RVB);

	void DeleteCache(IVertexCache* rvc);

	IVertexCache * GetVertexCache(std::string cname);

	IVertexCache * GetVCByFile(std::string filename); /* return 0 if VC doesn1t exists */

	void CreateCacheFromFile(std::string cname, std::string filename);

	std::vector<IVertexCache*> * GetRVCs();

	void Release();

	~RebVertexCacheManager();
};

#endif