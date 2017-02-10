#ifndef REBEVENT_H
#define REBEVENT_H

#include "..\Rimba\IEvent.h"
#include <Windows.h>

class RebWindow;

class RebKeyEvent : public IKeyEvent
{
	RebKeyCode key;
	bool pressed;
public:
	RebKeyEvent(RAWINPUT * raw);

	RebEventType GetType();
	std::string GetAddInfo();

	RebKeyCode GetKey();
	std::string GetReadable();
	bool POR();
};

class RebMouseEvent : public IMouseEvent
{
	RebKeyCode mousekey;
	bool pressed;
	int posx, posy;
	int relx, rely;
	RebVector pos, rel;
	RebWindow* win;

public:
	RebMouseEvent(RAWINPUT * raw);

	RebEventType GetType();
	std::string GetAddInfo();

	RebVector GetPos();
	RebVector GetRel();

	RebKeyCode GetMouseKey();
	bool POR();

	int GetPosX();
	int GetPosY();
	int GetMoveX();
	int GetMoveY();
};




#endif