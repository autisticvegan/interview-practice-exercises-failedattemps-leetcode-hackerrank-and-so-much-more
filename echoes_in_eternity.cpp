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
	std::string smallestSubsequence(std::string text) {

		//idea: first, count occurences of each letter
		//also have a used set
		// build a string:
		// for each letter, if weve used it already, continue
		// while we still have letters left of that type and res.back() is less
		// than that letter (lexigraphically) and res is not empty,
		// pop back on res and remove that letter that you popped from the used set
		// push the letter onto res


		std::string result;

		std::unordered_map<char, int> count;
		std::unordered_set<char> used;

		for (int i = 0; i < text.size(); ++i) {
			count[text[i]]++;
		}

		for (int i = 0; i < text.size(); ++i) {

			count[text[i]]--;
			if (used.count(text[i]) > 0) continue;

			used.insert(text[i]);

			while (!result.empty() && result.back() > text[i] &&
				count[result.back()] > 0) {

				if (used.count(result.back())) {
					used.erase(result.back());
				}
				result.pop_back();

			}

			result.push_back(text[i]);
		}

		return result;
	}


	TreeNode* sufficientSubset(TreeNode* root, int limit) {

		//idea, traverse down tree, if you hit a leaf,
		//check if its less than limit.  if its not, return root
		//else return the null
		//as we are traversing, subtract root vals from limit
		//remember we have to do the 1st step twice

		if (!root)
			return nullptr;

		if (!root->left && !root->right) {
			if (root->val < limit) {
				return nullptr;
			}
			else {
				return root;
			}
		}

		if (root->left) {
			root->left = sufficientSubset(root->left, limit - root->val);
		}

		if (root->right) {
			root->right = sufficientSubset(root->right, limit - root->val);
		}

		if (!root->left && !root->right) {
			return nullptr;;
		}

		return root;
	}
};