//amazon questions
// triangle one
// integer to english
// maximal square

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cctype>


/*

problems with amazon interviewers:
1. They said I could code on computer before interview, then during interview they insisted I code on whiteboard.
2. They didn't correct me when I asked about the function signature or when I said things like "This sounds like a dp problem".
3. leadership principles LOL

*/

//dynamic programming problem
int maximalSquare(std::vector<std::vector<int>>& in) {

	
	std::vector<std::vector<int>> dp(in.size(), std::vector<int>(in[0].size()));
	int result = 0;
	for (int i = 1; i < in.size(); ++i) {
		for (int j = 1; j < in[0].size(); ++j) {
			if (in[i - 1][j - 1] == 1) {
				dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
				result = std::max(result, dp[i][j]);
			}
		}
	}



	return result * result;

}

int numberOfTriangles(std::vector<int>& triangleSides) {

	//2 pointers
	std::sort(triangleSides.begin(), triangleSides.end());
	int total = 0;

	for (int i =2; i < triangleSides.size(); ++i) {

		int left = 0;
		int right = i - 1;

		while (left < right) {

			if (triangleSides[left] + triangleSides[right] > triangleSides[i]) {
				total += right - left;
				--right;
			}
			else {
				++left;
			}

		}


	}
	return total;
}

class Solution3 {
public:

	static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	std::vector<std::string> below10{ "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
	//special case
	std::vector<std::string> below20{ "Ten" , "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	std::vector<std::string> below100{ "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
	std::vector<std::string> extras{ " ", " Hundred ", " Thousand ", " Million ", " Billion " };

	std::string intToEnglishHelper(int x) {



		std::string result;

		if (x < 10) {
			result = below10[x];
		}
		else if (x < 20) {
			result = below20[x - 10];
		}
		else if (x < 100) {
			result = below100[x / 10] + extras[0] + intToEnglishHelper(x % 10);
		}
		else if (x < 1000) {
			result = intToEnglishHelper(x / 100) + extras[1] + intToEnglishHelper(x % 100);
		}
		else if (x < 1000000) {
			result = intToEnglishHelper(x / 1000) + extras[2] + intToEnglishHelper(x % 1000);
		}
		else if (x < 1000000000) {
			result = intToEnglishHelper(x / 1000000) + extras[3] + intToEnglishHelper(x % 1000000);
		}
		else {
			result = intToEnglishHelper(x / 1000000000) + extras[4] + intToEnglishHelper(x % 1000000000);
		}

		rtrim(result);
		return result;
	}




	std::string numberToWords(int x) {

		if (x == 0) {
			return "Zero";
		}
		return intToEnglishHelper(x);
	}

};
//bullshit random thing 2 ways

int main(void) {

	//1234567
	//numberToWords(1234567);
	return 0;
}