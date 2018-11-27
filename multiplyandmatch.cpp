#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>
#include <istream>
#include <iterator>
#include <iostream>
#include <sstream>
#include <deque>

bool isMatch(std::string s, std::string p)
{
	int i = 0;
	int j = 0;
	int asterisk = -1; //need to check if >= 0, not the first
	int match = -1;
	//greedy algorithim, no dp needed
	while (i < s.length())
	{//3 cases: either star, match or ?, else repeated asterisk
		if (j < p.size() && p[j] == '*')
		{//update match and asterisk
			match = i;
			asterisk = j++;
		}
		else if (j < p.size() && (s[i] == p[j] || p[j] == '?'))
		{//business as usual
			++i;
			++j;
		}
		else if (asterisk >= 0)
		{//update i and j
			i = match;
			j = asterisk + 1;
			++match;
		}
		else
		{
			return false;
		}
	}

	//finish off trailing stars
	while (j < p.size() && p[j] == '*')
		++j;

	return j == p.size();

}

//terrible bloated solution
std::string multiply(std::string num1, std::string num2) {

	if (num1.length() < num2.length())
		std::swap(num1, num2);

	if (num1.empty() || num2.empty())
		return "0";

	if (num1 == "0" || num2 == "0")
		return "0";

	//i is for longer, top number (num1)
	//j is for shorter, bottom number (num2)

	//each iteration, add running total

	std::string result;

	int zerocount = 0;
	std::deque<int> temp;

	for (int j = num2.size() - 1; j >= 0; --j)
	{
		std::deque<int> prev = temp;
		temp.clear();
		for (int k = 0; k < zerocount; ++k)
			temp.push_front(0);

		int carry = 0;
		for (int i = num1.size() - 1; i >= 0; --i)
		{//could also do vector then index reverse
			int r = (num1[i] - '0') * (num2[j] - '0');
			r += carry;
			if (r > 9)
			{
				carry = r / 10;
				r %= 10;
			}
			else
			{
				carry = 0;
			}
			temp.push_front(r);
		}//instead of zerocount could use j 

		if (carry > 0)
		{
			temp.push_front(carry);
		}

		++zerocount;
		//add into result
		if (!prev.empty())
		{
			int z = prev.size() - 1;
			int acarry = 0;
			for (int k = temp.size() - 1; k >= 0; --k)
			{
				int t = 0;
				if (z < 0)
				{
					t = temp[k] + acarry;
				}
				else
				{
					t = temp[k] + prev[z] + acarry;

					--z;
				}


				if (t > 9)
				{
					temp[k] = t % 10;

					acarry = t / 10;

				}
				else
				{
					temp[k] = t;
					acarry = 0;
				}


			}

			if (acarry > 0)
				temp.push_front(acarry);
		}
	}

	//add in temp final time
	for (int i = 0; i < temp.size(); ++i)
	{
		result.push_back(temp[i] + '0');
	}

	return result;
}

int main(void)
{
	multiply("123", "456");

	return 0;
}