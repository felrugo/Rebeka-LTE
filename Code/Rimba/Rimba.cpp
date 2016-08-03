#include "Rimba.h"



void Rimba::LoadGameDLL(IGame ** game)
{
	void(*generator)(IGame **) = 0;

	//IGame
	gamedll = LoadLibrary(L"RebGame.dll");
	generator = (void(*)(IGame **)) GetProcAddress(gamedll, "LoadGame");
	generator(game);
}


void Rimba::LoadModules(RebGDC* gdc)
{

	//GDC Support modules
	gdc->rfs = new RebFileSystem();

	//primitive function
	void (*generator)(RebGDC*) = 0;

	//IWAEM
	waemdll = LoadLibrary(L"RebWAEM.dll");
	generator = (void(*)(RebGDC*)) GetProcAddress(waemdll, "CreateRebWAEM");
	generator(gdc);

	//IRenderDevice

	renderdll = LoadLibrary(L"RebGL.dll");
	generator = (void(*)(RebGDC*)) GetProcAddress(renderdll, "CreateRebGL");
	generator(gdc);

	//IGameLogic
	glogicdll = LoadLibrary(L"RebGameLogic.dll");
	generator = (void(*)(RebGDC*)) GetProcAddress(glogicdll, "CreateGameLogic");
	generator(gdc);

	//IEntitySystem
	entsysdll = LoadLibrary(L"RebEntitySystem.dll");
	generator = (void(*)(RebGDC*)) GetProcAddress(entsysdll, "CreateEntitySystem");
	generator(gdc);

	//another module



}


void Rimba::ReleaseGameDLL(IGame ** game)
{
	void(*release)(IGame **) = 0;
	release = (void(*)(IGame **)) GetProcAddress(gamedll, "ReleaseGame");
	release(game);
}