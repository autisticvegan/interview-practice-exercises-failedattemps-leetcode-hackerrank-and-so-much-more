
#include <vector>
#include <stack>
#include <set>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
TreeNode* bstFromPreorder(std::vector<int>& preorder) {

	if (preorder.empty())
		return nullptr;

	std::stack<TreeNode*> node_Stack;

	TreeNode* maxNode = new TreeNode(INT_MAX);
	node_Stack.push(maxNode);

	for (int i = 0; i < preorder.size(); ++i)
	{
		int val = preorder[i];
		int curVal = node_Stack.top()->val;

		if (val < curVal)
		{
			node_Stack.top()->left = new TreeNode(val);
			node_Stack.push(node_Stack.top()->left);
		}
		else
		{
			TreeNode* curr;
			do
			{
				curr = node_Stack.top();
				node_Stack.pop();
			} while (node_Stack.top()->val < val);

			curr->right = new TreeNode(val);
			node_Stack.push(curr->right);
		}
	}

	return maxNode->left;
}

	int main(void)
	{
		std::vector<int> t{ 8,5,1,7,10,12 };
		TreeNode* g = bstFromPreorder(t);
		return 0;
	}