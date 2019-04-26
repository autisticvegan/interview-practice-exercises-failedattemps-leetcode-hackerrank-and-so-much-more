// SQL for finding shortest distance for 1D: 
// 	
// SELECT MIN(p2.x - p1.x) AS shortest FROM point AS p1, point AS p2 WHERE p1.x < p2.x;
// We do not need ABS because the list is sorted, and we are iterating in a direction ( WHERE p1.x < p2.x )
//
// Other leetcode problems here: Range of Sum BST, Remove Outermost Parentheses, Squares of a sorted array
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>
#include <iostream>
#include <sstream>

std::vector<int> sortedSquares(std::vector<int>& A) {
	// idea: 2 pointers, one for the negatives, one for the positives
	// runtime: O(N), space: (O(N))
	// use abs to check which is bigger so we know which to sort
	// go from back to front (biggest to smallest)
	std::vector<int> result(A.size());

	for (int posPointer = A.size() - 1,
		negPointer = 0,
		current = A.size() - 1;
		negPointer <= posPointer;
		--current) {

		bool isNegSmallerThanPos = std::abs(A[negPointer]) < std::abs(A[posPointer]);
		int posVal = A[posPointer];
		int negVal = A[negPointer];

		int res = -1;
		if (isNegSmallerThanPos) {
			res = posVal * posVal;
			--posPointer;
		}
		else {
			res = negVal * negVal;
			++negPointer;
		}
		result[current] = res;
	}
	return result;
}

std::string removeOuterParentheses(std::string S) {
	// What we want-everything except the first and last open and close
	// this means, is we check open and close paretheses, and if they arent the first
	// or last, we put them in our result

	std::string res;

	int openCount = 0;
	for (const auto& c : S) {
		if (c == '(' && openCount++ > 0) {
			res += "(";
		}
		else if (c == ')' && openCount-- > 1) {
			res += ")";
		}
	}

	return res;
}

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// idea: need to find "straddle" point.  If we can find straddle point, then we can
// add up the left and right sides, plus the root, to get the answer.
// remember when we split to set the bounds as the root val.
// if our straddle point is on the left, go left, if it is on the right, go right

//     10
//   5       15
// 3   7   x     18
int rangeSumBST(TreeNode* root, int L, int R) {

	if (!root) {
		return 0;
	}

	if (root->val > R) {
		return rangeSumBST(root->left, L, R);
	}
	else if (root->val < L) {
		return rangeSumBST(root->right, L, R);
	}
	else {
		return root->val + rangeSumBST(root->left, L, root->val) + rangeSumBST(root->right, root->val, R);
	}
}

// anagram mapping (premium problem so have to do it myself)
std::vector<int> findAnagramMapping(std::vector<int>& A, std::vector<int>& B) {
	
	std::unordered_map<int, int> intsToIndices;
	
	int index = 0;
	for (const auto& i : B) {
		intsToIndices.insert( {i, index++})
	}

}


int main(void)
{
	return 0;
}
