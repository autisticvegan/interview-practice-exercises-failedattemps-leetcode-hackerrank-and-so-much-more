#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

int findJudge(int N, std::vector<std::vector<int>>& trust) {

	std::unordered_map<int, int> indexToCount;
	std::unordered_set<int> seen;
	for (std::vector<int>& t : trust)
	{
		seen.insert(t[0]);
		indexToCount[t[1]]++;
	}

	if (indexToCount.empty())
	{
		return 1;
	}

	for (const auto& p : indexToCount)
	{
		if (p.second == N - 1 && seen.count(p.first) == 0)
			return p.first;
	}

	return -1;
}

std::vector<std::string> commonChars(std::vector<std::string>& A)
{
	std::unordered_map<char, int> char_To_Count;
	std::unordered_map<char, int> freq;

	for (int i = 0; i < 26; ++i)
	{
		freq.insert({ 'a' + i, INT_MAX });
	}

	for (const auto& s : A)
	{
		char_To_Count.clear();
		for (int i = 0; i < s.length(); ++i)
		{
			char_To_Count[s[i]]++;
		}

		for (auto& p : freq)
		{
			p.second = std::min(p.second, char_To_Count[p.first]);
		}
	}

	std::vector<std::string> res;
	for (const auto& p : freq)
	{
		int reps = p.second;

		for (int j = 0; j < reps; ++j)
		{
			std::string t = "";
			t += p.first;
			res.push_back(t);
		}
	}

	return res;
}

int main(void)
{
	std::vector<std::string> t{ "acabcddd", "bcbdbcbd", "baddbadb", "cbdddcac", "aacbcccd", "ccccddda", "cababaab", "addcaccd" };
	auto tt = commonChars(t);
	return 0;
}