#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;

std::string defangIPaddr(std::string address) {
	size_t pos = address.find(".");
	std::vector<size_t> positions;
	while (pos != std::string::npos) {
		positions.push_back(pos);
		pos = address.find(".", pos + 1);
	}

	int add = 0;
	for (const auto& p : positions) {
		auto pos1 = p + add;
		auto pos2 = p + 2 + add;
		address.insert(pos1, "[");
		address.insert(pos2, "]");
		add += 2;
	}

	return address;
}
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {

	std::map<int, int> arr1Val2Count;

	for (const auto& i : arr1) {
		arr1Val2Count[i]++;
	}

	std::vector<int> res;

	// go through 2nd array, for each one, insert to result count, and erase from map
	// then insert remaining
	for (auto& p : arr2) {
		if (arr1Val2Count.count(p)) {
			int count = arr1Val2Count[p];
			for (int i = 0; i < count; ++i) {
				res.push_back(p);
			}
			arr1Val2Count.erase(p);
		}
	}

	for (const auto& i : arr1Val2Count) {
		for (int k = 0; k < i.second; ++k)
			res.push_back(i.first);
	}


	return res;
}
/*
int longestUnivaluePath(TreeNode* root) {

	if (!root)
		return 0;

	int r = 0;
	//base case: root is equal to both, get max of l and r
	helper(root, r);
	return r;
}

int helper(TreeNode* root, int& runningTotal) {

	int leftSum = 0;
	if (root->left) {
		leftSum = helper(root->left, runningTotal);
	}

	int rightSum = 0;
	if (root->right) {
		rightSum = helper(root->right, runningTotal);
	}

	//add 1 if root is same

	if (root->left && root->left->val == root->val) {
		leftSum++;
	}
	else {
		leftSum = 0;
	}

	if (root->right && root->right->val == root->val) {
		rightSum++;
	}
	else {
		rightSum = 0;
	}


	runningTotal = std::max(runningTotal, leftSum + rightSum);
	return std::max(leftSum, rightSum);
}

string gcdOfStrings(string str1, string str2) {

	//first find gcd of strings (number) by using gcd func on sizes
	// then once we know taht, get the T substr by doing
	// str1.substr(0, gcd);
	// then check 2 conditions (1 for each str) (stepping along p size):
	// if p < sz1 && str1.compare(p, T.size(), T) == 0 , then return ""
	// so if the substr doesnt match for either then we break

	int gcd = __gcd(str1.size(), str2.size());
	std::string T = str1.substr(0, gcd);
	// we dont know which one is longer
	int longest = std::max(str1.size(), str2.size());

	for (int p = 0; p <= longest; p += T.size()) {

		if ((p < str1.size() && str1.compare(p, T.size(), T) != 0)
			|| (p < str2.size() && str2.compare(p, T.size(), T) != 0))
			return "";

	}

	return T;
}
*/

bool isMagicSquare(std::vector<std::vector<int>>& g, int x, int y) {

	if (x + 2 >= g.size() || y + 2 >= g[0].size())
		return false;

	std::unordered_set<int> s;
	//check for 1 - 9
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (g[x + i][y + j] < 1 || g[x + i][y + j] > 9)
				return false;

			s.insert(g[x + i][y + j]);
		}
	}
	if (s.size() != 9)
		return false;

	int sum = 0;
	for (int i = 0; i < 3; ++i) {
		sum += g[x + i][y];
	}

	int sum2 = 0;

	for (int i = 0; i < 3; ++i) {
		sum2 += g[x][y + i];
	}

	if (sum != sum2)
		return false;

	int sum3 = 0;
	for (int i = 0; i < 3; ++i) {
		sum3 += g[x + i][y + i];
	}

	return sum3 == sum && sum3 == sum2;
}

int numMagicSquaresInside(vector<vector<int>>& grid) {

	if (grid.size() < 3 || grid[0].size() < 3)
		return 0;

	int sum = 0;
	for (int i = 0; i <= grid.size() - 3; ++i) {
		for (int j = 0; j <= grid[0].size() - 3; ++j) {
			if (isMagicSquare(grid, i, j)) {
				sum++;
			}
		}
	}
	return sum;
}

int main(void) {

	/*
	std::vector<int> t = {
		2,21,43,38,0,42,33,7,24,13,12,27,12,24,5,23,29,48,30,31
	};

	std::vector<int> tt = {
		2,42,38,0,43,21
	};

	relativeSortArray(t, tt);
	*/

	std::vector<std::vector<int>> t = { {4, 3, 8, 4},{9, 5, 1, 9},{2, 7, 6, 2} };
	numMagicSquaresInside(t);
	return 0;
}