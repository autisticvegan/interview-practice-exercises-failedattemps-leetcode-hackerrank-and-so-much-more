#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>

class bfs_info
{
public:

	int x = 0;
	int y = 0;
	int runningTotalOfMoves = 0;
	std::vector<std::vector<int>> boardcopy;


};

bool solved(std::vector<std::vector<int>>& b)
{

	std::vector<std::vector<int>> t;

	std::vector<int> tt({ 1,2,3 });
	std::vector<int> ttt({ 4,5,0 });

	t.push_back(tt);
	t.push_back(ttt);


	return t == b;
}

bool ValidMove(int x, int y)
{
	if (x > 1 || y > 2 || x < 0 || y < 0)
		return false;

	return true;
}

std::string Board2String(std::vector<std::vector<int>>& b)
{
	std::string ret;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			ret.push_back(b[i][j]);
		}
	}

	return ret;
}

int slidingPuzzle(std::vector<std::vector<int>>& board)
{
	//bfs because least number of moves

	std::queue<bfs_info> boardStatesToDo;

	//cant use vector of vector of ints for unordered_sets
	std::unordered_set<std::string> checkedBoards;

	//find the first zero, and init the queue and set

	int xz = 0;
	int yz = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board[i][j] == 0)
			{
				xz = i;
				yz = j;
				break;
			}
		}
	}

	bfs_info first;
	first.boardcopy = board;
	first.x = xz;
	first.y = yz;

	boardStatesToDo.push(first);

	checkedBoards.insert(Board2String(board));

	std::vector<int> xoff({ -1,0,0,1 });
	std::vector<int> yoff({ 0,-1,1,0 });

	while (!boardStatesToDo.empty())
	{
		bfs_info current = boardStatesToDo.front();
		boardStatesToDo.pop();

		if (solved(current.boardcopy))
		{
			return current.runningTotalOfMoves;
		}

		//move in 4 dirs
		for (int i = 0; i < 4; ++i)
		{
			int xcurr = xoff[i] + current.x;
			int ycurr = yoff[i] + current.y;

			if (ValidMove(xcurr, ycurr))
			{
				//make a new board with the swap
				std::vector<std::vector<int>> newboard = current.boardcopy;

				std::swap(newboard[xcurr][ycurr], newboard[current.x][current.y]);

				std::string checkthis = Board2String(newboard);

				//if we havent seen it before, push it onto the queue and insert it
				if (checkedBoards.count(checkthis) == 0)
				{
					bfs_info newinfo;
					newinfo.x = xcurr;
					newinfo.y = ycurr;
					newinfo.boardcopy = newboard;
					newinfo.runningTotalOfMoves = current.runningTotalOfMoves + 1;
					boardStatesToDo.push(newinfo);

					checkedBoards.insert(checkthis);
				}

			}
		}
	}
	//no answer found
	return -1;
}

bool validTicTacToe(std::vector<std::string>& board)
{

	//check x and o count

	int xcount = 0;
	int ocount = 0;
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[i].length(); ++j)
		{
			if (board[i][j] == 'X')
				++xcount;
			else if (board[i][j] == 'O')
				++ocount;
		}
	}

	if (ocount > xcount)
		return false;

	if (xcount > ocount + 1)
		return false;


	//check for game over conditions
// row, row, row

//col, col, col

//cross, cross

	bool xvic = false;
	bool ovic = false;


	for (int i = 0; i < 3; ++i)
	{
		if (board[i] == "XXX")
		{
			if (ovic)
				return false;

			xvic = true;
		}

		if (board[i] == "OOO")
		{
			if (xvic)
				return false;
			ovic = true;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		std::string temp;
		temp.push_back(board[0][i]);
		temp.push_back(board[1][i]);
		temp.push_back(board[2][i]);

		if (temp == "XXX")
		{
			if (ovic)
				return false;

			xvic = true;
		}

		if (temp == "OOO")
		{
			if (xvic)
				return false;

			ovic = true;
		}
	}

	std::string tempc;
	tempc.push_back(board[0][0]);
	tempc.push_back(board[1][1]);
	tempc.push_back(board[2][2]);

	if (tempc == "XXX")
	{
		if (ovic)
			return false;

		xvic = true;
	}

	if (tempc == "OOO")
	{
		if (xvic)
			return false;
		ovic = true;
	}

	std::string tempcc;
	tempcc.push_back(board[2][0]);
	tempcc.push_back(board[1][1]);
	tempcc.push_back(board[0][2]);

	if (tempcc == "XXX")
	{
		if (ovic)
			return false;

		xvic = true;
	}

	if (tempcc == "OOO")
	{
		if (xvic)
			return false;
		ovic = true;
	}


	if (xvic && ovic)
		return false;

	if (xvic && xcount == ocount)
		return false;

	if (ovic && xcount > ocount)
		return false;


	return true;
}


int main(void)
{
	//more tic tac toe coming soon to a theater near you

	std::string t = "XOX";


	std::vector<std::string> t1;

	t1.push_back("OXX");
	t1.push_back("XOX");
	t1.push_back("OXO");

//	for(int i = 0; i < 3; ++i)
//	t1.push_back("XO ");

	validTicTacToe(t1);

	return 0;
}