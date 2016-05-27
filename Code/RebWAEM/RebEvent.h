#ifndef REBEVENT_H
#define REBEVENT_H

#include "..\Rimba\IEvent.h"
#include <Windows.h>

class RebEvent : public IEvent
{
public:
	 RebEventType GetType();
	 std::string GetAddInfo();
};


class RebKeyEvent : public RebEvent, public IKeyEvent
{
	RebKeyCode key;
	bool pressed;
public:
	RebKeyEvent(UINT message, WPARAM wParam, LPARAM lParam);

	RebEventType GetType();
	std::string GetAddInfo();

	virtual RebKeyCode GetKey();
	virtual bool POR();
};




#endif