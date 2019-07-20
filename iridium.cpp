#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <istream>
#include <sstream>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

std::vector<TreeNode*> helper(int start, int end) {

	std::vector<TreeNode*> res;

	if (start > end) {
		res.push_back(nullptr);
		return res;
	}

	for (int i = start; i <= end; ++i) {

		std::vector<TreeNode*> leftNodes = helper(start, i - 1);
		std::vector<TreeNode*> rightNodes = helper(i + 1, end);

		for (int j = 0; j < leftNodes.size(); ++j) {
			for (int k = 0; k < rightNodes.size(); ++k) {

				TreeNode* t = new TreeNode(i);
				t->left = leftNodes[j];
				t->right = rightNodes[k];
				res.push_back(t);

			}
		}

	}



	return res;
}


std::vector<TreeNode*> generateTrees(int n) {

	//idea: have helper function with start, end
	// kickstart from 1,n
	// for each func call: go from outer to inner
	// as in, i -> end.  i+1, i-1
	// left is start, i-1
	// right is i+1, end
	// once we have calculated the 2 vectors for left right
	// loop through them and push back root on each iteration
	// root new node, i -> left, j -> right, push_back(root)
	// then return

	if (n < 1) {
		return std::vector<TreeNode*>();
	}

	return helper(1, n);

}

// catalan number
int numTrees(int n) {
	long long ans = 1, i;
	for (i = 1; i <= n; i++)
		ans = ans * (i + n) / i;
	return ans / i;
}

//google problem
// given a matrix of letters
// such as
// A Z B
// C K O
// X W Y
// find the longest path
// start from any letter
// only go forward in alphabet
std::vector<int> dirX{ 0,1,-1,0 };
std::vector<int> dirY{ 1, 0, 0, -1 };

int helper(int startX, int startY, std::vector<std::vector<char>>& matrix, std::vector<std::vector<int>>& table) {

	if (!isValidCell(startX, startY, matrix)) {
		return 0;
	}

	if (table[startX][startY] != 0) {
		return table[startX][startY];
	}

	for (int i = 0; i < 4; ++i) {
		int newX = dirX[i] + startX;
		int newY = dirY[i] + startY;
		
		if (isValidCell(newX, newY, matrix)) {
			if (matrix[newX][newY] > matrix[startX][startY]) {
				table[startX][startY] = std::max(table[startX][startY], 1 + helper(newX, newY, matrix, table));
			}
		}
	}

	return table[startX][startY] = std::max(1, table[startX][startY]);

}

bool isValidCell(int x, int y, std::vector<std::vector<char>>& m) {
	if (x < 0 || y < 0 || x >= m.size() || y >= m[0].size())
		return false;

	return true;
}



int longestPath(std::vector<std::vector<char>>& matrix) {
	int result = 0;
	int size = matrix.size();

	std::vector<std::vector<int>> table(size, std::vector<int>(size));

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (table[i][j] == 0) {
				helper(i, j, matrix, table);
			}

			result = std::max(table[i][j], result);
		}
	}



	return result;
}


int numDecodings(std::string s) {
	//idea: 1st digit is always 1
	// then other spots could be either 1 or 2 digits
	// if we are in 2 digit branch, it must be less than 26
	// if we are in 1 digit branch the digit cant be 0
	// note 2 digit looks back
	// use DP which is size 2 bigger than s
	// because we update 2 forward, with either the current one
	// or the current + 1 index.  also remember to init
	// spot [1] to 1. (spot 0 is 0)

	std::vector<int> dp(s.size() + 2, 0);
	dp[1] = 1;
	for (int i = 0; i < s.size(); ++i) {

		// 1 digit branch
		if (s[i] != '0') {
			dp[i + 2] += dp[i + 1];
		}

		// 2 digit branch
		if (i != 0) {

			int num = (s[i - 1] - '0') * 10 + (s[i] - '0');

			if (num >= 10 && num < 27) {
				dp[i + 2] += dp[i];
			}

		}



	}

	return dp.back();
}

int lastStoneWeight(std::vector<int>& stones) {
	std::priority_queue<int> pq;

	for (const auto& s : stones) {
		pq.push(s);
	}

	while (!pq.empty() && pq.size() > 1) {
		int n1 = pq.top();
		pq.pop();
		int n2 = pq.top();
		pq.pop();

		if (n1 != n2) {
			pq.push(n1 - n2);
		}
	}

	if (pq.empty()) {
		return 0;
	}

	return pq.top();
}

int lastStoneWeightII(std::vector<int>& stones) {
	// either + or -
	// sum of one side vs other
	// get min
	// use set to see if you've sen
	// each loop, swap set and reuse it
	// get min of all
	std::unordered_set<int> seen{ 0 };
	for (int i = 0; i < stones.size(); ++i) {

		std::unordered_set<int> temp = seen;
		seen.clear();
		for (const auto& num : temp) {
			int pos = std::abs(num + stones[i]);
			int neg = std::abs(num - stones[i]);
			seen.insert(pos);
			seen.insert(neg);
		}
	}

	int min = INT_MAX;

	for (const auto& n : seen) {
		min = std::min(n, min);
	}

	return min;
}




