std::vector<int> powerfulIntegers(int x, int y, int bound) {

	int iUpperLimit = (x == 1) ? 1 : ((int)((double)std::log(bound) / (double)std::log(x)));
	int jUpperLimit = (y == 1) ? 1 : ((int)((double)std::log(bound) / (double)std::log(y)));

	std::unordered_map<int, int> expo2resX;
	std::unordered_map<int, int> expo2resY;

	for (int i = 0; i <= iUpperLimit; ++i) {
		expo2resX[i] = std::pow(x, i);
	}

	for (int j = 0; j <= jUpperLimit; ++j) {
		expo2resY[j] = std::pow(y, j);
	}

	std::unordered_set<int> r;
	for (int i = 0; i <= iUpperLimit; ++i) {
		for (int j = 0; j <= jUpperLimit; ++j) {

			int res = expo2resY[j] + expo2resX[i];

			if (res <= bound) {
				r.insert(res);
			}
			else {
				break;
			}
		}
	}

	return { r.begin(), r.end() };
}


int kthSmallest(TreeNode* root, int k) {

	//go all left, then pop and go right then all left, etc
	TreeNode* node = root;
	std::stack<TreeNode*> s;
	while (node) {
		s.push(node);
		node = node->left;
	}
	int val = 69;
	while (k > 0) {

		TreeNode* t = s.top();
		s.pop();
		val = t->val;

		t = t->right;

		while (t) {
			s.push(t);
			t = t->left;
		}

		k--;
	}

	return val;

}


struct RadixNode {
	RadixNode() {
		fill(next.begin(), next.end(), nullptr);
	}
	array<RadixNode*, 2> next;
	int count = 0;
};

struct RadixTree {
	RadixTree() {
		mem.emplace_back();
		root = &mem.back();
	}

	void insert(int num) {
		uint32_t u = (uint32_t)num;
		u ^= (1u << 31);
		uint32_t mask = 1u << 31;
		RadixNode* cur = root;
		for (int i = 0; i < 32; ++i) {
			bool bit = ((u & mask) != 0);
			mask >>= 1;
			RadixNode*& next = cur->next[bit];
			if (!next) {
				mem.emplace_back();
				next = &mem.back();
			}
			next->count += 1;
			cur = next;
		}
	}

	int count_less_than(int num) {
		uint32_t u = (uint32_t)num;
		u ^= (1u << 31);
		uint32_t mask = 1u << 31;
		RadixNode* cur = root;
		int count = 0;
		for (int i = 0; i < 32; ++i) {
			bool bit = ((u & mask) != 0);
			mask >>= 1;
			if (bit == 1 && cur->next[0] != nullptr) {
				count += cur->next[0]->count;
			}
			cur = cur->next[bit];
			if (cur == nullptr) break;
		}
		return count;
	}

	RadixNode* root;
	deque<RadixNode> mem;
};


class Solution {
public:
	int reversePairs(vector<int>& nums) {

		RadixTree radixt;
		int64_t count = 0;
		for (ptrdiff_t i = nums.size() - 1; i >= 0; --i) {
			int upper_bound = nums[i] / 2;
			if (nums[i] % 2 > 0) upper_bound += 1;
			count += radixt.count_less_than(upper_bound);
			radixt.insert(nums[i]);
		}
		return int(count);
	}
};