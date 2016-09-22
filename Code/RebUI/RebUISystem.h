#ifndef REBUISYSTEM_H
#define REBUISYSTEM_H

#include "../Rimba/IWAEM.h"
#include "../Rimba/IUISystem.h"
#include "RebUIElements.h"




class RebUISystem : public IUISystem
{
	RebGDC * gdc;
	int w, h;
	GLuint uiframe, uiframetex;

	void InitFBO();
	void SetToDraw();
	void TestDraw();
public:
	RebUISystem(RebGDC * gdc);


	unsigned int RenderUI();
};





#endif