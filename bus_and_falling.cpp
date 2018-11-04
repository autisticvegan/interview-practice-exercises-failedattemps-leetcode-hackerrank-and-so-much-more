#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>

int numBusesToDestination(std::vector<std::vector<int>>& routes, int S, int T) {

	if (routes.empty())
		return -1;

	if (S == T)
		return 0;



	//bfs

	std::unordered_map<int, std::unordered_set<int>> stop2routes;

	for (int i = 0; i < routes.size(); ++i)
	{
		for (int j = 0; j < routes[i].size(); ++j)
		{
			stop2routes[routes[i][j]].insert(i);
		}
	}

	std::unordered_set<int> visited;

	std::queue<std::pair<int, int>> need_to_visit;

	//start at S, end at T
	need_to_visit.push({ S,0 }); //2nd number is number of buses weve been on at this point
	visited.insert(S);

	//this will find shortest because its bfs
	while (!need_to_visit.empty())
	{
		std::pair<int, int> currentStop = need_to_visit.front();

		//first check if we are done
		if (currentStop.first == T)
		{
			return currentStop.second;
		}

		need_to_visit.pop();

		//loop through the routes for S (all the places we can go from here)
		for (int i : stop2routes[currentStop.first])
		{   //now that we have a route, index into routes and look through all those stops
			for (int nextStop : routes[i])
			{
				if (visited.count(nextStop))
				{//can also do this with return value from insert (returns iterator)
					continue;
				}
				else //havent seen it yet
				{
					need_to_visit.push({ nextStop,currentStop.second + 1 });
					visited.insert(nextStop);
				}
			}

			//clear out routes weve visited
			routes[i].clear();
		}
	}

	return -1; //no possible path
}

//dynamic programming
int minFallingPathSum(std::vector<std::vector<int>>& A) {

	if (A.empty())
		return 0;

	//for each square, we have 3 choices, upper left, center, or upper right (obviously not at sides)
	std::vector<std::vector<int>> board(A.size(), std::vector<int>(A[0].size()));

	board[0] = A[0];

	for (int i = 1; i < A.size(); ++i)
	{
		for (int j = 0; j < A[i].size(); ++j)
		{
			//min of 3 vals, current A[i][j] + choose(A[i-1][j], A[i-1][j-1], A[i-1][j+1])
			if (j == 0)
			{
				board[i][j] = std::min(A[i][j] + board[i - 1][j], A[i][j] + board[i - 1][j + 1]);
			}
			else if (j == A[i].size() - 1)
			{
				board[i][j] = std::min(A[i][j] + board[i - 1][j], A[i][j] + board[i - 1][j - 1]);
			}
			else
			{
				int min1 = std::min(A[i][j] + board[i - 1][j], A[i][j] + board[i - 1][j - 1]);
				int min2 = std::min(min1, A[i][j] + board[i - 1][j + 1]);
				board[i][j] = min2;
			}

		}
	}

	auto it = board[board.size() - 1].begin();
	auto ite = board[board.size() - 1].end();
	return *std::min_element(it, ite);
}

int main(void)
{
	std::vector<std::vector<int>> routes(4, std::vector<int>(3));

	std::vector<int> a({0,1,2 });
	routes[0] = a;

	std::vector<int> aa({ 0,3,4 });
	routes[1] = aa;
	std::vector<int> aaa({ 2,5,6 });
	routes[2] = aaa;
	std::vector<int> aaaa({ 4,7,6 });
	routes[3] = aaaa;

	return 0;
}