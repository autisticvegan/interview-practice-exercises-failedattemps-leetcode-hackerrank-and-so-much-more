#include <string>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <numeric>

//Determine the number of pairs of similar strings.
//similar means differing by one letter.
//all strings are same length
//run time should be less than exponential

//Can use long longs for hackerrank style

// Handshake formula = n(n-1)/2
int HandShake_Algorithm(std::unordered_map<std::string, int>& m)
{
	return std::accumulate(m.begin(), m.end(), 0,
		[](auto a, auto b) {int t = a + (b.second * (b.second - 1)) / 2;
	return t; });
}

int Similar_Strings(std::vector<std::string> input)
{
	int size = input.size();

	//idea, insert into a new hash table strings that have 1 letter substituted.
	//for example:
	// abc
	// abd
	// bbd
	// answer would be 2, for abc create strings -> ?bc, a?c, ab? ... etc
	std::unordered_map<std::string, int> substituted;
	std::unordered_map<std::string, int> original;
	
	for (std::string& s : input)
	{
		original[s]++;

		for (int i = 0; i < s.length(); ++i)
		{
			char reCopy = s[i];
			s[i] = '?';
			substituted[s]++;
			s[i] = reCopy;
		}
	}

	int sub = HandShake_Algorithm(substituted);
	int old = HandShake_Algorithm(original) * size;
	return sub - old;
}


int main(void)
{
	std::vector<std::string> tt = { "abc", "abd", "bbd" };
	int t = Similar_Strings(tt);
	return 0;
}