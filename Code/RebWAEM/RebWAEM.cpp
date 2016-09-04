#include "RebWAEM.h"


extern "C"
{

	__declspec(dllexport) void CreateRebWAEM(RebGDC * gdc)
	{
		gdc->waem = new RebWAEM(gdc);
	}

	__declspec(dllexport) void ReleaseRebWAEM(RebGDC * gdc)
	{
		delete gdc->waem;
		gdc->waem = NULL;
	}

}



RebWindow::RebWindow(HWND set, std::string sname)
{
	hWnd = set;
	name = sname;

	dc = NULL;
	glrc = NULL;
	UpdateMetrics();
	ShowWindow(hWnd, SW_SHOW);
}

HWND RebWindow::GetHWND()
{
	return hWnd;
}


std::string RebWindow::GetName()
{
	return name;
}

void RebWindow::SetSize(int w, int h)
{
	RECT win, adj;
	GetWindowRect(hWnd, &win);
	adj.top = adj.left = 0;
	adj.bottom = h;
	adj.right = w;
	AdjustWindowRect(&adj, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(hWnd, NULL, win.left, win.top, adj.right - adj.left, adj.bottom - adj.top, SWP_FRAMECHANGED);
	ShowWindow(hWnd, SW_SHOW);
	UpdateMetrics();
		
}


void RebWindow::ExpandClient()
{
	RECT win, adj;
	GetWindowRect(hWnd, &win);
	adj.top = adj.left = 0;
	adj.bottom = win.bottom - win.top;
	adj.right = win.right - win.left;
	AdjustWindowRect(&adj, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(hWnd, NULL, win.left, win.top, adj.right - adj.left, adj.bottom - adj.top, SWP_FRAMECHANGED);
	ShowWindow(hWnd, SW_SHOW);
	UpdateMetrics();
}

void RebWindow::SetFullScreen(bool fs)
{
	if (fs)
	{
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(hWnd, (HWND)-1, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
		UpdateMetrics();
	}
	else
	{
		//SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	}

}

void RebWindow::TrapMouse(bool t)
{
	if (t)
	{
		/*RECT win, trans;
		GetClientRect(hWnd, &win);
		POINT tl;
		tl.x = tl.y = 0;
		ClientToScreen(hWnd, &tl);
		trans.top = tl.y;
		trans.left = tl.x;
		trans.bottom = trans.top + win.bottom;
		trans.right = trans.left + win.right;
		ClipCursor(&trans);*/

		//ShowCursor(false);//hide
		trapped = true;
		SetCursorPos(ccx, ccy);
		//move to center
		
	}
	else
	{
		trapped = false;
	}
}

void RebWindow::UpdateMetrics()
{
	RECT win;
	GetClientRect(hWnd, &win);
	csx = win.right - win.left;
	csy = win.bottom - win.top;

	POINT p;
	p.x = win.right / 2;
	p.y = win.bottom / 2;
	ClientToScreen(hWnd, &p);
	ccx = p.x;
	ccy = p.y;
}

void RebWindow::GetSize(int* w, int * h)
{
	RECT rect;
	if (GetWindowRect(hWnd, &rect))
	{
		*w = rect.right - rect.left;
		*h = rect.bottom - rect.top;
	}
}


bool RebWindow::isTrapped()
{
	return trapped;
}

RebVector RebWindow::RelativeMouse(int * px, int * py)
{
		RebVector ret;
		*px -= ccx;
		*py -= ccy;
		ret.x = float(*px) / float(ccx);
		ret.y = float(*py) / float(ccy);
		return ret;
}

void RebWindow::UpdateMouse()
{
	if(trapped)
	SetCursorPos(ccx, ccy);
}

void RebWindow::SetCurrentContext()
{
	if(glrc != NULL)
	wglMakeCurrent(dc, glrc);
}

void RebWindow::CreateGLContext()
{
	if (glrc != NULL)
		return;
	
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
			32,                        //Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                        //Number of bits for the depthbuffer
			8,                        //Number of bits for the stencilbuffer
			0,                        //Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		dc = GetDC(hWnd);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(dc, &pfd);
		SetPixelFormat(dc, letWindowsChooseThisPixelFormat, &pfd);

		glrc = wglCreateContext(dc);
		wglMakeCurrent(dc, glrc);
}


void RebWindow::SwapBuff()
{
	if(dc != NULL)
	SwapBuffers(dc);
}



RebWAEM::RebWAEM(RebGDC * sgdc)
{
	gdc = sgdc;
	winds.clear();

	// Register the window class.
	hinst = GetModuleHandle(NULL);

	wc.lpfnWndProc = StaticWndProc;
	wc.hInstance = hinst;
	wc.lpszClassName = L"RLWC";

	RegisterClass(&wc);


	//read config

	std::ifstream cfg;
	IFile * cfgfile = gdc->rfs->Search(".*/Config/Windows.cfg")[0];
	cfg.open(cfgfile->GetAPath());
	if (cfg.is_open())
	{
			std::string buff, win, cont;
			int w, h;
			cfg >> buff;
			cfg >> win;
			cfg >> w;
			cfg >> h;
			cfg >> cont;
			RebWindow * window = (RebWindow*) CreateWnd(buff, w, h, (win == "fullscreen" ? true : false));

			if (cont == "OpenGL")
				window->CreateGLContext();

			gdc->window = window;
		cfg.close();
	}
	else
	{
		RebWindow * window = (RebWindow*)CreateWnd("Launcher", 1280, 720);
		window->CreateGLContext();
		gdc->window = window;
	}

}

IWindow * RebWAEM::CreateWnd(std::string name, int sx, int sy, bool fullscreen, int posx, int posy)
{
	if (GetByName(name) == NULL)
	{
		RECT adj;
		
		adj.top = adj.left = 0;
		adj.bottom = sy;
		adj.right = sx;
		AdjustWindowRect(&adj, WS_OVERLAPPEDWINDOW, FALSE);

		HWND hwnd;
		hwnd = CreateWindow(
			L"RLWC",                     // Window class
			std::wstring(name.begin(), name.end()).c_str(),    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

											// Size and position
			(posx < 0) ? CW_USEDEFAULT : posx, (posy < 0) ? CW_USEDEFAULT : posy, adj.right - adj.left, adj.bottom - adj.top,

			NULL,       // Parent window    
			NULL,       // Menu
			hinst,  // Instance handle
			this        // Additional application data
			);

		if (hwnd == NULL)
		{
			return NULL;
		}

		RebWindow * ret = new RebWindow(hwnd, name);
		ret->SetSize(sx, sy);
		winds.push_back(ret);
		return ret;
	}
	return NULL;
}


IWindow * RebWAEM::GetByName(std::string name)
{
	for (size_t i = 0; i < winds.size(); i++)
	{
		if (winds[i]->GetName() == name)
			return winds[i];
	}
	return NULL;
}


RebWindow* RebWAEM::GetByHWND(HWND tof)
{
	for (size_t i = 0; i < winds.size(); i++)
	{
		if (winds[i]->GetHWND() == tof)
		{
			return winds[i];
		}
	}
	return 0;
}

void RebWAEM::DeleteWindow(IWindow * win)
{
	for (size_t i = 0; i < winds.size(); i++)
	{
		if (winds[i] == win)
		{
			winds.erase(winds.begin() + i);
		}
	}
	delete (RebWindow*)win;
}


LRESULT CALLBACK RebWAEM::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		RebWAEM * waem = (RebWAEM *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLong(hWnd, GWL_USERDATA, (long)waem);
		return waem->WndProc(hWnd, message, wParam, lParam);
	}
	if (GetWindowLong(hWnd, GWL_USERDATA) != NULL)
	{
		RebWAEM * waem = (RebWAEM*)GetWindowLong(hWnd, GWL_USERDATA);
		return waem->WndProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT RebWAEM::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		gdc->grp = false;
		break;

	case WM_QUIT:
		gdc->grp = false;
		break;
	}

	//KeyEvent process
	if (message == WM_KEYDOWN || message == WM_KEYUP || message == WM_CHAR)
	{
		if (wParam == VK_F4) //emergency exit
		{
			gdc->grp = false;
		}
		RebKeyEvent rke(0, message, wParam, lParam);
	}

	//MouseEvent process
	if (0x0200 <= message && message <= 0x0205)
	{
		RebMouseEvent(GetByHWND(hWnd), message, wParam, lParam);
	}


	return DefWindowProc(hWnd, message, wParam, lParam); //Handle all the messages that we didn't
}


void RebWAEM::RegisterEventListener(IEventListener* toreg)
{
	for (size_t i = 0; i < evlists.size(); i++)
	{
		if (evlists[i] == toreg)
			return;
	}
	evlists.push_back(toreg);
}

void RebWAEM::UnRegisterEventListener(IEventListener* tounreg)
{
	for (size_t i = 0; i < evlists.size(); i++)
	{
		if (evlists[i] == tounreg)
		{
			evlists.erase(evlists.begin() + i);
		}
	}
}



void RebWAEM::GetEvent()
{
	GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}