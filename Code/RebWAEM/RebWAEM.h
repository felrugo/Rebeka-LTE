#pragma once

#include "..\Rimba\IWAEM.h"
#include "RebEvent.h"
#include "..\RebSupport\RebFileSystem.h"
#include <Windows.h>
#include <windowsx.h>
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
	bool trapped;

	//metrics
	int csx, csy;
	int ccx, ccy;



	RebWindow(HWND set, std::string sname);
public:
	HWND GetHWND();

	std::string GetName();

	void SetSize(int w, int h);

	void ExpandClient();

	/**
	Set size and center coords for relative mouse handling.
	*/
	void UpdateMetrics();

	/**
	\return True if mouse is trapped.
	*/
	bool isTrapped();

	/**
	Used to calculate relative mouse movement.
	\param px Current mouse x coord in client, will be set to relative movement in pixel.
	\param py Current mouse y coord in client, will be set to relative movement in pixel.
	\return The relative movement normalized with the client size.
	*/
	RebVector RelativeMouse(int * px, int * py);

	void GetSize(int* w, int * h);

	void SetFullScreen(bool fs);

	void UpdateMouse();

	void CreateGLContext();

	void SetCurrentContext();

	void TrapMouse(bool t);

	void SwapBuff();
};


class RebWAEM : public IWAEM
{
	RebGDC * gdc;

	WNDCLASS wc;

	HINSTANCE hinst;

	MSG msg;

	std::vector<RebWindow*> winds;

	std::vector<IEventListener*> evlists;

	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	RebWindow* GetByHWND(HWND tof);

public:

	
	RebWAEM(RebGDC * sgdc);

	IWindow * CreateWnd(std::string name, int sx, int sy, bool fullscreen = false, int posx = -1, int posy = -1);

	IWindow * GetByName(std::string name);

	void RegisterEventListener(IEventListener* toreg);

	void UnRegisterEventListener(IEventListener* tounreg);

	void DeleteWindow(IWindow * win);

	void GetEvent();



};