#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <queue>


//arrays for going in 4 dirs
std::vector<int> xdir = { 0, 1, -1, 0 };
std::vector<int> ydir = { 1, 0,  0, -1 };

class Cell
{
public:
	int h;
	int x;
	int y;

	Cell() {}
	Cell(int hh, int xx, int yy) : h(hh), x(xx), y(yy) {}

	bool operator<(const Cell& c) const
	{
		return h < c.h;
	}

	bool operator>(const Cell& c) const
	{
		return h > c.h;
	}

};

bool ValidSpace(int x, int y, std::vector<std::vector<int>>& h)
{
	if (x < 0 || y < 0 || x >= h.size() || y >= h[0].size())
		return false;

	return true;
}


int trapRainWater(std::vector<std::vector<int>>& heightMap) {

	int max = INT_MIN;
	int res = 0;

	if (heightMap.size() == 0 || heightMap[0].size() == 0)
		return 0;

	if (heightMap.size() == 1 && heightMap[0].size() == 1)
	{
		return 0;
	}

	std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;

	//push all border cells into q

	std::vector<std::vector<bool>> visited(heightMap.size(), std::vector<bool>(heightMap[0].size(), false));


	for (int i = 0; i < heightMap.size(); ++i)
	{
		for (int j = 0; j < heightMap[i].size(); ++j)
		{
			if (!(i == 0 || i == heightMap.size() - 1 || j == 0 || j == heightMap[i].size() - 1))
				continue;

			pq.push(Cell(heightMap[i][j], i, j));
			visited[i][j] = true;
		}
	}

	//flood fill unvisited neighbors
	while (!pq.empty())
	{
		Cell temp = pq.top();
		pq.pop();
		max = std::max(temp.h, max);

		for (int i = 0; i < 4; ++i)
		{
			int offx = xdir[i] + temp.x;
			int offy = ydir[i] + temp.y;

			if (ValidSpace(offx, offy, heightMap) && !visited[offx][offy])
			{
				//formula is add either 0 or temp height - current height
				//(cant add negative)
				res += std::max(0, max - heightMap[offx][offy]);

				pq.push(Cell(std::max(heightMap[offx][offy], temp.h), offx, offy));
				visited[offx][offy] = true;
			}
		}
	}

	//get lowest cell
	//update max if necessary

	//visit any unvisited neighbors 
	return res;
}


int main(void)
{
	std::vector<std::vector<int>> t(3);

	t[0] = { 1,4,3,1,3,2 };
	t[1] = { 3,2,1,3,2,4 };
	t[2] = { 2,3,3,2,3,1 };

	trapRainWater(t);
	return 0;
}


class Solution {
public:

	std::vector<int> xdir = { 0,1,-1,0 };
	std::vector<int> ydir = { 1,0,0,-1 };

	bool Valid(int x, int y, int n)
	{
		if (x < 0 || y < 0 || x >= n || y >= n)
			return false;

		return true;
	}

	class Cell {
	public:
		int h;
		int i;
		int j;
		Cell() {}
		Cell(int hh, int xx, int yy) : h(hh), i(xx), j(yy) {}

		bool operator<(const Cell& o) const
		{
			return h < o.h;
		}

		bool operator >(const Cell& o) const
		{
			return h > o.h;
		}

	};

	int swimInWater(std::vector<std::vector<int>>& grid) {

		int size = grid.size(); // N x N

		std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;

		//use a vector to hold the paths, and init'd to -1
		std::vector<std::vector<int>> calc_done(size, std::vector<int>(size, -1));

		//init pq with top left space
		pq.push(Cell(grid[0][0], 0, 0));
		calc_done[0][0] = grid[0][0];
		//while the bottom corner is -1
		//pop off a node, check in 4 dirs
		//push on nodes, where new height = max (grid[x][y], temp.height)

		while (calc_done[size - 1][size - 1] == -1)
		{
			Cell t = pq.top();
			pq.pop();

			for (int i = 0; i < 4; ++i)
			{
				int xoff = xdir[i] + t.i;
				int yoff = ydir[i] + t.j;

				if (Valid(xoff, yoff, size) && calc_done[xoff][yoff] == -1)
				{
					int maxheight = std::max(grid[xoff][yoff], t.h);
					calc_done[xoff][yoff] = maxheight;
					pq.push(Cell(maxheight, xoff, yoff));
				}
			}

		}

		return calc_done[size - 1][size - 1];

	}
};