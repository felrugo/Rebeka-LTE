#pragma once

#include "..\RebSupport\RebGDC.h"
#include <string>

class IWindow
{
public:
	virtual std::string GetName() = 0;

	virtual void CreateGLContext() = 0;

	virtual void SetSize(int w, int h) = 0;

	virtual void GetSize(int* w, int * h) = 0;

	virtual void SetFullScreen(bool fs) = 0;

	virtual void SwapBuff() = 0;
};

class IWAEM
{
public:
	

	virtual IWindow * CreateWnd(std::string name, int sx, int sy, bool fullscreen = false, int posx = 0, int posy = 0) = 0;

	virtual IWindow * GetByName(std::string name) = 0;

	virtual void DeleteWindow(IWindow * win) = 0;

	virtual void GetEvent() = 0;
};
