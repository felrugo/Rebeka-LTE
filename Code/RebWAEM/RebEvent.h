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
	RebKeyEvent(RebWindow* win, UINT message, WPARAM wParam, LPARAM lParam);

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
	int mx, my;
	int relx, rely;
	RebVector pos, rel;
	RebWindow* win;

public:
	RebMouseEvent(RebWindow* win, UINT message, WPARAM wParam, LPARAM lParam);

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