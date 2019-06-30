#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> pathInZigZagTree(int label) {

	int level = 1;
	std::vector<int> result;
	while (level <= label)
		level *= 2;

	while (true) {
		result.push_back(label);

		if (label == 1)
			break;

		label = (level + level / 2 - label - 1) / 2;
		level /= 2;
	}

	std::reverse(begin(result), end(result));

	return result;
}

int minHeightShelves(std::vector<std::vector<int>>& books, int shelf_width) {

	std::vector<int> dp(books.size() + 1, INT_MAX);
	dp[0] = 0;

	for (int i = 1; i <= books.size(); ++i) {
		auto p = books[i - 1];
		int width = p[0];
		int height = p[1];
		dp[i] = dp[i - 1] + height;

		for (int j = i - 1; j > 0; --j) {
			width += books[j - 1][0];
			height = std::max(height, books[j - 1][1]);

			if (width > shelf_width)
				break;

			dp[i] = std::min(dp[i], dp[j - 1] + height);
		}
	}

	return dp[books.size()];
}

int main(void) {
	
	auto z = pathInZigZagTree(1);
	auto zz = pathInZigZagTree(16);
	auto zzz = pathInZigZagTree(15);
	

	std::vector<std::vector<int>> t{ {1,1}, {2,3}, {2,3}, {1,1}, {1,1}, {1,1}, {1,2} };
	auto zzzz = minHeightShelves(t, 4);


	return 0;
}