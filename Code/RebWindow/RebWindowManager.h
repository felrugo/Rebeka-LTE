#ifndef REBWINDOWMANAGER_H
#define REBWINDOWMANAGER_H


#include "SDL.h"
#include "IWindowManager.h"
#include <string>
#include <map>
#include <vector>

class RebWindowManager : public IWindowManager
{
	std::map<std::string, SDL_Window*> windows;

	std::map<std::string, SDL_GLContext> glcontexts;

	std::vector<std::string> keys;

	int finv(std::string name);
public:
	void Init();

	void Release();
		
	 void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0);

	 void DestroyWindow(std::string name);

	 void* GetWindow(std::string name);

	 void EnableRender(std::string name);

	 void DisableRender(std::string name);

	 void SwapWindow(void * window);

	 void TrapMouse(bool trap);

};





#endif