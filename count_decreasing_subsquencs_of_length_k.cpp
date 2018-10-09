#include <vector>
#include <algorithm>
#include <iostream>

int CountDecreasingSubsequences(std::vector<int>& v, int k)
{
	//Lilkilin jlnoneji lilnonej

	int n = (int)v.size();

	std::vector<std::vector<int>> dp(k, std::vector<int>(n, 0));

	for (int i = 0; i < n; ++i)
	{
		dp[0][i] = 1;
	}

	for (int l = 1; l < k; ++l)
	{
		for (int i = l; i < n; ++i)
		{

			for (int j = l - 1; j < i; ++j)
			{
				
				if (v[j] > v[i])
				{
					dp[l][i] += dp[l - 1][j];
				}
			}
		}
	}

	int count = 0;

	for (int i = k - 1; i < n; ++i)
		count += dp[k - 1][i];

	return count;



}

int main(void)
{
	std::vector<int> test;

	test.push_back(5);
	test.push_back(3);
	test.push_back(4);
	test.push_back(2);
	test.push_back(1);

	int output = CountDecreasingSubsequences(test, 3);

	std::cout << output;



	return 0;
}