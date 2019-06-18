class Solution {
public:
	// idea: use LCS, then combine from 3 parts - the lcs, and part of a and part of b
	// as we go through each character in the lcs, have 2 indices as well, one for a and one for b

		// dont just save the length, save the string along with it
	std::string MyLCS(std::string& A, std::string& B) {
		int sizeA = A.size();
		int sizeB = B.size();

		std::vector<std::vector<std::string>> dp(sizeA + 1, std::vector<std::string>(sizeB + 1, ""));

		for (int i = 0; i < sizeA; ++i) {
			for (int j = 0; j < sizeB; ++j) {
				if (A[i] == B[j]) {
					dp[i + 1][j + 1] = dp[i][j] + A[i];
				}
				else { // take from either above or back (max).
					dp[i + 1][j + 1] = dp[i + 1][j].size() > dp[i][j + 1].size() ? dp[i + 1][j] : dp[i][j + 1];
				}
			}
		}

		return dp[sizeA][sizeB];
	}


	std::string shortestCommonSupersequence(std::string str1, std::string str2) {

		std::string result = "";

		int i = 0;
		int j = 0;
		std::string LCS = MyLCS(str1, str2);
		for (int k = 0; k < LCS.size(); ++k) {

			while (str1[i] != LCS[k]) {
				result += str1[i++];
			}
			while (str2[j] != LCS[k]) {
				result += str2[j++];
			}

			result += LCS[k];
			++i;
			++j;
		}

		return result + str1.substr(i) + str2.substr(j);

	}
};

class Solution {
public:
	void duplicateZeros(std::vector<int>& arr) {

		int totalSize = arr.size();
		for (int i = 0; i < totalSize; ++i) {
			if (arr[i] == 0) {
				arr.insert(arr.begin() + i, 0);
				++i;
			}
		}

		arr.resize(totalSize);

	}
};


bool validCell(std::vector<std::vector<int>>& g, std::pair<int, int>& c) {
	return (c.first >= 0 && c.second >= 0 && c.first < g.size() && c.second < g.size() && !g[c.first][c.second]);
}

int shortestPathBinaryMatrix(std::vector<std::vector<int>>& g, int steps = 0) {
	std::queue<std::pair<int, int>> q;
	q.push({ 0, 0 });
	int goalX = g.size() - 1;
	int goalY = g.size() - 1;

	while (!q.empty()) {
		++steps;
		std::queue<std::pair<int, int>> q1;
		while (!q.empty()) {
			auto c = q.front();
			q.pop();

			if (validCell(g, c)) {
				g[c.first][c.second] = 1;

				if (c.first == goalX && c.second == goalY)
					return steps;

				for (auto i = -1; i < 2; ++i)
					for (auto j = -1; j < 2; ++j)
						if (i != 0 || j != 0) q1.push({ c.first + i, c.second + j });
			}
		}
		std::swap(q, q1);
	}
	return -1;
}