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

std::vector<int> partitionLabels(std::string S) {

	std::unordered_map<char, int> letterToLastIndex;

	for (int i = 0; i < S.length(); ++i) {
		letterToLastIndex[S[i]] = i;
	}

	std::vector<int> result;
	int length = 0;
	int maxIndexOfLastLetter = INT_MIN;
	for (int i = 0; i < S.length(); ++i) {

		maxIndexOfLastLetter = std::max(
			maxIndexOfLastLetter, letterToLastIndex[S[i]]);

		if (maxIndexOfLastLetter == i) {
			result.push_back(i - length + 1);
			length = i + 1;
		}
	}

	return result;
}

int main(void) {

	int t = 5;
	int tt = 69;
	int ttt = std::exchange(t, tt);
	int tttt = std::exchange(tt, t);

	return 0;
}