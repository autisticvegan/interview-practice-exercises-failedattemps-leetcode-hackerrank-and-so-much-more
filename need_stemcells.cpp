#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>







/*
e0 = current number of ways we could decode, ending on any number;
e1 = current number of ways we could decode, ending on an open 1;
e2 = current number of ways we could decode, ending on an open 2;

Also note thet < 7 because 26
	*/

int numDecodings(string s) {
	long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2;
	for (char c : s) {
		if ('*' == c) {
			f0 = 9 * e0 + 9 * e1 + 6 * e2;
			f1 = f2 = e0;
		}
		else {
			f0 = int(c > '0') * e0 + e1 + int(c < '7') * e2;
			f1 = '1' == c ? e0 : 0;
			f2 = '2' == c ? e0 : 0;
		}
		e0 = f0 % 1000000007;
		e1 = f1;
		e2 = f2;
	}
	return int(e0);
}








struct Log {
	int id;
	string status;
	int timestamp;
};


class Solution {
public:
	vector<int> exclusiveTime(int n, vector<string>& logs) {
		vector<int> times(n, 0);
		stack<Log> st;
		for (string log : logs) {
			stringstream ss(log);
			string temp, temp2, temp3;
			getline(ss, temp, ':');
			getline(ss, temp2, ':');
			getline(ss, temp3, ':');

			Log item = { stoi(temp), temp2, stoi(temp3) };

			//key here, use stack to keep track of previous "level"
			//if its start, just push it on stack
			// if not, then get time_added from end - start + 1
			// if stack is not empty, subtract that timeadded from the previous one

			if (item.status == "start") {
				st.push(item);
			}
			else {

				int timeAdded = item.timestamp - st.top().timestamp + 1;
				st.pop();
				times[item.id] += timeAdded;

				if (!st.empty()) {
					times[st.top().id] -= timeAdded;
				}

			}
		}

		return times;
	}
};




int decodeWays(std::string& s) {

	std::vector<int> dp(s.size() + 2);
	dp[1] = 1; //rest is 0

	for (int i = 0; i < s.size(); ++i) {

		//2 cases - if its not 0, then just add it 2 - 1
		// if i is not 0, then 2 cases, either 1 or 2 digits
		// if its 2 digits - num >= 10 and <= 26

		if (s[i] != '0') {
			dp[i + 2] += dp[i + 1];
		}

		if (i != 0) {
			int num = (s[i - 1] - '0') * 10 + (s[i] - '0');
			if (num >= 10 || num <= 26) {
				dp[i + 2] += dp[i];
			}
		}

	}


	return dp.back();
}


int countTriangles(std::vector<int>& nums) {

	int total = 0;

	std::sort(nums.begin(), nums.end());

	for (int i = 2; i < nums.size(); ++i) {

		int left = 0;
		int right = i - 1;
		while (left < right) {

			if (nums[left] + nums[right] > nums[i]) {
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


int maxSubarrayWithOneMissing(std::vector<int>& a) {

	std::vector<int> forwards(a.size());
	std::vector<int> backs(a.size());
	backs[a.size() - 1] = a[a.size() - 1];
	forwards[0] = a[0];

	int currMax = a[0];
	int maxSoFar = a[0];

	for (int i = 1; i < a.size(); ++i) {

		currMax = std::max(a[i], currMax + a[i]);
		maxSoFar = std::max(currMax, maxSoFar);
		forwards[i] = currMax;

	}

	currMax = a[a.size() - 1];
	maxSoFar = a[a.size() - 1];

	for (int i = a.size() - 2; i >= 0; --i) {
		currMax = std::max(a[i], currMax + a[i]);
		maxSoFar = std::max(currMax, maxSoFar);
		backs[i] = currMax;
	}

	int answer = currMax;
	for (int i = 1; i < a.size() - 1; ++i) {
		answer = std::max(answer, forwards[i - 1] + backs[i + 1]);
	}


	return answer;
}



int main(void) {

	std::vector<int> t{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> tt{ 1,-1,-5,-6,-7,-8,-9,10,-9,-1,99,-99,10 };

	return 0;
}