#include "RebKeyMaps.h"
#include "RebEvent.h"
#include "RebWAEM.h"

RebKeyCode ConvertKeyToRebKeyCode(RAWKEYBOARD * rk)
{
	//mod chars
	bool extended = false;

	RebKeyCode ret = RK_NI;

	try
	{
		ret = VKtoRKC[rk->VKey];
	}
	catch (...)
	{
		ret = RK_NI;
	}

	
	//diff l/r shift
	if (ret == RK_LSHIFT && rk->MakeCode == 0x36)
		ret = RK_RSHIFT;



	return ret;
}


RebKeyEvent::RebKeyEvent(RAWINPUT * raw)
{
	key = ConvertKeyToRebKeyCode(&raw->data.keyboard);
	pressed = (raw->data.keyboard.Flags % 2 == 0);
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





RebMouseEvent::RebMouseEvent(RAWINPUT * raw)
{
	
				rel.x = raw->data.mouse.lLastX;
				rel.y = raw->data.mouse.lLastY;
				rel = rel / 100.0;
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