#ifndef IEVENT_H
#define IEVENT_H

#include "RebKeyCodes.h"
#include <string>

enum RebEventType {RE_NOTDEF, RE_QUIT, RE_KEY};


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

class IKeyEvent : public virtual IEvent
{
public:
	virtual RebKeyCode GetKey() = 0;
	virtual bool POR() = 0;
};

class IEventListener
{
public:
	virtual void onEvent(IEvent * ev) = 0;
};



#endif