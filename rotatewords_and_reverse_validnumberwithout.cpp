#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

//this removes the .'s in the front part, and removes everything from + forward
std::string FormatEmail(std::string& e)
{
	size_t index = e.find_first_of('@');


	//now index is @
	std::string subo = e.substr(0, index);

	size_t pupu = subo.find_first_of('+');

	std::string finalo;

	if (pupu != std::string::npos) //if there was a +
	{
		finalo = subo.substr(0, pupu );
	}
	else
	{
		finalo = subo;
	}

	finalo.erase(std::remove(finalo.begin(), finalo.end(), '.'), finalo.end());

	return finalo + e.substr(index, e.length() - index);
}




int main(void)
{
	std::vector<std::string> g;
	g.push_back("ahoeu+hoeu@a.com");
	g.push_back("ahoeu@a.com");
	g.push_back("a.y.u.@pp.com");
	g.push_back("ayu@pp.com");
	g.push_back("a.@pp.com");
	g.push_back("a+@pp.com");

	std::unordered_set<std::string> FOAD;

	for (std::string& p : g)
	{
		FOAD.insert(FormatEmail(p));
	}


	return 0;
}