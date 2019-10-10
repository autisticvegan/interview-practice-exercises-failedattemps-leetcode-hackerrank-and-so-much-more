#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// a company that starts with a p and ends with a t
bool validCell(int x, int y, char nextChar,
	const std::vector<std::vector<std::string>>& g) {
	return !(x < 0 || y < 0 || x >= g.size()
		|| y >= g[0].size() || nextChar != g[x][y][0]);
}

//recurse
// Think about optimizing with lookup table to not go down same paths
bool Recurse(int x, int y, const std::vector<std::vector<string>>& grid,
	const std::string& target, int index, std::vector<std::pair<int, int>>& path) {

	if (index == target.size()) {
		return true;
	}

	if (!validCell(x, y, target[index], grid)) {
		//path.clear();
		return false;

	}
	path.push_back({ x,y });
	//go right
	bool res = false;
	res = Recurse(x + 1, y, grid, target, index + 1, path);

	if (res) {
		return true;
	}

	//go down
	res = Recurse(x, y + 1, grid, target, index + 1, path);

	path.pop_back();
	return res;
}

void findWord(const string word, const vector<vector<string>>& grid) {
	// Your code here. Prints to standard output.

	if (word.empty() || grid.empty()) {
		cout << "None" << endl;
		return;
	}

	char c = word[0];
	std::vector<std::pair<int, int>> path;
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j][0] == c) {
				//launch Recurse func
				bool res = Recurse(i, j, grid, word, 0, path);
				if (res) {

					for (const auto& p : path) {
						std::cout << p.first << " " << p.second << std::endl;
					}
					return;
				}
			}
		}
	}

	cout << "None" << endl;
};

int main() {
	string line;
	bool firstArg = true;
	vector<vector<string>> grid;
	string word;

	while (getline(cin, line)) {
		if (line == "") continue;
		if (line == "test") break;
		istringstream iss(line);
		if (firstArg) {
			firstArg = false;
			word = line;
		}
		else {
			vector<string> parts(istream_iterator<string>{iss}, istream_iterator<string>());
			grid.push_back(parts);
		}
	}

	findWord(word, grid);
}
