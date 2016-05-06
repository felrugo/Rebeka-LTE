
#ifndef RENDERINTERFACE_H 
#define RENDERINTERFACE_H 
 

// I N C L U D E S ///////////////////////////////////////////////// 
 

#include "RebGraphicElements.h"
#include "..\RebSupport\RebGDC.h"
#include "IGameLogic.h"
 
// D E F I N E S /////////////////////////////////////////////////// 
 
#define MAX_3DHWND 8 
 
 
 
// S T R U C T S /////////////////////////////////////////////////// 


class ILightSystem
{
public:
	virtual ~ILightSystem() {}
};


class IRenderDevice;

class IRenderModel;

class IShaderProgram
{
public:
};

class IShaderSystem
{
	public:
		virtual IShaderProgram * GetFromBank(std::string name) = 0;

};


class IImageHandler
{
public:
	virtual void LoadFile(std::string file) = 0;
	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;
	virtual RebVector GetPixelColor(unsigned int x, unsigned int y) = 0;
	virtual void LoadIntoRenderer() = 0;


};

class IModelHandler
{
public:
virtual bool LoadModel(std::string file) = 0;
virtual IVertexCache * GetRVC() = 0;
};

class ISkinManager {
public:
	
	
      
   };

class IVertexCacheManager
{
public:
	virtual void CreateCache(std::string name, std::vector<IVertexBuffer> RVB) = 0;

	virtual void DeleteCache(IVertexCache * rvc) = 0;

	virtual IVertexCache * GetVertexCache(std::string cname) = 0;

	virtual IVertexCache * GetVCByFile(std::string filename) = 0; /*if VC doesn't exists return 0 */

	virtual void CreateCacheFromFile(std::string cname, RebFile * file) = 0;

	virtual void Release() = 0;

	virtual std::vector<IVertexCache*> * GetRVCs() = 0;

	virtual ~IVertexCacheManager() {}
};

class IGameEnv
{
public:
	virtual ITerrain * CreateTerrain() = 0;
	virtual ITerrain * CreateTerrain(std::string frp) = 0;
	virtual std::vector<ITerrain*> * GetTerrains() = 0;
	virtual void DeleteTerrain(ITerrain * del) = 0;
};

class IRenderDevice// : public RebScriptImplementer
{	
	public:

	virtual void SetResolution(unsigned int w, unsigned int h) = 0; 

	virtual void ClearColor(float r, float g, float b, float a) = 0;

	virtual void StartDraw(Methold met) = 0;

	virtual void EndDraw() = 0;

	virtual ISkinManager * GetSkinManager() = 0;

	virtual IVertexCacheManager * GetVertexCacheManager()= 0;

	virtual IGameEnv * GetEnv() = 0;

	virtual ILightSystem * GetLightSystem() = 0;

	virtual RebMatrix GetViewportMat() = 0;

	virtual void SetViewportMat(RebMatrix svm) = 0;

	virtual void ** GetViewportID() = 0;

	virtual void GetViewportSize(unsigned int * w, unsigned int * h) = 0;

	virtual void Vertex3(float x, float y, float z) = 0;

	virtual void Vertex3(RebVector RV)= 0;

	virtual void TextCoord2(float s, float t) = 0;

	virtual void BindTexture(UINT id) = 0;

	virtual void Color(float r, float g, float b) = 0;

	virtual void Normal(RebVector RV) = 0;

	virtual void ChangeMatrixMode(MatrixMode mm) = 0;

	virtual void Clear(bool color, bool depth) = 0;

	virtual void ResetMatrix() = 0;

	virtual void PushMatrix() = 0;

	virtual void PopMatrix() = 0;

	virtual void Translate(float x, float y, float z) = 0;

	virtual void Rotate(float a, float x, float y, float z) = 0;

	virtual void Scale(float x, float y, float z) = 0;

	virtual void TransformMatrix(RebMatrix trans) = 0;

	virtual void Swap(void * window) = 0;

	virtual void Flush() = 0;

	virtual void Render() = 0;
};

   

#endif