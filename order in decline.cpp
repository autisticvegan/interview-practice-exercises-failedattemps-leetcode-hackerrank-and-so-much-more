
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

bool isOdd(int i) {
	return i % 2 != 0;
}

int movesToMakeZigzag(vector<int>& nums) {
	//final step: take min of either left or right of result
	//iterate through array, and for each one, check left and right side
	//get min of left and right, then take A[i] - min + 1.
	//if that val is negative, dont add anything, that means we are already in sync
	//important: use modulus to add for appropriate index 
	// (i.e. 0 -> 0, 1 -> 1, 2 -> 0, 3 -> 1, etc) 
	std::pair<int, int> result;

	for (int i = 0; i < nums.size(); ++i) {

		int left = INT_MAX;
		if (i != 0) {
			left = nums[i - 1];
		}

		int right = INT_MAX;
		if (i != nums.size() - 1) {
			right = nums[i + 1];
		}

		int val = nums[i] - std::min(left, right) + 1;

		if (val <= 0) {
			continue;
		}

		if (isOdd(i)) {
			result.second += val;
		}
		else {
			result.first += val;
		}

	}


	return std::min(result.first, result.second);
}



// idea recursive:
// base case: string is length 0, return 0.  if its not, return 1;
// early return: 2 + func


int longestDecomposition(string text) {

	int size = text.size();

	for (int i = 0; i < size / 2; ++i) {

		std::string s1 = text.substr(0, i + 1);
		std::string s2 = text.substr(size - 1 - i);
		// abciabc
		// ab
		// aa
		if (s1 == s2) {
			return 2 + longestDecomposition(text.substr(i + 1, size - s1.size() - s2.size()));
		}

	}


	if (size == 0) {
		return 0;
	}
	else {
		return 1;
	}

}



TreeNode* findNode(TreeNode* r, int v) {

	if (!r)
		return r;

	TreeNode* temp = r;

	if (r && r->val == v) {
		return r;
	}

	temp = findNode(r->left, v);
	if (!temp)
		temp = findNode(r->right, v);

	return temp;
}

int count(TreeNode* ro) {

	if (!ro)
		return 0;

	int l = 0;
	int r = 0;

	if (ro->left)
		l = count(ro->left);

	if (ro->right)
		r = count(ro->right);

	return 1 + l + r;
}

bool btreeGameWinningMove(TreeNode* root, int n, int x) {

	//assumption, its in the tree

	//3 vals - left, right, and n - left - right
	auto temp = findNode(root, x);
	int most = 0;
	int left = 0;
	int right = 0;
	if (temp) {
		left = count(temp->left);
		right = count(temp->right);
		most = std::max(left, right);
	}

	if (root->val != x) {
		most = std::max(n - left - right - 1, most);
	}

	return most > n - most;

}



class SnapshotArray {
public:

	unordered_map<int, map<int, int>> a;
	int cur_snap = 0;

	SnapshotArray(int length) {

	}

	void set(int index, int val) {
		a[index][cur_snap] = val;
	}

	int snap() {
		return cur_snap++;
	}

	int get(int index, int snap_id) {

		auto it = a[index].upper_bound(snap_id);
		return it == begin(a[index]) ? 0 : prev(it)->second;
	}
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

int main(void) {
	SnapshotArray s(1);

	s.set(0, 15);
	s.snap();
	s.snap();
	s.snap();
	s.get(0, 2);
	s.snap();
	s.snap();
	s.get(0, 0);
}