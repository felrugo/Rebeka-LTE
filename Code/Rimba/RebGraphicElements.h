#ifndef REBGRAPHICELEMENTS_H
#define REBGRAPHICELEMENTS_H

#include <string>
#include <vector>
#include "..\Reb3D\Reb3d.h"
#include "IFileSystem.h"


enum Methold {R_TRIANGLES, R_QUADS};

enum MatrixMode
{
	MM_MODELVIEW,
	MM_PROJECTIONVIEW
};


enum PhysicState { PS_NOPS, PS_STATIC, PS_MOOVABLE, PS_SOFTBODY};

enum LightType {LT_SPOT, LT_POINT};


typedef RebVector RebColor;

typedef unsigned int UINT;


class ITexture
{
public:
	virtual IFile * GetFile() = 0;
	virtual void Bind() = 0;
};


class ITexture2D : public ITexture
{
public:
};

class IMaterial
{
public:
	virtual void Bind() = 0;
};


class ILight
{
protected:
	/*RebVector pos;
	RebColor color;
	LightType lt;
	RebMatrix view;*/
public:
	virtual RebVector GetPos() = 0;
	virtual RebVector GetColor() = 0;
};

class ITerrain
{
protected:
	/*std::vector<float> Hps;
	unsigned int stepx;
	unsigned int stepy;
	unsigned int textureid;
	float stepsize;
	RebMatrix trans;*/
public:
	virtual void Draw() = 0;
	virtual RebMatrix GetTrans() = 0;

};

class IVertexBuffer
{
public:
	
	virtual std::vector<RebVector> * GetVertices() = 0;

	virtual std::vector<RebVector> * GetNormals() = 0;

	virtual std::vector<RebVector> * GetTextureCoords() = 0;

	virtual void SetRenderable(bool s) = 0;

	virtual bool isRenderable() = 0;

	virtual IMaterial * GetMaterial() = 0;

	virtual void Draw() = 0;

	virtual void SetName(std::string sname) = 0;

	virtual void SetTrans(RebMatrix set) = 0;

	virtual RebMatrix * GetTrans() = 0;

	virtual void SetMaterial(IMaterial * set) = 0;


	
};


class IVertexCache
{
protected:
	/*std::vector<RebVertexBuffer*> RVBs;
	RebMatrix transf;
	std::string name;
	RebSkin skin;
	std::string filename;*/

public:

	virtual void AddBuffer(IVertexBuffer * abuff) = 0;
	
	virtual void SetName(std::string sname) = 0;

	virtual std::string GetName() = 0;

	virtual std::string GetFileName() = 0;

	virtual std::vector<IVertexBuffer*> * GetRVBs() = 0;

	virtual void SetTrans(RebMatrix set) = 0;

	virtual RebMatrix * GetTrans() = 0;

	virtual void SetFileName(std::string sfname) = 0;

	virtual void DeleteBuffer(UINT VBID) = 0;


	

};





#endif