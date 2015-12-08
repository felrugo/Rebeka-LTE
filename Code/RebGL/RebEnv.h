#ifndef REBENV
#define REBENV

#include <string>
#include <vector>
#include "RebGL_SS.h"

class RebGLTerrain : public ITerrain
{
	std::vector<float> Hps;
	unsigned int stepx;
	unsigned int stepy;
	unsigned int textureid;
	float stepsize;
	RebMatrix trans;
	bool loaded;
	GLuint vbo[2];
public:
	RebGLTerrain();

	void LoadFromFile(std::string rtf);

	void LoadIntoGL();

	void LoadFlat(int x, int y);

	void Draw();

	RebMatrix GetTrans();

	~RebGLTerrain();
};

class RebEnv : public IGameEnv
{
	std::vector<ITerrain*> Terrains;
public:
	RebEnv();
	ITerrain * CreateTerrain();
	ITerrain * CreateTerrain(std::string hmf);
	std::vector<ITerrain*> * GetTerrains();
	void DeleteTerrain(ITerrain * del);
};



#endif