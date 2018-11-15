#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>

bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {

	if (n == 0)
		return true;

	if (flowerbed.size() < 2)
	{
		if (flowerbed[0] == 0)
		{
			if (n > 1)
				return false;

			return true;
		}

		return false;
	}

	int count = 0;

	for (int i = 0; i < flowerbed.size(); ++i)
	{
		if (i == 0)
		{//first is 0
			if (flowerbed[i] == 0 && flowerbed[i + 1] == 0)
			{
				++count;
				++i;
			}
		}
		else if (i == flowerbed.size() - 1)
		{
			if (flowerbed[i] == 0 && flowerbed[i - 1] == 0)
			{
				++count;
				++i;//unnecessary
			}
		}
		else if (flowerbed[i] == 0)
		{
			if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0)
			{
				++count;
				++i;
			}
		}

	}

	if (n > count)
		return false;

	return true;

}

int main(void)
{
	std::vector<int> t = { 0,0,1,0,0 };
	canPlaceFlowers(t, 2);
	return 0;
}

bool buddyStrings(std::string A, std::string B) {

	if (A.size() != B.size())
	{
		return false;
	}

	std::unordered_set<char> aletters(A.begin(), A.end());

	//can have one double
	if (A == B && aletters.size() < B.size())
	{
		return true;
	}

	int count = 0;
	char diff = ' ';

	std::vector<int> index_diffs;
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
		{
			if (index_diffs.size() > 2)
			{
				return false;
			}

			index_diffs.push_back(i);
		}
	}

	if (index_diffs.size() < 2)
		return false;

	if (A[index_diffs[0]] == B[index_diffs[1]] &&
		A[index_diffs[1]] == B[index_diffs[0]])
	{
		return true;
	}

	return false;
}