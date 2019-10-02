bool validCell(std::vector<std::vector<int>>& g, int x, int y) {
	return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size());
}

std::vector<int> xDir{ 0,0,-1,1 };
std::vector<int> yDir{ 1,-1,0,0 };

//inside rot function set it to + d + 3
// if d is 0, then orange becomes 3.  Then we will know
// which rotted yesterday so we dont have to waste iterations
// could also use a visited array but that wastes space
int rot(std::vector<std::vector<int>>& g, int x, int y, int d) {
	if (!validCell(g, x, y) || g[x][y] != 1)
		return 0;

	g[x][y] = d + 3;
	return 1;
}

int orangesRotting(vector<vector<int>>& grid) {

	int freshCount = 0;

	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {
			if (grid[i][j] == 1)
				++freshCount;
		}
	}

	int result = 0;
	while (freshCount > 0) {

		int oldFresh = freshCount;

		for (int i = 0; i < grid.size(); ++i) {
			for (int j = 0; j < grid[0].size(); ++j) {

				if (!validCell(grid, i, j)) {
					continue;
				}

				// + 2 only because we care about yesterday
				// i.e. days is 0, then 2 is rotten oranges
				// days is 1, then 3 is rotten oranges
				// days is 2, then 4 is rotten oranges
				if (grid[i][j] == result + 2) {

					for (int k = 0; k < 4; ++k) {

						int newx = i + xDir[k];
						int newy = j + yDir[k];
						freshCount -= rot(grid, newx, newy, result);
					}
				}
			}
		}

		if (oldFresh == freshCount) //none rotted
			return -1;

		++result;
	}

	return result;

	//if we did not rot any, then return -1

}


int minimumMoves(vector<vector<int>>& grid) {

	//idea: since we need 2 spots, use
	//2 pairs - x,y  and x,y (head and tail)
	// use a q with bfs, along with distance
	// x,y,x,y , dist 
	//inside q loop:
	//if we hit exit, return the dist
	// 2 cases: horiz and vert
	// in each case, calculate the next 3 moves and 
	// see if valid
	// once we have our moves, if they are not visited
	// visit them, and add them into the q with dist
	// + 1
	//return -1 since no sol

	int N = grid.size();
	std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> visited;
	std::queue<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> q;
	q.push({ {{0,0},{0,1}},0 });

	while (!q.empty()) {

		auto pointsAndDist = q.front();
		q.pop();

		auto x1y1 = pointsAndDist.first.first; //tail
		auto x2y2 = pointsAndDist.first.second; //head
		int dist = pointsAndDist.second;

		//exit condition
		if (x1y1.first == N - 1 && x1y1.second == N - 2 && x2y2.first == N - 1 && x2y2.second == N - 1) {
			return dist;
		}

		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> points;

		//horiz
		if (x1y1.first == x2y2.first) {

			if (x2y2.second + 1 < N && grid[x2y2.first][x2y2.second + 1] != 1) {
				points.push_back({ {x1y1.first, x1y1.second + 1}, {x2y2.first, x2y2.second + 1} });
			}

			if (x1y1.first + 1 < N && grid[x1y1.first + 1][x1y1.second] != 1 &&
				grid[x2y2.first + 1][x2y2.second] != 1) {
				points.push_back({ {x1y1.first + 1, x1y1.second},{x2y2.first + 1, x2y2.second} });

				points.push_back({ {x1y1.first, x1y1.second}, {x1y1.first + 1, x1y1.second} });
			}

		}

		//vert
		if (x1y1.second == x2y2.second) {

			if (x2y2.first + 1 < N && grid[x2y2.first + 1][x2y2.second] != 1) {
				points.push_back({ {x1y1.first + 1, x1y1.second}, {x2y2.first + 1, x2y2.second} });
			}

			if (x1y1.second + 1 < N && grid[x1y1.first][x1y1.second + 1] != 1 &&
				grid[x2y2.first][x2y2.second + 1] != 1) {
				points.push_back({ {x1y1.first, x1y1.second + 1},{x2y2.first, x2y2.second + 1} });

				points.push_back({ {x1y1.first, x1y1.second}, {x1y1.first, x1y1.second + 1} });
			}

		}


		for (const auto& c : points) {
			if (visited.count(c) == 0) {
				visited.insert(c);
				q.push({ c, dist + 1 });
			}
		}
	}

	return -1;
}

string removeDuplicates(string s, int k) {

	int header = 0;
	int size = s.size();

	std::vector<int> count(size);

	for (int moving = 0; moving < size; ++moving, ++header) {
		s[header] = s[moving];
		if (header > 0 && s[header - 1] == s[moving]) {
			count[header] = count[header - 1] + 1;
		}
		else {
			count[header] = 1;
		}

		if (count[header] == k) {
			header -= k;
		}
	}

	return s.substr(0, header);

}

vector<vector<int>> generateMatrix(int n) {

	std::vector<std::vector<int>> res(n, std::vector<int>(n));

	int x = 0;
	int y = 0;
	int iters = n;
	int currIters = 0;
	bool change = false;
	int dir = 0; //0 right, 1 down, 2 left, 3 up
	for (int i = 1; i <= n * n; ++i) {

		res[x][y] = i;

		++currIters;

		if (currIters == iters && !change) {
			currIters = 0;
			iters--;
			dir = (dir + 1) % 4;
			change = true;
		}
		else if (currIters == iters) {
			change = false;
			currIters = 0;
			dir = (dir + 1) % 4;
		}

		if (dir == 0) {
			y += 1;
		}
		else if (dir == 1) {
			x += 1;
		}
		else if (dir == 2) {
			y -= 1;
		}
		else {
			x -= 1;
		}

	}


	return res;
}