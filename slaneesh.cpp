#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <ctime>
#include <chrono>
#include <stack>

using namespace std::chrono;
using namespace std;
void marktheisland(std::vector<std::vector<int>>& grid, int x, int y, int sizex, int sizey)
{
	int xa[] = { 0,0,1,-1 };
	int ya[] = { 1,-1,0,0 };

	std::stack<std::pair<int, int>> q;

	std::pair<int, int> p(x, y);
	q.push(p);

	while (!q.empty())
	{
		std::pair<int, int> current = q.top();
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int xoff = current.first + xa[i];
			int yoff = current.second + ya[i];

			if (xoff < 0 || yoff < 0 || xoff >= sizex || yoff >= sizey)
				continue;

			if (grid[xoff][yoff] == 1)
			{
				std::pair<int, int> p(xoff, yoff);
				q.push(p);
				grid[xoff][yoff] = 0;
			}


		}


	}

}

int numIslands(vector<vector<int>>& grid) {

	int islandcount = 0;

	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j] == 1)
			{
				++islandcount;
				marktheisland(grid, i, j, grid.size(), grid[i].size());
			}
		}
	}

	return islandcount;
}

bool get40PercentChoice() {
	int c = std::rand() % 6; // 0 to 4
	return c <= 1;
}

const int BIGNUM = 3;

bool isValidCell(int x, int y, std::vector<std::vector<int>>& g) {
	return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size() || g[x][y] == 0);
}

std::vector<int> xDirs{ 0,0,1,-1 };
std::vector<int> yDirs{ -1,1,0,0 };

using namespace std;
int main(void) {
	std::srand(std::time(nullptr));
	//generate big graph

	std::vector<std::vector<int>> huge(BIGNUM, std::vector<int>(BIGNUM));

	for (int i = 0; i < BIGNUM; ++i) {

		for (int j = 0; j < BIGNUM; ++j) {
			bool setToOne = get40PercentChoice();
			if (setToOne) {
				huge[i][j] = 1;
			}
		}
	}


	std::vector<std::pair<int, int>> edges;
	//fill edges
	for (int i = 0; i < BIGNUM; ++i) {

		for (int j = 0; j < BIGNUM; ++j) {
			
			if (huge[i][j] == 1) {
				
				int vertexNum = i * BIGNUM + j;

				//four dirs
				for (int k = 0; k < 4; ++k) {
					int newX = i + xDirs[k];
					int newY = j + yDirs[k];

					if (isValidCell(newX, newY, huge)) {

						int newVertex = newX * BIGNUM + newY;

						edges.push_back({ newVertex, vertexNum });
					}
				}

			}

		}
	}


	using namespace boost;
	{
		typedef adjacency_list <vecS, vecS, undirectedS> Graph;

		Graph G;
		
		for (const auto& p : edges) {
			add_edge(p.first, p.second, G);
		}
		
		std::vector<int> component(num_vertices(G));
		auto start = high_resolution_clock::now();


		int num = connected_components(G, &component[0]);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		start = high_resolution_clock::now();
		int myNum = numIslands(huge);
		stop = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop - start);

		cout << duration.count() << endl;
		std::cout << duration2.count() << std::endl;

		cout << "Total number of components: " << num << endl;
		std::cout << "Total number of my: " << myNum << std::endl;
	}
	return 0;

}