#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <climits>

int numofcoins(const std::vector<int>& coins, int target)
{
	//if needing the actual values, make 2 arrays
	//if we only count we can get by with just one
	//double for loop - do coinvalues, and target

	std::vector<int> T(target + 1, 0);

	for (int i = 1; i < T.size(); ++i)
	{
		T[i] = INT_MAX;
	}

	for (int j = 0; j < coins.size(); ++j)
	{
		for (int i = 1; i <= target; ++i)
		{
			if (i >= coins[j])
			{
				T[i] = std::min(T[i], 1 + T[i - coins[j]]);
			}
		}
	}

	return T[target];

	//if i >= coins[j]
	//dynamic programming problem
	//formula = T[i] = std::min(T[i], 1 + T[i - coins[j])

}

//grow for 2 years omg
//tips (lol)


int numofcoins(const std::vector<int>& coins, int target)
{
	std::vector<int> T(target + 1, INT_MAX);
	T[0] = 0;
	




	return T[target];
}





int main(void)
{
	int target;
	std::cin >> target;
	//target hardcoded
	std::vector<int> coins;
	coins.push_back(1);
	coins.push_back(2);
	coins.push_back(4);



	return 0;
}

bool CheckIfUnique(int num)
{
	std::unordered_set<int> myset;

	while (num > 0)
	{
		int test = num % 10;
		if (myset.count(test))
		{
			return false;
		}
		myset.insert(test);
		num /= 10;
	}


	return true;
}

//given a number, reverse it and add it as a sum
//if it has all unique, return, if not, keep doing it
//return the number of iterations and the final answer
std::pair<int, int> CountNumberOfIterationsToGetUnique(int input)
{
	std::pair<int, int> result;

	//could also use long longs here to prevent integer overflow
	std::string temp = std::to_string(input);
	std::reverse(temp.begin(), temp.end());
	int g = std::stoi(temp);
	int pass = g + input;
	
	int iterations = 1;
	bool isu = CheckIfUnique(pass);

	if (isu)
	{
		result.first = iterations;
		result.second = pass;
		return result;
	}

	while (!isu)
	{
		iterations++;

		std::string temp = std::to_string(pass);
		std::reverse(temp.begin(), temp.end());
		int g = std::stoi(temp);
		pass = g + pass;

		isu = CheckIfUnique(pass);
	}

	result.first = iterations;
	result.second = pass;
	return result;
	
}