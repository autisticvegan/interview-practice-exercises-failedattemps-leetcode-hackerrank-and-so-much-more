#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>
#include <istream>
#include <iterator>
#include <iostream>
#include <sstream>
#include <deque>

int jump(std::vector<int>& nums) {

	int n = nums.size(), step = 0, start = 0, end = 0;

	while (end < n - 1)
	{
		++step;
		int maxend = end + 1;

		for (int i = start; i <= end; i++)
		{
			if (i + nums[i] >= n - 1) 
				return step;
			
			maxend = std::max(maxend, i + nums[i]);
		}

		start = end + 1;
		end = maxend;
	}
	return step;


}

bool canJump(std::vector<int>& nums) {


	int i = 0;
	int n = nums.size();
	for (int reach = 0; i < n && i <= reach; ++i)
	{
		if (reach >= n)
			return true;

		reach = std::max(i + nums[i], reach);
	}


	return i == n;

}

bool ValidDiag(std::vector<std::string>& b, int x, int y, int n)
{
	for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (b[i][j] == 'Q')
			return false;
	}

	for (int i = x - 1, j = y + 1; i >= 0 && j < n; --i, ++j)
	{
		if (b[i][j] == 'Q')
			return false;
	}

	return true;
}

bool ValidCol(std::vector<std::string>& b, int x, int y, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (b[i][y] == 'Q' && i != x)
			return false;
	}
	return true;
}

bool ValidRow(std::vector<std::string>& b, int x, int y, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (b[x][i] == 'Q' && i != y)
			return false;
	}
	return true;
}

bool ValidSpace(std::vector<std::string>& b, int x, int y, int n)
{
	if (ValidCol(b, x, y, n) && ValidDiag(b, x, y, n))
		return true;

	return false;
}

//idea, similar to sudoku, recursive backtracking, only need row (not col) because only one Q per col
//also only check the V up of the diags, since we are moving top down

void RecurseSolveNQueens(std::vector<std::vector<std::string>>& res, std::vector<std::string>& b, int r, int size)
{
	//terminate condition: when row = size
	if (r == size)
	{
		res.push_back(b);
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		if (ValidSpace(b, r, i, size))
		{
			b[r][i] = 'Q';
			RecurseSolveNQueens(res, b, r + 1, size);
			b[r][i] = '.';
		}
	}

}

std::vector<std::vector<std::string>> solveNQueens(int n) {

	std::vector<std::vector<std::string>> res;

	std::vector<std::string> nQueens(n, std::string(n, '.'));
	RecurseSolveNQueens(res, nQueens, 0, n);

	return res;
}

int main(void)
{
	std::vector<int> t = {10,9,8,7,6,5,4,3,2,1,1,0};
	jump(t);

	return 0;
}