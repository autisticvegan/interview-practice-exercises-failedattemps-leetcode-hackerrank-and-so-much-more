#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>

std::vector<int> grayCode(int n) {
	//print gray code sequence starting with 0
	// idea: use /2 and xor
	std::vector<int> ans;
	int end = 1 * std::pow(2, n);
	for (int i = 0; i < end; ++i) {
		int div = i / 2;
		ans.push_back(i ^ div);
	}
	return ans;
}

void helper(int currentIndex, bool pickLast, std::vector<int>& nums, std::vector<int>& t, std::vector<std::vector<int>>& res) {

	if (currentIndex == nums.size()) {
		res.push_back(t);
	}
	else {
		t.push_back(nums[currentIndex]);
		helper(currentIndex + 1, true, nums, t, res);
		t.pop_back();

		if (currentIndex > 0 && nums[currentIndex - 1] == nums[currentIndex] && pickLast) {
			return;
		}
		helper(currentIndex + 1, false, nums, t, res);

	}
}

std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {


	//plan: sort, then use dfs (push pop). to speed up, check if the previous 
	//choice was the same as the current choice AND picklast is true.
	//picklast is set to true on the first recurse call, and false on the second
	//so we have this pattern: 
	// NNN (choose)
	// NNX (choose)
	// NXX (choose)
	// XXX (choose)
	// all others like NXN etc dont choose

	std::vector<std::vector<int>> res;
	std::vector<int> t;
	std::sort(nums.begin(), nums.end());
	helper(0, false, nums, t, res);


	return res;
}


bool isScramble(std::string s1, std::string s2) {

	std::unordered_map <char, int> s1m;
	std::unordered_map <char, int> s2m;

	if (s1.length() != s2.length())
		return false;

	for (int i = 0; i < s1.size(); ++i) {
		s1m[s1[i]]++;
		s2m[s2[i]]++;
	}

	if (s1m.size() != s2m.size())
		return false;

	for (const auto t : s1m) {
		if (t.second != s2m[t.first])
			return false;
	}

	if (s1 == s2)
		return true;

	int aLen = s1.size();

	for (int i = 1; i < s1.size(); i++) {


		std::string FrontS1 = s1.substr(0, i);
		std::string BackS1 = s1.substr(i);

		std::string frontS2 = s2.substr(0, i);
		std::string backS2 = s2.substr(i);

		// going in both directions.  above is left to right
		// below is right to left
		std::string backS2Right = s2.substr(aLen - i);
		std::string frontS2Right = s2.substr(0, aLen - i);

		if (isScramble(FrontS1, frontS2) && isScramble(BackS1, backS2)) {
			return true;
		}

		if (isScramble(FrontS1, backS2Right) && isScramble(BackS1, frontS2Right)) {
			return true;
		}
	}
	return false;
}

using namespace std;
int maximalRectangle(vector<vector<char>>& matrix) {

	if (matrix.size() == 0 || matrix[0].size() == 0)
		return 0;

	int cLen = matrix[0].size();    // column length
	int rLen = matrix.size();       // row length
	std::vector<int> height(cLen + 1);
	height[cLen] = 0;
	int max = 0;

	//go row by row
	 // stack will keep track of the last place we saw that height
	 // (so that we know the width)
	 // note that when we hit a 0, we will reset that column's height



	for (int row = 0; row < rLen; row++) {
		std::stack<int> s;

		for (int i = 0; i < cLen + 1; i++) {

			if (i < cLen) {
				if (matrix[row][i] == '1')
					height[i] += 1;
				else height[i] = 0;
			}


			if (s.empty() || height[s.top()] <= height[i])
				s.push(i);
			else {
				while (!s.empty() && height[i] < height[s.top()]) {

					int top = s.top();
					s.pop();
					int area = height[top] * (s.empty() ? i : (i - s.top() - 1));

					max = std::max(max, area);
				}
				s.push(i);
			}
		}
	}
	return max;
}

int maximalSquare(vector<vector<char>>& matrix) {
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return 0;

	std::vector<std::vector<int>> dp(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0));
	int result = 0;

	for (int i = 1; i <= matrix.size(); ++i) {
		for (int j = 1; j <= matrix[0].size(); ++j) {
			if (matrix[i - 1][j - 1] == '1') {
				dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
				result = std::max(result, dp[i][j]);
			}

		}
	}

	return result * result;
}

ListNode* partition(ListNode* head, int x) {
	//idea - go through, and pick up all values < and >=
	//
	if (head == nullptr)
		return nullptr;

	ListNode* mommy_head = new ListNode(0);
	ListNode* daddy_head = new ListNode(0);
	ListNode* mommy = mommy_head;
	ListNode* daddy = daddy_head;

	// walk head.  if head < x , mommy->next = head and mommy = mommy->next
	// else, similar for daddy.  daddy->next = head, daddy = daddy->next
	while (head != nullptr) {

		if (head->val < x) {
			mommy->next = head;
			mommy = mommy->next;

		}
		else {
			daddy->next = head;
			daddy = daddy->next;
		}

		head = head->next;

	}
	daddy->next = nullptr;

	//only place we use daddy head
	mommy->next = daddy_head->next;

	//only place we use mommy head
	return mommy_head->next;
}

int main(void) {

	std::vector<std::vector<char>> t {{'1','0','1','0','0'},
  {'1','0','1','1','1'},
  {'1','1','1','1','1'},
  {'1','0','0','1','0'} };

	maximalRectangle(t);


	return 0;
}