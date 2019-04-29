/*
 * Matrix Cells in Distance Order,
 * Find Customer Referee
 * Nested List Weight Sum
 */


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <multimap>

/*
 SELECT name FROM customers WHERE REF_ID <> 2
 
 */

class NestedInteger {
public:
	int value;
	std::vector<NestedInteger> list;
	NestedInteger() {}
	bool isInteger(){ return list.empty(); }
	std::vector<NestedInteger> getList() {
		return list;
	};
};

// idea: use recursion.  If it is an int, add and multiply.
// if it isn't, recurse, and increment depth by 1.

int helper(std::vector<NestedInteger> in, int depth) {
	
	if (in.empty()) {
		return 0;
	}

	int sum = 0;
	for (auto& nestedInt : in) {
		if (nestedInt.isInteger()) {
			sum += depth * nestedInt.value;
		} else {
			sum += helper(nestedInt.getList(), depth + 1);
		}
	}


	return sum;
}

int NestedListWeightSum(std::vector<NestedInteger>& in) {
	return helper(in, 1);
}

std::vector<std::vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {

	std::vector<std::vector<int>> res = { { r0, c0 } };
	// c17
	auto max_d = std::max({ r0 + c0, c0 + R - r0, r0 + C - c0, R - r0 + C - c0 });
	for (auto d = 1; d <= max_d; ++d) {
		for (int x = -d; x <= d; ++x) {
			// get the row, and the column on each side (+ and -)
			auto r1 = r0 + x, c1_a = c0 + d - abs(x), c1_b = c0 + abs(x) - d;
			// if its a valid row
			if (r1 >= 0 && r1 < R) {
				// if its a valid column, and they aren't identical
				if (c1_a >= 0 && c1_a < C) res.push_back({ r1, c1_a });
				if (c1_a != c1_b && c1_b >= 0 && c1_b < C) res.push_back({ r1, c1_b });
			}
		}
	}
	return res;

}


int main(void)
{
	return 0;
}