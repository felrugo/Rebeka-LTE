#include "RebKeyMaps.h"
#include "RebEvent.h"
#include "RebWAEM.h"

RebKeyCode ConvertKeyToRebKeyCode(WPARAM wParam, LPARAM lParam)
{
	//mod chars
	UINT scancode = (lParam & 0x00ff0000) >> 16;
	int extended = (lParam & 0x01000000) != 0;

	RebKeyCode ret = RK_NI;

	try
	{
		ret = VKtoRKC[wParam];
	}
	catch (...)
	{
		ret = RK_NI;
	}

	if (MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX) == VK_RSHIFT)
		ret = RK_RSHIFT;


	if (extended)
	{
		switch (ret)
		{
		case RK_LCTRL:
			ret = RK_RCTRL;
			break;
		case RK_LALT:
			ret = RK_RALT;
			break;
		default:
			break;
		}
	}

	return ret;
}


RebKeyEvent::RebKeyEvent(RebWindow* win, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t ch;
	switch (message)
	{
	case WM_KEYDOWN:
		pressed = true;
		key = ConvertKeyToRebKeyCode(wParam, lParam);
		break;
	case WM_KEYUP:
		pressed = false;
		key = ConvertKeyToRebKeyCode(wParam, lParam);
		break;
	case WM_CHAR:
		ch = wParam;
		break;
	default:
		throw "NOT KEY EVENT";
	}
}

RebEventType RebKeyEvent::GetType()
{
	return RE_KEY;
}


std::string RebKeyEvent::GetAddInfo()
{
	return "KeyEvent";
}


RebKeyCode RebKeyEvent::GetKey()
{
	return key;
}

std::string RebKeyEvent::GetReadable()
{
	return RKtoReadable[key];
}


bool RebKeyEvent::POR()
{
	return pressed;
}





RebMouseEvent::RebMouseEvent(RebWindow* win, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		mousekey = RK_LMOUSE;
		pressed = true;
		break;
	case WM_LBUTTONUP:
		mousekey = RK_LMOUSE;
		pressed = false;
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		relx = posx = GET_X_LPARAM(lParam);
		rely = posy = GET_Y_LPARAM(lParam);
		if (win->isTrapped())
		{
			rel = win->RelativeMouse(&relx, &rely);
			win->UpdateMouse();
		}
		pos = RebVector(float(posx), float(posy), 0.0f);
		break;
	case WM_MOUSELEAVE:
		win->UpdateMouse();
		break;
	default:
		throw "NOT MOUSE EVENT";
	}
	this->win = win;
}

RebEventType RebMouseEvent::GetType()
{
	return RE_MOUSE;
}
std::string RebMouseEvent::GetAddInfo()
{
	return "";
}


RebVector RebMouseEvent::GetPos()
{
	return pos;
}

RebVector RebMouseEvent::GetRel()
{
	return rel;
}

RebKeyCode RebMouseEvent::GetMouseKey()
{
	return mousekey;
}

bool RebMouseEvent::POR()
{
	return pressed;
}

int RebMouseEvent::GetPosX()
{
	return posx;
}

int RebMouseEvent::GetPosY()
{
	return posy;
}

int RebMouseEvent::GetMoveX()
{
	return relx;
}

int RebMouseEvent::GetMoveY()
{
	return rely;
}