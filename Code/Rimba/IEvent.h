#ifndef IEVENT_H
#define IEVENT_H

#include "RebKeyCodes.h"
#include "../Reb3D/Reb3d.h"
#include <string>

enum RebEventType {RE_NOTDEF, RE_QUIT, RE_KEY, RE_MOUSE};


class IEvent
{
public:
	virtual RebEventType GetType() = 0;
	virtual std::string GetAddInfo() = 0;
};


class IQuitEvent : public virtual IEvent
{
public:
};

class IKeyEvent : public IEvent
{
public:
	virtual RebKeyCode GetKey() = 0;
	virtual std::string GetReadable() = 0;
	virtual bool POR() = 0;
};

class IMouseEvent : public IEvent
{
public:
	virtual RebKeyCode GetMouseKey() = 0;

	virtual RebVector GetPos() = 0;
	virtual RebVector GetRel() = 0;

	virtual int GetPosX()=0;
	virtual int GetPosY()=0;
	virtual int GetMoveX()=0;
	virtual int GetMoveY()=0;
};

class IEventListener
{
public:
	virtual void onEvent(IEvent * ev) = 0;
};

class IMouseEventListener : public IEventListener
{
public:
	virtual void onMouseMove(IMouseEvent* me) = 0;
	virtual void onMouseKeyPress(IMouseEvent* me) = 0;
};



#endif