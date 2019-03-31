#include <string>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <queue>

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 

	bool isCommonParent(TreeNode* root, int x, int y)
	{
		std::unordered_set<int> t{ x,y };

		if (root->left != nullptr && root->right != nullptr &&
			((root->left->val == x && root->right->val == y) ||
			(root->left->val == y && root->right->val == x)))
			return true;

		return false;
	}

	bool isCousins(TreeNode* root, int x, int y) {

		//idea: level order traversal.
		//when checking each node, make sure its children are not x and y,
		//if they are, return false
		//when through a level, make sure the set contains x and y, if so, return true

		if (root == nullptr)
			return false;

		std::queue<TreeNode*> node_Queue;
		node_Queue.push(root);

		while (!node_Queue.empty())
		{
			std::unordered_set<int> set_of_nodes;
			int iterations = node_Queue.size();

			for (int i = 0; i < iterations; ++i)
			{
				TreeNode* t = node_Queue.front();
				node_Queue.pop();

				if (isCommonParent(t, x, y))
					return false;

				set_of_nodes.insert(t->val);

				if (t->left)
					node_Queue.push(t->left);

				if (t->right)
					node_Queue.push(t->right);

			}

			if (set_of_nodes.count(x) && set_of_nodes.count(y))
				return true;
		}

		return false;
	}


int main(void)
{

	return 0;
}