
#include <Windows.h>
#include "..\RebGame\IGame.h"

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)             
{
	IGame * game = 0;
	LoadGame(&game);
	game->Init();
	game->GameLoop();
	game->Release();
	ReleaseGame(&game);
	return 0;
}