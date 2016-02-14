
#include <Windows.h>
#include "..\Rimba\Rimba.h"

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)             
{
	Rimba loader;
	IGame * game = 0;
	loader.LoadGameDLL(&game);
	game->Init();
	game->GameLoop();
	game->Release();
	loader.ReleaseGameDLL(&game);
	return 0;
}