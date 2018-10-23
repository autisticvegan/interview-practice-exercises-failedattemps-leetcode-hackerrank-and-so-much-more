#include <vector>
#include <list>


class Solution {
public:

	bool ValidSquares(std::vector<std::vector<char>>& board, int row, int col, char v)
	{
		int offsetX = 0;
		int offsetY = 0;

		offsetX = row - row % 3;
		offsetY = col - col % 3;


		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{

				char ins = board[i + offsetX][j + offsetY];

				if (ins == v)
					return false;
			}

		}

		return true;
	}

	bool ValidColumn(std::vector<std::vector<char>>& board, int col, char v)
	{
		for (int i = 0; i < 9; ++i)
		{
			char ins = board[i][col];

			if (v == ins)
				return false;
		}

		return true;
	}

	bool ValidRow(std::vector<std::vector<char>>& board, int row, char v)
	{
		for (int i = 0; i < 9; ++i)
		{
			char ins = board[row][i];
			if (v == ins)
				return false;

		}

		return true;
	}

	bool validSudoku(std::vector<std::vector<char>>& b, int i, int j, char num2try)
	{
		if (!ValidRow(b, i, num2try))
			return false;

		if (!ValidColumn(b, j, num2try))
			return false;

		if (!ValidSquares(b, i, j, num2try))
			return false;

		return true;
	}


	bool ss(std::vector<std::vector<char>>& b, int row, int col)
	{
        //all done
		if(row == 9)
			return true;

        //first go rows, then go cols
		if (col == 9)
			return ss(b, row + 1, 0);

        //skip it
		if (b[row][col] != '.')
		{
			return ss(b, row, col + 1);
		}

			for (char c = '1'; c <= '9'; ++c)
			{
				if (validSudoku(b, row, col, c))
				{
					b[row][col] = c;

					if (ss(b,row,col+1))
						return true; // done
                    
                    //important: need to put back to . if our solve failed
					b[row][col] = '.';
				}
			}

		return false;
	}

	void solveSudoku(std::vector<std::vector<char>>& board) {
		ss(board, 0, 0);
	}
};

int main(void)
{
	std::vector<std::vector<char>> u;

		std::vector<char> t{ '5','3','.','.','7','.','.','.','.', };
	u.push_back(t);

	std::vector<char> t1{ '6','.','.','1','9','5','.','.','.', };
	u.push_back(t1);
	std::vector<char> t2{ '.','9','8','.','7','.','.','6','.', };
	u.push_back(t2);
	std::vector<char> t3{ '8','.','.','.','6','.','.','.','3', };
	u.push_back(t3);
	std::vector<char> t4{ '4','.','.','8','.','3','.','.','1', };
	u.push_back(t4);
	std::vector<char> t5{ '7','.','.','.','2','.','.','.','6', };
	u.push_back(t5);
	std::vector<char> t6{ '.','6','.','.','.','.','2','8','.', };
	u.push_back(t6);
	std::vector<char> t7{ '.','.','.','4','1','9','.','.','5', };
	u.push_back(t7);
	std::vector<char> t8{ '.','.','.','.','8','.','.','7','9', };
	u.push_back(t8);


	Solution a;
	a.solveSudoku(u);

		return 0;
}