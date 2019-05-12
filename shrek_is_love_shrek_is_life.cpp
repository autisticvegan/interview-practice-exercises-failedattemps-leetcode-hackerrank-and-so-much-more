#include <queue>


#include <vector>
#include <algorithm>
#include <string>

 struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

 bool helper(std::string& s, int lowIndex, int highIndex, int diffCount) {

	 if (diffCount > 1) {
		 return false;
	 }

	 while (lowIndex < highIndex) {

		 if (s.at(lowIndex) == s.at(highIndex)) {

			 lowIndex++;
			 highIndex--;
		 }
		 else {
			 return (helper(s, lowIndex + 1, highIndex, diffCount + 1) ||
				 helper(s, lowIndex, highIndex - 1, diffCount + 1));
		 }

	 }
	 return true;
 }

 bool validPalindrome(std::string s) {
	 //idea, we can only differ by 1, so check until you
	 // find a diff.  if you find a diff, split into
	 // 2 functions, one where you delete the lower diff
	 // and one where you delete the upper diff.
	 // if count of function (going into recurse) is
	 // higher than k(which is 1 in this case), then 
	 // return false

	 return helper(s, 0, s.length() - 1, 0);
 }

int main(void) {

	std::string s;
	int t = 5;
	int tt = 1;
	int ttt = 2;
	int tttt = 0;

	int z = t & 1;
	int zz = tt & 1;
	int zzz = ttt & 1;
	int zzzz = tttt & 1;

	return 0;
}


int reachNumber(int target) {

	// can use sum formula to solve in O(1)

	//make sure target is positive for formula to work
	target = std::abs(target);

	// n will be the final biggest n from 1..2..n to be bigger than
	// target.  Note this is like solving a quadratic equation 
	// -b + sqrt(b^2 - 4ac) / 2a
	// THATS THE TRICK.jpg
	long long n = std::ceil((-1 + sqrt(1 + 8.0 * target)) / 2);
	long long sum = n * (n + 1) / 2;

	if (sum == target) {
		return n;
	}

	long long remaining = sum - target;

	bool remainingIsOdd = remaining & 1;

	if ((sum == target) || !remainingIsOdd)
		return n;

	bool nIsOdd = n & 1;

	return n + (nIsOdd ? 2 : 1);
}

std::vector<double> averageOfLevels(TreeNode* root) {



	std::queue<TreeNode*> nodeQueue;

	std::vector<double> res;

	if (!root)
		return res;

	nodeQueue.push(root);

	while (!nodeQueue.empty()) {

		double avg = 0;

		int iterations = nodeQueue.size();


		for (int i = 0; i < iterations; ++i) {

			TreeNode* t = nodeQueue.front();
			nodeQueue.pop();

			if (t->left) {
				nodeQueue.push(t->left);
			}

			if (t->right) {
				nodeQueue.push(t->right);
			}

			avg += t->val;
		}

		avg /= iterations;

		res.push_back(avg);
	}


	return res;
}

// turns 1s to 0s, and 0s to 1s
int flip(int in) {
	return 1 - in;
}

bool hasAlternatingBits(int n) {
	int lastBit = n & 1;

	while ((n & 1) == lastBit) {
		lastBit = flip(lastBit);
		n >>= 1;
	}
	return n == 0;
}