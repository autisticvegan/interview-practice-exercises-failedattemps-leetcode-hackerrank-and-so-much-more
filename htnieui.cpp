#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>


std::vector<std::string> subdomainVisits(std::vector<std::string>& cpdomains) {

	std::unordered_map<std::string, int> domains2visits;

	for (std::string& s : cpdomains)
	{
		size_t space = s.find(' ');
		std::string vall = s.substr(0, space);
		int val = std::stoi(vall);

		size_t dot1 = s.find('.');

		std::string vvvv = s.substr(dot1 + 1);
		domains2visits[vvvv] += val;


		size_t dot2 = s.find('.', dot1 + 1);

		std::string finall;

		if (dot2 != std::string::npos)
		{
			finall = s.substr(dot2 + 1);
			domains2visits[finall] += val;
		}

		std::string vvv = s.substr(space + 1);
		domains2visits[vvv] += val;
	}

	std::vector<std::string> res;

	for (const auto& it : domains2visits)
	{
		std::string s = std::to_string(it.second);
		s += " " + it.first;
		res.push_back(s);
	}


	return res;


}

std::vector<int> shortestToChar(std::string S, char C) {

	//scan back and forth
	//
	size_t first = S.find(C);
	size_t second = S.find(C, first + 1);
	std::vector<int> results(S.length());

	for (int i = 0; i < S.length(); ++i)
	{
		if (i < first)
		{
			results[i] = std::abs((int)first - i);
		}
		else if (i > first && i < second)
		{
			results[i] = std::min(i - first, second - i);
		}
		else if (i == first || i == second)
		{
			results[i] = 0;
		}
		else
		{
			first = second;
			second = S.find(C, second + 1);


			results[i] = std::min(i - first, second - i);
		}
	}

	return results;
}


int main(void)
{
	std::vector<std::string> g;
	g.push_back("9001 leetcode.ui.com");
	subdomainVisits(g);

	return 0;
}