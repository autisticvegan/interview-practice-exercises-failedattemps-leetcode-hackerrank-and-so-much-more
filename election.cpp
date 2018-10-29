#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
std::string Winner(std::vector<std::string>& in)
{
	std::string res;

	std::unordered_map<std::string, int> n2v;

	for (std::string& a : in)
	{
		n2v[a]++;
	}

	int max = 0;
	for (const auto& it : n2v)
	{
		if (it.second > max)
		{
			max = it.second;
			res = it.first;
		}
		else if(it.second == max && res.compare(it.first) < 0)
		{
			res = it.first;
		}
	}

	return res;
}

int main(void)
{
	std::vector<std::string> a;
	a.push_back("b");
	a.push_back("b");
	a.push_back("b");
	a.push_back("b");

	a.push_back("c");
	a.push_back("c");
	a.push_back("c");


	a.push_back("a");

	Winner(a);

	return 0;
}