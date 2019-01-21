#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iterator>


std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {

	//hash way easy

	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	std::vector<int> res;

	auto iter1 = nums1.begin();
	auto iter2 = nums2.begin();

	while (iter1 != nums1.end() && iter2 != nums2.end())
	{
		if (*iter1 < *iter2)
		{
			++iter1;
		}
		else if (*iter1 > *iter2)
		{
			++iter2;
		}
		else
		{
			res.push_back(*iter1);
			++iter1;
			++iter2;
		}
	}

	return res;
}


std::string intToRoman(int num) {


	std::vector<std::string> thou{ "", "M", "MM", "MMM", "MMMM" };
	std::vector<std::string> hun{ "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	std::vector<std::string> ten{ "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	std::vector<std::string> one{ "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

	std::string ret;

	ret += thou[num / 1000];
	ret += hun[(num / 100) % 10];
	ret += ten[(num / 10) % 10];
	ret += one[num % 10];


	return ret;

}
};


/* Old way
		  std::vector<int> ret(1000);
	  std::set<int> one;
	  std::set<int> two;

	  for(int i = 0; i < nums1.size(); ++i)
		  one.insert(nums1[i]);

		  for(int i = 0; i < nums2.size(); ++i)
		  two.insert(nums2[i]);


	  std::vector<int>::iterator iter = std::set_intersection(one.begin(), one.end(), two.begin(), two.end(), ret.begin());
	  ret.resize(iter - ret.begin());
	  return ret;
	  */

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
	std::vector<int> result;

	std::unordered_set<int> tempresult;
	//obv if sorted we dont have to sort
	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	auto iter = nums1.begin();
	auto iter2 = nums2.begin();

	while (iter != nums1.end() && iter2 != nums2.end())
	{
		if (*iter < *iter2)
			++iter;
		else if (*iter > *iter2)
			++iter2;
		else
		{
			tempresult.insert(*iter);
			++iter;
			++iter2;
		}
	}

	for (const auto& i : tempresult)
		result.push_back(i);

	return result;
}




using namespace std;

//basic idea: count steps and make sure path length is equal to that
//since we have to walk over all the steps
//set to -1, then do 4 directions, then set back to 0


//copying and pasting because leetcode is stupid and didnt save

int dfs(vector<vector<int>>& g, int i, int j, int s, int t_s) {
	if (i < 0 || j < 0 || i >= g.size() || j >= g[0].size() || g[i][j] == -1) return 0;
	if (g[i][j] == 2) return s == t_s ? 1 : 0;
	g[i][j] = -1;
	int paths = dfs(g, i + 1, j, s + 1, t_s) + dfs(g, i - 1, j, s + 1, t_s) +
		dfs(g, i, j + 1, s + 1, t_s) + dfs(g, i, j - 1, s + 1, t_s);
	g[i][j] = 0;
	return paths;
}
int uniquePathsIII(vector<vector<int>>& g) {
	auto i1 = 0, j1 = 0, t_steps = 0;
	for (auto i = 0; i < g.size(); ++i)
		for (auto j = 0; j < g[0].size(); ++j) {
			if (g[i][j] == 1) i1 = i, j1 = j;
			if (g[i][j] != -1) ++t_steps;
		}
	return dfs(g, i1, j1, 1, t_steps);
}

int minDistance(std::string word1, std::string word2)
{

	if (word1.empty() || word2.empty())
		return word1.size() + word2.size();

	std::vector<std::vector<int>> dp(word1.length() + 1, std::vector<int>(word2.length() + 1));

	for (int i = 0; i < word1.length() + 1; ++i)
	{
		dp[i][0] = i;
	}

	for (int i = 0; i < word2.length() + 1; ++i)
	{
		dp[0][i] = i;
	}

	for (int i = 1; i < word1.length() + 1; ++i)
	{
		for (int j = 1; j < word2.length() + 1; ++j)
		{
			//  min of all 3 (up+1, left+1, diag)
			// if not same, then add 1 to diag

			int up = dp[i - 1][j] + 1;
			int left = dp[i][j - 1] + 1;
			int diag = dp[i - 1][j - 1];

			if (word1[i - 1] != word2[j - 1])
				diag += 1;

			dp[i][j] = std::min(up, std::min(left, diag));
		}
	}


	return dp[word1.length()][word2.length()];
}