/*

*/
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <optional>

int calPoints(std::vector<std::string>& ops) {

	int sum = 0;
	int scoreForThisRound = 0;
	std::vector<int> roundScores;

	for (const auto& o : ops) {

		if (o == "C") {
			sum -= roundScores.back();
			roundScores.pop_back();
			continue;
		}
		else if (o == "D") {
			scoreForThisRound = 2 * roundScores.back();
		}
		else if (o == "+") {
			size_t s = roundScores.size();
			scoreForThisRound = roundScores[s - 2] + roundScores[s - 1];
		}
		else {
			scoreForThisRound = std::stoi(o);
		}


		sum += scoreForThisRound;
		roundScores.push_back(scoreForThisRound);
	}
	return sum;

}

bool canPermutePalindrome(std::string& s) {
	std::unordered_map<char, int> m;

	for (int i = 0; i < s.length(); ++i) {
		m[s[i]]++;
	}

	int count = 0;

	for (const auto& p : m) {
		count += p.second % 2;
	}

	//if more than 1 odd, its not possible to have a palindrome
	return count <= 1;
}


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};


TreeNode* trimBST(TreeNode* root, int L, int R) {

	// first, find root by going between L and R

	while (root && (root->val < L || root->val > R)) {

		if (root->val < L) {
			root = root->right;
		}
		else {
			root = root->left;
		}
	}

	if (!root)
		return nullptr;

	TreeNode* leftSide = root;
	TreeNode* rightSide = root;

	//symmetric

	// remove left garbage
	// go left until we hit boundary, then go right
	while (leftSide && leftSide->left) {

		if (leftSide->left->val < L) {
			leftSide->left = leftSide->left->right;
		}
		else {
			leftSide = leftSide->left;
		}
	}

	while (rightSide && rightSide->right) {

		if (rightSide->right->val > R) {
			rightSide->right = rightSide->right->left;
		}
		else {
			rightSide = rightSide->right;
		}
	}

	// remove right garbage
	// go right until we hit boundary, then go left
	return root;
}

/*
Area of triangle formula:
x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)


*/

bool isBoomerang(std::vector<std::vector<int>>& p) {
	return p[0][0] * (p[1][1] - p[2][1]) + p[1][0] * (p[2][1] - p[0][1]) + p[2][0] * (p[0][1] - p[1][1]) != 0;
}

//max size is 32 bit number, so only need primes up to 31
// bool[32] = 665772
// also using intrinsics (thanks stefan)
// could just hardcode the primes and see if they exist

int countPrimeSetBits(int L, int R) {
	int count = 0;
	while (L <= R)
		count += 665772 >> __builtin_popcount(L++) & 1;
	return count;
}

int main(void) {
	return 0;
}