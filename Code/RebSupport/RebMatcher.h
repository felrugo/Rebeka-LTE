#ifndef REBMATCHER_H
#define REBMATCHER_H

#include <string>
#include <vector>




class RebMatcher
{
	std::string sample;
	std::vector<std::string> splitted;

	bool isOperator(char c);

public:
	void SetSample(std::string ss);
	bool Match(std::string tocomp);
};



bool isOperator(char c)
{
	switch (c)
	{
	case '*':
		return true;
	default:
		return false;
	}
}

bool AdvencedMatch(std::string sample, std::string tom)
{
	size_t im = 0;
	size_t fp = 0;
	bool res = false;
	for (size_t is = 0; is < sample.length(); is++)
	{
		

		switch (sample[is])
		{
		case '*':

			fp = 0;
			res = false;
			if (is + 1 >= sample.length())
				return true;
			fp = tom.find_first_of(sample[is + 1], fp);
			//if(fp != std::string::npos)
			//res = AdvencedMatch(sample.substr(is + 1, sample.length() - 1), tom.substr(fp, tom.length()-fp));

			while (!res && fp != std::string::npos)
			{
				res = AdvencedMatch(sample.substr(is + 1, sample.length() - 1), tom.substr(fp, tom.length() - fp));
				if (res)
					return true;
				fp = fp = tom.find_first_of(sample[is + 1], fp+1);

			}
			return false;


			break;

		default:
			if (im >= tom.length())
				return false;
			if (sample[is] != tom[im])
			{
				return false;
			}
			break;
		}
			im++;
	}
	if (im < tom.length())
		return false;
	return true;
}


#endif
