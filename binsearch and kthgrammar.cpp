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
 
 int kthGrammar(int N, int K) {

	 int nM = N - 1;
	 bool odd = K % 2;

	 if (N == 1) return 0;
	 else if (!odd) return kthGrammar(nM, K / 2) ? 0 : 1;
	 else return kthGrammar(nM, (K + 1) / 2) ? 1 : 0;
 }

 int search(std::vector<int>& nums, int target) {

	 int high = nums.size() - 1;
	 int low = 0;

	 while (low <= high)
	 {
		 int mid = low + (high - low) / 2;

		 if (nums[mid] == target)
			 return mid;
		 else if (nums[mid] > target)
		 {
			 high = mid - 1;
		 }
		 else
		 {
			 low = mid + 1;
		 }
	 }

	 return -1;
 }

int main(void)
{

	return 0;
}