#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;


string alphabetBoardPath(string target) {

	//idea:
	//coords dont change. So have a mapping of letters to coords.
	//for each letter, do moves to get to it.  Then add a bang.
	std::pair<int, int> currentPos = { 0,0 };
	std::unordered_map<char, std::pair<int, int>> letter2Coords;
	letter2Coords.insert({ 'a', {0,0} });
	letter2Coords.insert({ 'b', {0,1} });
	letter2Coords.insert({ 'c', {0,2} });
	letter2Coords.insert({ 'd', {0,3} });
	letter2Coords.insert({ 'e', {0,4} });
	letter2Coords.insert({ 'f', {1,0} });
	letter2Coords.insert({ 'g', {1,1} });
	letter2Coords.insert({ 'h', {1,2} });
	letter2Coords.insert({ 'i', {1,3} });
	letter2Coords.insert({ 'j', {1,4} });
	letter2Coords.insert({ 'k', {2,0} });
	letter2Coords.insert({ 'l', {2,1} });
	letter2Coords.insert({ 'm', {2,2} });
	letter2Coords.insert({ 'n', {2,3} });
	letter2Coords.insert({ 'o', {2,4} });
	letter2Coords.insert({ 'p', {3,0} });
	letter2Coords.insert({ 'q', {3,1} });
	letter2Coords.insert({ 'r', {3,2} });
	letter2Coords.insert({ 's', {3,3} });
	letter2Coords.insert({ 't', {3,4} });
	letter2Coords.insert({ 'u', {4,0} });
	letter2Coords.insert({ 'v', {4,1} });
	letter2Coords.insert({ 'w', {4,2} });
	letter2Coords.insert({ 'x', {4,3} });
	letter2Coords.insert({ 'y', {4,4} });
	letter2Coords.insert({ 'z', {5,0} });

	std::string result;
	for (const auto& c : target) {

		auto coords = letter2Coords[c];

		while (currentPos != coords) {

			//4 dirs
			if (currentPos.first > coords.first) {
				result += "U";
				currentPos.first--;
			}

			if (currentPos == coords)
				break;

			if (currentPos.first < coords.first && !(currentPos.first == 4 && currentPos.second > 0)) {
				result += "D";
				currentPos.first++;
			}

			if (currentPos == coords)
				break;

			if (currentPos.second > coords.second) {
				result += "L";
				currentPos.second--;
			}

			if (currentPos == coords)
				break;

			if (currentPos.second > coords.second && !(currentPos.first == 5)) {
				result += "R";
				currentPos.second++;
			}

		}

		result += "!";
	}

	return result;
}

int largest1BorderedSquare(std::vector<std::vector<int>>& grid) {
	int width = grid.size();
	int height = grid[0].size();

	if (width == 1 && height == 1) {
		return grid[0][0];
	}

	std::vector<std::vector<int>> X(width, std::vector<int>(height, 0));
	std::vector<std::vector<int>> Y(width, std::vector<int>(height, 0));

	int maxLength = 0;

	//initialize

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (grid[i][j] == 1) {
				if (i == 0) {
					Y[i][j] = 1;
				}
				else {
					Y[i][j] = Y[i - 1][j] + 1;
				}

				if (j == 0) {
					X[i][j] = 1;
				}
				else {
					X[i][j] = X[i][j - 1] + 1;
				}
			}
		}
	}


	for (int i = width - 1; i >= 0; --i) {

		for (int j = height - 1; j >= 0; --j) {

			int currentLength = std::min(X[i][j], Y[i][j]);

			while (currentLength > 0) {

				bool doWeHaveASquare = X[i - currentLength + 1][j] >= currentLength &&
					Y[i][j - currentLength + 1] >= currentLength;

				if (doWeHaveASquare) {
					maxLength = std::max(maxLength, currentLength);
				}

				currentLength--;
			}


		}


	}

	return maxLength * maxLength;

}

int main(void) {

//	alphabetBoardPath("leet");

	std::vector<std::vector<int>> t{ {1,1,0,0} };
	largest1BorderedSquare(t);

	/*
	std::vector<int> t = {
		2,21,43,38,0,42,33,7,24,13,12,27,12,24,5,23,29,48,30,31
	};
	
	std::vector<int> tt = {
		2,42,38,0,43,21
	};

	relativeSortArray(t, tt);
	*/


	return 0;
}