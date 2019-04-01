#include <string>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <queue>
#include <set>

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
 bool isUnivalTree(TreeNode* root) {

	 std::queue<TreeNode*> node_queue;

	 if (!root)
		 return true;



	 node_queue.push(root);
	 std::unordered_set<int> s;
	 s.insert(root->val);
	 while (!node_queue.empty())
	 {
		 int iterations = node_queue.size();

		 for (int i = 0; i < iterations; ++i)
		 {
			 TreeNode* t = node_queue.front();
			 node_queue.pop();

			 if (s.count(t->val) == 0)
				 return false;

			 if (t->left)
				 node_queue.push(t->left);

			 if (t->right)
				 node_queue.push(t->right);

		 }
	 }

	 return true;
 }
 void DFS(std::vector<std::vector<int>>& image, int sr, int sc, int oc, int nc)
 {
	 if (sr < 0 || sc < 0 || sr >= image.size() || sc >= image[0].size() || image[sr][sc] != oc)
		 return;

	 image[sr][sc] = nc;

	 DFS(image, sr + 1, sc, oc, nc);
	 DFS(image, sr - 1, sc, oc, nc);
	 DFS(image, sr, sc + 1, oc, nc);
	 DFS(image, sr, sc - 1, oc, nc);
 }

 std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor) {

	 if (image[sr][sc] != newColor)
		 DFS(image, sr, sc, image[sr][sc], newColor);
	 return image;
 }

int main(void)
{

	return 0;
}