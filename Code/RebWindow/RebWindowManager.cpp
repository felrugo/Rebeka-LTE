#include "RebWindowManager.h"

void CreateWindowManager(IWindowManager **interf)
{
	*interf = new RebWindowManager();
}

void ReleaseWindowManager(IWindowManager **interf)
{
	delete *interf;
}

void RebWindowManager::Init()
{
	int error;
    error = SDL_Init(SDL_INIT_EVERYTHING);
    // Turn on double buffering.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void RebWindowManager::Release()
{
	SDL_Quit();
	int i = 0;
	while (keys.size() > 0)
	{
		DisableRender(keys[i]);
		DestroyWindow(keys[i]);
		i++;
	}
}

void RebWindowManager::CreateWin(std::string name, int w, int h, int posx, int posy)
{
	windows[name] = SDL_CreateWindow(
		name.c_str(), posx, posy, w, h, 
    SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	keys.push_back(name);
}

void RebWindowManager::DestroyWindow(std::string name)
{
	DisableRender(name);
	SDL_DestroyWindow(windows[name]);
	windows.erase(name);
	if(finv(name) != -1)
	keys.erase(keys.begin() + finv(name));
}

void* RebWindowManager::GetWindow(std::string name)
{
	return windows[name];
}

void RebWindowManager::EnableRender(std::string name)
{
	glcontexts[name] = SDL_GL_CreateContext(windows[name]);
}

void RebWindowManager::DisableRender(std::string name)
{
	SDL_GL_DeleteContext(glcontexts[name]);
}

int RebWindowManager::finv(std::string name)
{
	int i;
	for (i = 0; i < keys.size(); i++)
	{
		if(keys[i] == name)
		{
			return i;
		}
	}
	return -1;
}

void RebWindowManager::SwapWindow(void * window)
{
	SDL_GL_SwapWindow((SDL_Window *) window);
}



void RebWindowManager::TrapMouse(bool trap)
{
	SDL_SetRelativeMouseMode((SDL_bool)trap);
}