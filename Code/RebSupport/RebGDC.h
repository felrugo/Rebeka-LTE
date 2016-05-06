#ifndef REBGDC_H
#define REBGDC_H

class IWAEM;
class IWindow;
class IRenderDevice;
class RebGameLogic;
class RebFileSystem;
class IMEH;


class RebGDC
{
public:
	IWAEM * waem;
	IRenderDevice * rd;
	RebGameLogic * rlogic;
	IWindow * window;
	bool grp;
	RebFileSystem * rfs;
	RebGDC()
	{
		waem = 0;
		rd = 0;
		rlogic = 0;
		window = 0;
		rfs = 0;
		grp = 0;
	}
};


#endif