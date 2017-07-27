#pragma once
#include "RebUISystem.h"
#include <string>
#include <vector>
#include <map>


class RebUIComponent // can be Interface
{
protected:
	RebUIComponent * parent;
	std::map<std::string, std::string> props;
	std::map<std::string, std::string> style;
	std::vector<RebUIComponent *> childs;

public:
	virtual void AddComponent(RebUIComponent * nc);
	virtual void RemoveComponent(RebUIComponent * rc);
	virtual RebUIComponent * GetComponentByID(std::string id);
	virtual void SetProperity(std::string pname, std::string value);
	virtual std::string GetProperity(std::string pname);
	virtual void Draw();
	virtual void Invalidate();
};


class RebLabel;


class RebButton;

class RebPanel;

class RebWindow;

class RebScreen : public RebUIComponent
{
	std::map<std::string, RebUIComponent *> indexbyid;
public:
	RebScreen(RebUISystem * uis);

};