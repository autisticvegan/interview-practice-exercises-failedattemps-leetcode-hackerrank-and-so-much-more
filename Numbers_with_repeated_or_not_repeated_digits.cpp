#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_set>
// Formula:
/*

T(N) = the number of positive integers less than or equal to N that have at least 1 repeated digit.
S(N) = the number of positive integers less than or equal to N that have NO repeated digits.
T(N) = N - S(N)


*/
int numDupDigitsAtMostN(int N)
{
	// All numbers less don't have repeated digits
	if (N <= 10)
		return 0;

	// count up number of digits
	int digitLength = 0;
	for (int i = N; i > 0; i /= 10) 
		++digitLength;

	int noDupBaseSum = 0;
	std::vector<int> noDupBase(digitLength - 1, 0);

	// Get S[n] for up to digitLength - 1
	for (int i = 0; i < digitLength - 1; i++)
	{
		noDupBase[i] = i == 0 ? 9 : noDupBase[i - 1] * (10 - i);
		noDupBaseSum += noDupBase[i];
	}


	std::vector<int> digit(digitLength, 0);

	// Fill digit with each of our digits
	for (int i = 0, j = N; i < digitLength; i++, j /= 10)
		digit[digitLength - 1 - i] = j % 10;

	// Now, all  we need to do is calculate the last part of S[n]
	std::unordered_set<int> digitCount;
	std::vector<int> noDupRes(digitLength, 0);

	bool duplicate = false;
	for (int i = 0; i < digitLength; i++)
	{
		noDupRes[i] = i == 0 ? 9 : noDupRes[i - 1] * (10 - i);
		if (!duplicate)
		{
			int diff = 0;
			//if we haven't seen this digit before, add one to the diff
			for (int j = digit[i] + 1; j < 10; j++)
			{
				if (digitCount.count(j) == 0)
				{
					++diff;
				}
			}
			
			noDupRes[i] -= diff;

			if (digitCount.count(digit[i]))
			{
				duplicate = true;
			}
			else
			{
				digitCount.insert(digit[i]);
			}
		}
	}
	// Recall original formula
	return N - (noDupBaseSum + noDupRes[digitLength - 1]);
}
int main(void)
{
	numDupDigitsAtMostN(55674);
	return 0;
}