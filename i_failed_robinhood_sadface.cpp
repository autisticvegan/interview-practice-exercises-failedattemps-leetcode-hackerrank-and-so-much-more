class Solution {
public:
	int equalSubstring(string s, string t, int maxCost) {
		int i = 0;
		int j = 0;
		for (j = 0; j < s.size(); ++j) {
			if ((maxCost -= std::abs(s[j] - t[j])) < 0) {
				maxCost += std::abs(s[i] - t[i++]);
			}
		}

		return j - i;
	}
};

bool validCell(std::vector<std::vector<int>>& g, int x, int y) {
	return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size() || g[x][y] <= 0);
}

std::vector<int> xDirs{ 1,-1,0,0 };
std::vector<int> yDirs{ 0,0,-1,1 };

int explore(std::vector<std::vector<int>>& g, int x, int y) {

	if (!validCell(g, x, y))
		return 0;

	int max = INT_MIN;

	g[x][y] = -g[x][y];

	for (int i = 0; i < xDirs.size(); ++i) {
		int newX = xDirs[i] + x;
		int newY = yDirs[i] + y;

		max = std::max(explore(g, newX, newY), max);

	}

	g[x][y] = -g[x][y];

	return max + g[x][y];
}

int getMaximumGold(vector<vector<int>>& grid) {

	int max = 0;
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {

			max = std::max(max, explore(grid, i, j));

		}
	}
return max;
}
}

int longestSubsequence(vector<int>& arr, int difference) {

	//go backwards, adding 1 to the map of arr[i] + difference
	// if we see it in the future, we will increment
	std::unordered_map<int, int> m;
	int max = INT_MIN;
	for (int i = arr.size() - 1; i >= 0; --i) {

		m[arr[i]] = 1 + m[arr[i] + difference];
		max = std::max(max, m[arr[i]]);
	}

	return max;

}


