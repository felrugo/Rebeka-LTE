#include "RebMatcher.h"



bool RebMatcher::isOperator(char c)
{
	switch (c)
	{
	case '*':
		return true;
	default:
		return false;
	}

}

void RebMatcher::SetSample(std::string ss)
{
	sample = ss;
	splitted.clear();
	size_t sp = 0;
	for (size_t is = 0; is < sample.length(); is++)
	{
		if (isOperator(sample[is]))
		{
			std::string co = sample.substr(sp, is - sp + 1);
		}
	}
}

bool RebMatcher::Match(std::string tocomp)
{
	for (size_t is = 0; is < sample.length(); is++)
	{
		switch (sample[is])
		{
		case '*':
			
			break;

		default:
			break;
		}
	}



	return false;
}

