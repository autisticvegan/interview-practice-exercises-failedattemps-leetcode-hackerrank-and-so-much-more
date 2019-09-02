#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

//idea: use unordered map of ints to stacks (or could use vector)
//then use set to keep track of full stacks.  we want the smallest stack that is not full

std::map<int, std::stack<int>> index2Stacks;
std::set<int> setOfAvailableStacks;
int cap = 0;
DinnerPlates(int capacity) {
	cap = capacity;
}

void push(int val) {
	if (setOfAvailableStacks.empty()) {
		setOfAvailableStacks.insert(index2Stacks.size());
	}
	auto b = setOfAvailableStacks.begin();
	index2Stacks[*b].push(val);
	if (index2Stacks[*b].size() == cap) {
		setOfAvailableStacks.erase(*b);
	}
}

int pop() {

	if (index2Stacks.empty())
		return -1;

	return popAtStack(index2Stacks.rbegin()->first);

}

int popAtStack(int index) {
	if (index2Stacks.count(index) && !index2Stacks[index].empty()) {
		int r = index2Stacks[index].top();
		index2Stacks[index].pop();
		setOfAvailableStacks.insert(index);

		if (index2Stacks[index].empty())
			index2Stacks.erase(index);

		return r;
	}
	return -1;
}

//prefix sum problem
//  use xor (mask ^= 1 << (c - 'a')) to calculate the mask for each character
// dont forget to push_back an empty one for the first prefix
// once we have th emask, go through each query:
// count thenumber of set bits: use builtin_popcount or std::bitset<26>.count
// high+1 ^ low <-- THIS IS VERY IMPORTANT
// if q[2] * 2 >= oddCount - (q[1] - q[0] + 1) % 2);
// if our change number * 2 is greater than or equal to oddCount - distance % 2
std::vector<bool> canMakePaliQueries(std::string s, std::vector<std::vector<int>>& queries) {

	int mask = 0;
	std::vector<int> prefixMasks;
	prefixMasks.push_back(mask);

	for (int i = 0; i < s.size(); ++i) {
		mask ^= 1 << (s[i] - 'a');
		prefixMasks.push_back(mask);
	}
	std::vector<bool> res;
	for (auto& q : queries) {
		int oddCount = std::bitset<26>(prefixMasks[q[1] + 1] ^ prefixMasks[q[0]]).count();

		int maxVal = q[2] * 2;
		int distance = q[1] - q[0] + 1;
		bool r = (maxVal >= oddCount - distance % 2);
		res.push_back(r);
	}
	return res;
}

int getMask(string & s) {
	int mask = 0;
	for (auto c : s)
		mask |= (1 << (c - 'a'));
	return mask;
}
public:
	vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
		unordered_map<int, int> freq;
		for (auto & w : words) {
			int mask = getMask(w);
			freq[mask] ++;
		}
		vector<int> res;
		for (auto & p : puzzles) {
			int mask = getMask(p);
			int cnt = 0;
			int maskFirstChar = 1 << (p[0] - 'a');
			for (int i = mask; i > 0; i = ((i - 1) & mask)) {
				if ((i & maskFirstChar) > 0 && freq.count(i)) {
					cnt += freq[i];
				}
			}
			res.push_back(cnt);
		}
		return res;
	}


	bool isValid(int x, int y, int R, int C) {
		if (x < 0 || x >= R || y < 0 || y >= C) {
			return false;
		}
		return true;
	}

	vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
		int t = 0;
		int end = R * C;
		std::vector<std::vector<int>> res(end, std::vector<int>(2));
		int dir = 0;
		int x = r0;
		int y = c0;
		int changeDir = 0;
		int count = 1;
		while (t != end) {

			for (int i = 0; i < count; ++i) {

				if (isValid(x, y, R, C)) {
					res[t] = { x,y };
					++t;
				}

				if (dir == 0) {
					y++;
				}
				else if (dir == 1) {
					x++;
				}
				else if (dir == 2) {
					y--;
				}
				else if (dir == 3) {
					x--;
				}



			}

			++changeDir;
			if (changeDir == 2) {
				changeDir = 0;
				++count;
			}
			dir = (dir + 1) % 4;

		}

		return res;
	}

int main(void) {
	auto t = spiralMatrixIII(1, 4, 0, 0);
	return 0;
}