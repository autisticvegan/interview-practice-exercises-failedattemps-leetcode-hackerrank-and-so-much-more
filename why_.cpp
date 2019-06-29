#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>

TreeNode* getZucc(TreeNode* t) {

	if (!t)
		return nullptr;

	TreeNode* z = t->right;
	while (z && z->left && z->left != t) {
		z = z->left;
	}

	return z;
}

TreeNode* convertBST(TreeNode* root) {

	TreeNode* t = root;

	int sum = 0;

	while (t) {
		if (t->right == nullptr) {
			sum += t->val;
			t->val = sum;
			t = t->left;
		}
		else {
			TreeNode* s = getZucc(t);



			if (s->left == nullptr) {
				s->left = t;
				t = t->right;
			}
			else {
				s->left = nullptr;
				sum += t->val;
				t->val = sum;
				t = t->left;
			}

		}

	}
	return root;
}

int maxIncreaseKeepingSkyline(std::vector<std::vector<int>>& grid) {

	//idea, need to g et the tallest for rows and cols
	// as in, the skyline
	// then go through and take min - grid , summed up

	std::vector<int> rows(grid.size());
	std::vector<int> cols(grid.size());

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.size(); ++j) {
			rows[i] = std::max(rows[i], grid[i][j]);
			cols[j] = std::max(cols[j], grid[i][j]);
		}
	}

	int res = 0;

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.size(); ++j) {
			res += std::min(rows[i], cols[j]) - grid[i][j];
		}
	}


	return res;
}


int main(void) {


	return 0;
}