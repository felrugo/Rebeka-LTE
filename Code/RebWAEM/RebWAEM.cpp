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

	ShowWindow(hWnd, SW_SHOW);
}


std::string RebWindow::GetName()
{
	return name;
}

void RebWindow::SetSize(int w, int h)
{
	SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_FRAMECHANGED);
	ShowWindow(hWnd, SW_SHOW);
}




void RebWindow::SetFullScreen(bool fs)
{
	if (fs)
	{
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(hWnd, (HWND)-1, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);

	}
	else
	{
		//SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	}

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
	RebFile * cfgfile = gdc->rfs->Search("Windows.cfg")[0];
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

		HWND hwnd;
		hwnd = CreateWindow(
			L"RLWC",                     // Window class
			std::wstring(name.begin(), name.end()).c_str(),    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

											// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, sx, sy,

			NULL,       // Parent window    
			NULL,       // Menu
			hinst,  // Instance handle
			this        // Additional application data
			);

		if (hwnd == NULL)
		{
			return 0;
		}

		RebWindow * ret = new RebWindow(hwnd, name);
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
	if (message == WM_KEYDOWN || message == WM_KEYUP)
	{
		RebKeyEvent rke(message, wParam, lParam);
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