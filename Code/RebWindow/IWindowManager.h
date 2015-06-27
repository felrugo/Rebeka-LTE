#ifndef IWINDOWMANAGER_H
#define IWINDOWMANAGER_H

#ifdef REBWINDOWMANAGER_H
#define REBWINDOWMANAGERAPI __declspec(dllexport)
#else
#define REBWINDOWMANAGERAPI __declspec(dllimport)
#endif


#include <string>



class IWindowManager
{
public:
	virtual void Init() = 0;

	virtual void Release() = 0;

	virtual void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0) = 0;

	virtual void DestroyWindow(std::string name) = 0;

	virtual void* GetWindow(std::string name) = 0;

	virtual void EnableRender(std::string name) = 0;

	virtual void SwapWindow(void * window) = 0;

	virtual void DisableRender(std::string name) = 0;

	virtual void TrapMouse(bool trap) = 0;

	virtual ~IWindowManager() {};
};


REBWINDOWMANAGERAPI void CreateWindowManager(IWindowManager **interf);
   
REBWINDOWMANAGERAPI void ReleaseWindowManager(IWindowManager **interf);
	
#endif