


#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


std::vector<std::string> below10{"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
std::vector<std::string> below20{"Ten" "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
std::vector<std::string> below100{"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
std::vector<std::string> extras{ " ", " Hundred ", " Thousand ", "Million " };


std::string helper(int x) {
	std::string res;

	if (x < 10) {
		res = below10[x];
	}
	else if (x < 20) {
		res = below20[x - 10];
	}
	else if (x < 100) {
		res = below100[x / 10] + extras[0] + helper(x % 10);
	}
	else if (x < 1000) {
		res = helper(x / 100) + extras[1] + helper(x % 100);
	} ... etc



	return res;
}

std::string intToEnglish(int x) {

	if (x == 0) {
		return "Zero";
	}
	return helper(x);
}


int maxprofit(std::vector<int>& p) {
	int minPrice = p[0];
	int maxProfit = 0;
	for (const auto& i : p) {
		maxProfit = std::max(maxProfit, i - minPrice);
		minPrice = std::min(minPrice, i);
	}
	return maxProfit;
}

//integer to english
//triangle counting

int countValidTriangles(std::vector<int>& sides) {
	
	int count = 0;
	std::sort(sides.begin(), sides.end());
	
	for (int i = 2; i < sides.size(); ++i) {
		
		int left = 0;
		int right = i - 1;

		while (left < right) {
			if (nums[left] + nums[right] > nums[i]) {
				count += right - left;
				--right;
			}
			else {
				++left;
			}
		}

	}

	
	return count;
}


//merge arrays

//maximal square
int maximalSquareAMAZONPEEPEE(std::vector<std::vector<int>>& m) {

	int count = 0;

	//formula: if 1, dp = min of all 3 + 1
	// count = max(count, dp)
	std::vector<std::vector<int>> dp(m.size(), std::vector<int>(m[0].size()));
	for (int i = 1; i <= m.size(); ++i) {
		for (int j = 1; j <= m[0].size(); ++j) {
			if (m[i - 1][j - 1] == 1) {
				dp[i][j] = std::min(std::min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
				count = std::max(count, dp[i][j]);
			}
		}
	}

	return count * count;
}


// DO THIS OR DIE TRYING
int decodeWays(std::string& s) {
	
	std::vector<int> dp(s.size() + 2);
	dp[1] = 1;

	for (int i = 0; i < s.size(); ++i) {
		//1, 2

		if (s[i] != '0') {
			dp[i + 2] += dp[i + 1];
		}

		if (i != 0) {
			int num = (s[i - 1] - '0') * 10 + (s[i] - '0');
			if (num >= 10 && num <= 26) {
				dp[i + 2] += dp[i];
			}
		}
	}

	return dp.back();

}

// YOU SHALL NOT PASSSSSSSSSSSSSSSS
int decodeWays(std::string& s) {

	std::vector<int> dp(s.size() + 2);
	dp[1] = 1;

	for (int i = 0; i < s.size(); ++i) {
		//1 case, not a 0, if it is, dp += i+1

		if (s[i] != '0') {
			dp[i + 2] += dp[i + 1];
		}

		if (i != 0) {
			int num = (s[i - 1] - '0') * 10 + (s[i] - '0');
			if (num >= 10 && num <= 26) {
				dp[i + 2] += dp[i];
			}
		}

		//2 char case, check if num >= 10 and <= 26
		// if it is , dp += i
	}


	return dp.back();


}












int decodeWays(std::string& s) {

	std::vector<int> dp(s.size() + 2, 0);
	dp[1] = 1;

	for (int i = 0; i < s.size(); ++i) {
		//1
		if (s[i] != '0') {
			dp[i + 2] += dp[i + 1];
		}

		// 2
		if (i != 0) {
			
			int num = (s[i - 1] - '0') * 10 + (s[i] - '0');
			//between 10 and 26
			if (num >= 10 && num < 27) {
				dp[i + 2] += dp[i];
			}

		}

	}

	return dp.back();
}


std::string RevOnlyAlph(std::string& in) {
	
	int front = 0;
	int back = in.size() - 1;

	while (front < back) {

			while (front < back && in[front] == '-') {
				++front;
			}

			while (back > front && in[back] == '-') {
				--back;
			}

			std::swap(in[front], in[back]);

			++front;
			--back;
	}

	return in;
}
//decode ways

// count 1s in range
// segment tree or prefix sum
// the whitestripes, the strokes, the hives, the vines, the led zeppelins, the sums

std::vector<int> BuildSums(std::vector<int>& arr) {
	std::vector<int> retu(arr.size());
	int count = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == 1) {
			++count;
		}
		retu[i] = count;
	}
	return retu;
}

int query(int start, int end, std::vector<int>& arr, std::vector<int>& sums) {
	if (start < 0 || end >= arr.size()) {
		return -1;
	}

	return sums[end] - sums[start];
}


int main(void) {

	std::string t = "ab-cd-de";;
	std::string tt = "abcd-ef-ga";
	std::string ttt = "-------";
	std::string t4 = "--arcuhe--";
	std::string t5 = "";
	std::string t6 = "abc-def-ghijkl-";

	RevOnlyAlph(t);
	RevOnlyAlph(tt);
	RevOnlyAlph(ttt);
	RevOnlyAlph(t4);
	RevOnlyAlph(t5);
	RevOnlyAlph(t6);

	return 0;
}