#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>

//arrays for going in 4 dirs
std::vector<int> xdir = { 0, 1, -1, 0 };
std::vector<int> ydir = { 1, 0,  0, -1 };

bool ValidSpace(int x, int y, std::vector<std::vector<int>>& b)
{
	if (x < 0 || y < 0 || x >= b.size() || y >= b[0].size())
		return false;

	return true;
}
//need to use set for now since cant use vectors in unordered sets ()
void FloodFill(std::vector<std::vector<int>>& board, int x, int y, std::set<std::pair<int, int>>& visited)
{
	visited.insert({ x,y });

	for (int i = 0; i < 4; ++i)
	{        //use floodfill to find shortest distance (4 directions)
		int offx = x + xdir[i];
		int offy = y + ydir[i];
		//board[offx][offy] needs to be a 1
		if (ValidSpace(offx, offy, board) && board[offx][offy] && !visited.count({ offx,offy }))
		{
			FloodFill(board, offx, offy, visited);
		}
	}
}
//guaranteed to be at least 1 space between them
int shortestBridge(std::vector<std::vector<int>>& A)
{

	//islands will be represented by a set of pairs (x y)
	std::set<std::pair<int, int>> FirstIsland;
	std::set<std::pair<int, int>> SecondIsland;



	//floodfill

	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < A[i].size(); ++j)
		{
			if (A[i][j] == 1) //dont care about 0s
			{        //find the first island, mark it
				if (FirstIsland.empty())
				{
					FloodFill(A, i, j, FirstIsland);
				} //make sure element is not part of A
				else if (SecondIsland.empty() && !FirstIsland.count({ i,j }))
				{  //then find the 2nd island, mark it
					FloodFill(A, i, j, SecondIsland);
				}

			}
		}
	}

	int mindist = INT_MAX;
	//now quad find distance between all pairs (note-manhatten - 1 because doesn't count the starting square)
	for (const auto& a : FirstIsland)
	{
		for (const auto& b : SecondIsland)
		{
			int dist = std::abs(a.first - b.first) + std::abs(a.second - b.second) - 1;
			mindist = std::min(dist, mindist);
		}

	}

	return mindist;
}

int main(void)
{


	return 0;
}

bool Formula(int sum, int i, int n)
{
	return (sum * i % n == 0);
}
//formula:
//only possible if sum * i % n == 0
//          for i from 1 to n-1
// (lots of math)
//similar to sum of subsets dp problem
bool HasPossibleSolution(int sum, int n)
{
	for (int i = 1; i <= n / 2; ++i)
	{
		if (Formula(sum, i, n))
		{
			return true;
		}
	}

	return false;
}

//each row:
//number of elements added together
//so row 0 is 0
//row 1 is one element added together
//remember it comes from the top

bool splitArraySameAverage(std::vector<int>& A) {

	//m is equal to size of array divided by 2
	//this is because one partition is less than length of array divided by 2
	std::vector<std::unordered_set<int>> dpSums((A.size() / 2) + 1);

	int sum = std::accumulate(A.begin(), A.end(), 0);

	if (!HasPossibleSolution(sum, A.size()))
	{
		return false;
	}

	dpSums[0].insert(0); // base

	for (int num : A)
	{
		for (int i = A.size() / 2; i >= 1; --i)
		{
			//lamda that adds the above value
			std::transform(dpSums[i - 1].begin(), dpSums[i - 1].end(), std::inserter(dpSums[i], dpSums[i].end()),
				[num](int temp) {return temp + num; });
		}
	}

	for (int i = 1; i <= A.size() / 2; ++i)
	{
		if (Formula(sum, i, A.size()) && dpSums[i].count(sum * i / A.size()))
		{
			return true;
		}
	}

	return false; //should never get here
}