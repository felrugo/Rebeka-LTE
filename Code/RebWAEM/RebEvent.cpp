#include "RebEvent.h"

RebEventType RebEvent::GetType()
{
	return RE_NOTDEF;
}

std::string RebEvent::GetAddInfo()
{
	return "Basic Event Object";
}





RebKeyCode ConvertKeyToRebKeyCode(WPARAM wParam, LPARAM lParam)
{
	if ((wParam >= 48 && wParam <= 57)||(wParam >= 65 && wParam <= 90)) //0-9 and a-z
		return RebKeyCode(wParam);
	//numpad
	if (wParam >= 0x60 && wParam <= 0x6f)
	{
		if (wParam >= 0x60 && wParam <= 0x69)//num0-num9
		{
			return RebKeyCode(RK_NUM0 + (wParam - 0x60));
		}
		switch (wParam)
		{
		case VK_DIVIDE:
			return RK_NUMDIV;
		case VK_MULTIPLY:
			return RK_NUMMUL;
		case VK_SUBTRACT:
			return RK_NUMSUB;
		case VK_ADD:
			return RK_NUMADD;
		default:
			break;
		}
	}

	//F1-F12
	if (wParam >= VK_F1 && wParam <= VK_F12)
		return RebKeyCode(RK_F1 + (wParam - VK_F1));

	//Arrows


	//mod chars
	UINT scancode = (lParam & 0x00ff0000) >> 16;
	int extended = (lParam & 0x01000000) != 0;

	switch (wParam)
	{
	case VK_TAB:
		return RK_TAB;
	case VK_CONTROL:
		return extended ? RK_RCTRL : RK_LCTRL;
	}

	return RK_NI;
}


RebKeyEvent::RebKeyEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
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
	default:
		throw "not key event";
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


bool RebKeyEvent::POR()
{
	return pressed;
}