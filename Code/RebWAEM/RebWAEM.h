#pragma once

#include "..\Rimba\IWAEM.h"
#include "..\RebSupport\RebFileSystem.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>
#include <vector>
#include <fstream>



class RebWindow : public IWindow
{
friend class RebWAEM;

protected:
	std::string name;
	HWND hWnd;
	HDC dc;
	HGLRC glrc;

	RebWindow(HWND set, std::string sname);
public:
	std::string GetName();

	void SetSize(int w, int h);

	void GetSize(int* w, int * h);

	void SetFullScreen(bool fs);

	void CreateGLContext();

	void SetCurrentContext();

	void SwapBuff();
};


class RebWAEM : public IWAEM
{
	RebGDC * gdc;

	WNDCLASS wc;

	HINSTANCE hinst;

	std::vector<RebWindow*> winds;

	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	
	RebWAEM(RebGDC * sgdc);

	IWindow * CreateWnd(std::string name, int sx, int sy, bool fullscreen = false, int posx = 0, int posy = 0);

	IWindow * GetByName(std::string name);

	void DeleteWindow(IWindow * win);

	void GetEvent();



};