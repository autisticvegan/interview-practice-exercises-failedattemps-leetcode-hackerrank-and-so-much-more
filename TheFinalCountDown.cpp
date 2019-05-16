#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

int twoCitySchedCost(std::vector<std::vector<int>>& costs) {
	//idea: difference between going to a and b
	// sort in order, with the front half going to a,
	// and the latter half going to b.

	// can sort with only nth_element
	std::partial_sort(costs.begin(),
		costs.begin() + costs.size() / 2,
		costs.end(),
		[](std::vector<int>& left,
			std::vector<int>& right) {
				return (left[0] - left[1] < right[0] - right[1]);
		});

	int res = 0;
	for (int i = 0; i < costs.size() / 2; ++i) {
		res += costs[i][0];
	}

	for (int i = costs.size() / 2; i < costs.size(); ++i) {
		res += costs[i][1];
	}

	return res;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

bool isLeaf(TreeNode* node) {
	return (!node->left && !node->right);
}

int helper(TreeNode* root, int currSum) {
	if (!root) {
		return 0;
	}
	currSum = 2 * currSum + root->val;

	if (isLeaf(root)) {
		return currSum;
	}

	return helper(root->left, currSum) + helper(root->right, currSum);
}

int sumRootToLeaf(TreeNode* root) {
	return helper(root, 0);
}

int main(void) {
	return 0;
}