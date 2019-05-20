#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <stack>
#include <deque>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>

 struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

 int findUnsortedSubarray(std::vector<int>& nums) {

	 // look at whole array
	 // go from both sides
	 int minSoFar = INT_MAX;
	 int maxSoFar = INT_MIN;
	 int end = 0;
	 int begin = -1;

	 for (int i = 0, j = nums.size() - 1;
		 i < nums.size(); ++i, --j) {

		 maxSoFar = std::max(maxSoFar, nums[i]);
		 if (maxSoFar != nums[i]) {
			 begin = i;
		 }

		 minSoFar = std::min(minSoFar, nums[j]);
		 if (minSoFar != nums[j]) {
			 end = j;
		 }
	 }

	 return begin - end + 1;
 }

 // idea: use kmp:
// basically its O(m + n) rather than O(m*n)
// it checks if prefix matches suffix of a non-matching pattern
// saves prefix in table, so we don't have to go backwards
// all the way each time a match is not found

// find first matching spot, if its not 0, then + 1
// then length * x > total length of B
 int repeatedStringMatch(std::string a, std::string b) {
	 std::vector<int> prefTable(b.size() + 1); // 1-based to avoid extra checks.
	 for (auto sp = 1, pp = 0; sp < b.size();) {
		 if (b[pp] == b[sp]) {
			 pp = pp + 1;
			 prefTable[++sp] = pp;
		 }
		 else if (0 == pp) {
			 prefTable[++sp] = 0;
		 }
		 else {
			 pp = prefTable[pp];
		 }
	 }
	 for (auto i = 0, j = 0; i < a.size(); i += max(1, j - prefTable[j]), j = prefTable[j]) {
		 while (j < b.size() && a[(i + j) % a.size()] == b[j]) ++j;
		 if (j == b.size()) return (i + j) / a.size() + ((i + j) % a.size() != 0 ? 1 : 0);
	 }
	 return -1;
 }

 // idea: prime factors added together
 int minSteps(int n) {

	 int res = 0;
	 for (int k = 2; k <= n; k++) {
		 for (; n % k == 0; n /= k) {
			 res += k;
		 }
	 }
	 return res;
 }

int helper(TreeNode* root, int max, int min) {
	if (!root) {
		return max - min;
	}
	max = std::max(max, root->val);
	min = std::min(min, root->val);
	return std::max(helper(root->left, max, min), helper(root->right, max, min));
}

// greatest difference, so need max and min    
int maxAncestorDiff(TreeNode* root) {
	return helper(root, 0, INT_MAX);
}

int main(void) {

	return 0;
}