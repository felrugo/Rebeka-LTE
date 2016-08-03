#ifndef REBGDC_H
#define REBGDC_H

class IWAEM;
class IWindow;
class IRenderDevice;
class IGameLogic;
class RebFileSystem;
class IEntitySystem;
class IMEH;


class RebGDC
{
public:
	IWAEM * waem;
	IRenderDevice * rd;
	IGameLogic * gl;
	IWindow * window;
	bool grp;
	RebFileSystem * rfs;
	IEntitySystem * res;
	RebGDC()
	{
		waem = 0;
		rd = 0;
		res = 0;
		gl = 0;
		window = 0;
		rfs = 0;
		grp = 0;
	}
};


#endif