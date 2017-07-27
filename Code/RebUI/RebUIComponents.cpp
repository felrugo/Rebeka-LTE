#include "RebUIComponents.h"

void RebUIComponent::AddComponent(RebUIComponent * nc)
{
	childs.push_back(nc);
}

void RebUIComponent::RemoveComponent(RebUIComponent * rc)
{
	for (size_t i = 0; i < childs.size(); i++)
	{
		if (childs[i] == rc)
		{
			childs.erase(childs.begin()+i);
		}
	}
}
RebUIComponent * RebUIComponent::GetComponentByID(std::string id)
{
	for (std::vector<RebUIComponent*>::iterator i = childs.begin(); i != childs.end(); i++)
	{
		if ((*i)->GetProperity("id") == id)
			return (*i);
	}
	return NULL;
}


void RebUIComponent::SetProperity(std::string pname, std::string value)
{
	props[pname] = value;
}
std::string RebUIComponent::GetProperity(std::string pname)
{
	if (props.find(pname) != props.end())
	{
		return props[pname];
	}
	return "";
}

void RebUIComponent::Draw()
{

}


void RebUIComponent::Invalidate()
{

}


RebScreen::RebScreen(RebUISystem * uis)
{

}
