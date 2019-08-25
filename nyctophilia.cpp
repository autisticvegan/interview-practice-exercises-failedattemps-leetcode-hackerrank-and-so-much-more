vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {

	//go through twice, subtracting ends and adding fronts
	//then carry through
	std::vector<int> res(n);

	for (auto& v : bookings) {
		res[v[0] - 1] += v[2];

		if (v[1] < n) {
			res[v[1]] -= v[2];
		}
	}

	for (int i = 1; i < n; ++i) {
		res[i] += res[i - 1];
	}

	return res;


}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

	int globalMax = INT_MIN;

	int maxPathSum(TreeNode* root) {

		helper(root);
		return globalMax;
	}

	int helper(TreeNode* node) {
		if (!node) {
			return 0;
		}

		int left = std::max(helper(node->left), 0);
		int right = std::max(helper(node->right), 0);

		globalMax = std::max(globalMax, left + right + node->val);

		return std::max(left, right) + node->val;
	}

};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

	TreeNode* helper(TreeNode* node,
		bool isRoot,
		std::vector<TreeNode*>& res,
		std::unordered_set<int>& s) {

		if (!node)
			return nullptr;

		bool deleteThis = s.count(node->val);
		if (isRoot && !deleteThis) {
			res.push_back(node);
		}

		node->left = helper(node->left, deleteThis, res, s);
		node->right = helper(node->right, deleteThis, res, s);

		return deleteThis ? nullptr : node;
	}

	vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
		std::unordered_set<int> s;
		for (int i = 0; i < to_delete.size(); ++i) {
			s.insert(to_delete[i]);
		}
		std::vector<TreeNode*> res;
		helper(root, true, res, s);
		return res;
	}
};