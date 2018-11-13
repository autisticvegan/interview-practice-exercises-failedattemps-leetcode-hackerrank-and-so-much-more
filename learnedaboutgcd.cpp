#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <queue>

//interesting that my code usually worked in visual studio, but not in gcc or clang
//this was because the hash function was different for unordered maps(switching to maps fixed it)
//i guess in vs the hash function is like the integer so its kinda ordered

bool isLongPressedName(std::string name, std::string typed) {

	int index = 0;
	int nameindex = 0;

	std::map<int, int> Name2Blocks;
	std::map<int, int> Typed2Blocks;

	int i = 0;
	while (i < name.length())
	{
		char c = name[i];
		int count = 0;
		int orig = i;

		while (i < name.length() && c == name[i])
		{
			++i;
			++count;
		}

		Name2Blocks.insert({ orig,count });
	}

	i = 0;
	while (i < typed.length())
	{
		char c = typed[i];
		int count = 0;
		int orig = i;

		while (i < typed.length() && c == typed[i])
		{
			++i;
			++count;
		}

		Typed2Blocks.insert({ orig,count });
	}

	if (Typed2Blocks.size() != Name2Blocks.size())
		return false;

	auto typediter = Typed2Blocks.begin();
	auto nameiter = Name2Blocks.begin();

	while (nameiter != Name2Blocks.end())
	{
		if (typediter->second < nameiter->second)
		{
			return false;
		}

		typediter++;
		nameiter++;
	}


	return true;
}

bool hasGroupsSizeX(std::vector<int>& deck) {

	std::unordered_map<int, int> Suit2Count;
	for (int i : deck)
	{
		Suit2Count[i]++;
	}

	int gcd = 0;

	for (const auto& p : Suit2Count)
	{
		gcd = __gcd(p.second, gcd);

	}

	if (gcd > 1)
		return true;

	return false;
}

int main(void)
{
	//only words if c++ 17 is enabled in vs2017, or use __gcd if using gcc
	std::vector<int> g = { 1,1,2,2,2,2 };
	hasGroupsSizeX(g);
	std::gcd(1, 2);
	return 0;
}
