#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <stack>
#include <deque>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
// idea: since its 3 parts, use / 3, % 3
bool canThreePartsEqualSum(std::vector<int>& A) {
	int totalSum = std::accumulate(A.begin(), A.end(), 0);
	if (totalSum % 3 != 0) {
		return false;
	}

	int currentSum = 0;
	int sections = 0;
	for (int i = 0; i < A.size(); ++i) {

		currentSum += A[i];
		if (totalSum / 3 == currentSum) {
			++sections;
			currentSum = 0;
		}
	}

	return sections >= 3;
}

// idea: use stack
std::string removeDuplicates(std::string S) {

	std::stack<char> letterStack;

	letterStack.push(S[0]);
	for (int i = 1; i < S.size(); ++i) {
		char c = S[i];
		if (!letterStack.empty() && c == letterStack.top()) {
			letterStack.pop();
		}
		else {
			letterStack.push(c);
		}
	}

	std::string result;

	// optimization: can just use the result string as a stack
	while (!letterStack.empty()) {
		char c = letterStack.top();
		letterStack.pop();
		result.push_back(c);
	}

	std::reverse(result.begin(), result.end());
	return result;
}

// idea: dfs
// trick to toggle case: s[i] ^= (1 << 5);
void helper(std::vector<std::string>& results, std::string& S,
	int index) {
	if (index == S.size()) {
		results.push_back(S);
		return;
	}

	//first, backtrack for all cases
	helper(results, S, index + 1);

	//if its a letter, start a new branch
	if (isalpha(S[index])) {
		S[index] ^= (1 << 5);
		helper(results, S, index + 1);
	}


}

void helper(std::unordered_set<int>& visited,
	std::vector<std::vector<int>>& rooms,
	int currentRoom) {

	if (visited.count(currentRoom) == 1) {
		return;
	}

	visited.insert(currentRoom);

	for (int i = 0; i < rooms[currentRoom].size(); ++i) {
		helper(visited, rooms, rooms[currentRoom][i]);
	}

}

bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {

	int totalNumberOfRooms = rooms.size();

	std::unordered_set<int> visited;

	helper(visited, rooms, 0);

	int visitedCount = visited.size();

	return visitedCount == totalNumberOfRooms;
}

std::vector<std::string> letterCasePermutation(std::string S) {
	std::vector<std::string> results;

	helper(results, S, 0);

	return results;
}

double largestTriangleArea(std::vector<std::vector<int>>& points) {
	double result = 0;

	for (int i = 0; i < points.size() - 2; ++i) {
		for (int j = i + 1; j < points.size() - 1; ++j) {
			for (int k = j + 1; k < points.size(); ++k) {

				double currArea = std::abs(points[i][0] * (points[j][1] - points[k][1]) +
					points[j][0] * (points[k][1] - points[i][1]) +
					points[k][0] * (points[i][1] - points[j][1]));
				result = std::max(result, currArea);
			}
		}
	}

	return result / 2;
}

int main(void) {

	return 0;
}