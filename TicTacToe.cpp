#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <istream>
#include <unordered_set>
#include <random>

class TicTacToe
{
public:
	std::vector<std::vector<char>> board;

	int boardSize = 3;

	//optimization
	//std::unordered_set<std::string> victories;

	enum VICTORY_STATUS { NONE, XWINS, OWINS, TIE };

	TicTacToe();
	void PrintBoard();
	void GetInput(bool p1);
	bool SetMove(int x, int y, char xoro);
	bool ValidSpace(int x, int y);
	VICTORY_STATUS CheckVictory();
	void CheckVictoryStatus();

	//helper
	VICTORY_STATUS checkstring(std::string& s);
	void PrintVictory();

	bool blockingAI = true;
	bool solved = false;
	VICTORY_STATUS vic = NONE;
};

//loop
/*
	print board
	get input
	check input
	set move
	check victory
	print board
	other player move

	AI:
	check each row for doubles
	if see double, place there

*/

TicTacToe::VICTORY_STATUS TicTacToe::checkstring(std::string& s)
{
	if (s == "XXX")
		return XWINS;
	else if (s == "OOO")
		return OWINS;

	return NONE;
}

void TicTacToe::CheckVictoryStatus()
{
	VICTORY_STATUS vt = CheckVictory();
	if (vt != VICTORY_STATUS::NONE)
	{
		vic = vt;
		solved = true;
	}
}

TicTacToe::VICTORY_STATUS TicTacToe::CheckVictory()
{
	//check rows
	VICTORY_STATUS ret = NONE;

	std::string t1;
	std::string t2;
	std::string t3;

	for (int i = 0; i < boardSize; ++i)
	{
		t1.push_back(board[i][0]);
		t2.push_back(board[i][1]);
		t3.push_back(board[i][2]);
	}

	ret = checkstring(t1);
	if (ret != NONE)
		return ret;

	ret = checkstring(t2);
	if (ret != NONE)
		return ret;


	ret = checkstring(t3);
	if (ret != NONE)
		return ret;

	t1.clear();
	t2.clear();
	t3.clear();

	//check cols

	for (int i = 0; i < boardSize; ++i)
	{
		t1.push_back(board[0][i]);
		t2.push_back(board[1][i]);
		t3.push_back(board[2][i]);
	}

	ret = checkstring(t1);
	if (ret != NONE)
		return ret;

	ret = checkstring(t2);
	if (ret != NONE)
		return ret;


	ret = checkstring(t3);
	if (ret != NONE)
		return ret;

	t1.clear();
	t2.clear();

	for (int i = 0; i < boardSize; ++i)
	{
		t1.push_back(board[i][i]);
		t2.push_back(board[boardSize-i-1][i]);
	}

	//check diags
	ret = checkstring(t1);
	if (ret != NONE)
		return ret;

	ret = checkstring(t2);
	if (ret != NONE)
		return ret;

	int dc = 0;
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			if (board[i][j] == '-')
				++dc;
		}
	}

	if (dc == 0)
		return TIE;

	return NONE;
}

void TicTacToe::PrintVictory()
{
	if (!solved)
		return;

	if (vic == XWINS)
	{
		std::cout << "X WINS THE GAME!!!1\n";
	}
	else if (vic == OWINS)
	{
		std::cout << "O WINS THE GAME!!!1\n";
	}
	else
	{
		std::cout << "TIE!!!!!!\n";
	}


}

TicTacToe::TicTacToe()
{
	std::vector<std::vector<char>> b(boardSize, std::vector<char>(boardSize));
	board = b;

	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			board[i][j] = '-';
		}
	}

}

bool TicTacToe::ValidSpace(int x, int y)
{
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize)
		return false;

	//if already occupied not valid either

	if (board[x][y] != '-')
		return false;

	return true;
}

bool TicTacToe::SetMove(int x, int y, char xoro)
{
	if (!ValidSpace(x, y))
		return false;

	board[x][y] = xoro;
	return true;
}

void TicTacToe::GetInput(bool p1)
{
	//get input, validate it, and put it
	if (p1)
	{
		int x, y;

		while (true)
		{
			std::string strInput;
			std::getline(std::cin, strInput);

			// This code converts from string to number safely.
			std::stringstream myStream(strInput);
			
			

			bool v(myStream >> x);
			bool v2(myStream >> y);

			if (v && v2 && ValidSpace(x, y))
				break;
			
			std::cout << "Invalid input, please try again" << std::endl;
		}

		SetMove(x, y, 'X');
		
	}
	else
	{

		if (blockingAI)
		{
			//find where spot is
			std::string t1;
			std::string t2;
			std::string t3;

			for (int i = 0; i < boardSize; ++i)
			{
				t1.push_back(board[i][0]);
				t2.push_back(board[i][1]);
				t3.push_back(board[i][2]);
			}

			if (t1 == "X-X")
			{
				SetMove(1, 0, 'O');
				return;
			}

			if (t1 == "XX-")
			{
				SetMove(2, 0, 'O');
				return;
			}

			if (t1 == "-XX")
			{
				SetMove(0, 0, 'O');
				return;
			}

			if (t2 == "X-X")
			{
				SetMove(1, 1, 'O');
				return;
			}

			if (t2 == "XX-")
			{
				SetMove(2, 1, 'O');
				return;
			}

			if (t2 == "-XX")
			{
				SetMove(0, 1, 'O');
				return;
			}

			if (t3 == "X-X")
			{
				SetMove(1, 2, 'O');
				return;
			}

			if (t3 == "XX-")
			{
				SetMove(2, 2, 'O');
				return;
			}

			if (t3 == "-XX")
			{
				SetMove(0, 2, 'O');
				return;
			}

			t1.clear();
			t2.clear();
			t3.clear();

			for (int i = 0; i < boardSize; ++i)
			{
				t1.push_back(board[0][i]);
				t2.push_back(board[1][i]);
				t3.push_back(board[2][i]);
			}

			if (t1 == "X-X")
			{
				SetMove(0, 1, 'O');
				return;
			}

			if (t1 == "XX-")
			{
				SetMove(0, 2, 'O');
				return;
			}

			if (t1 == "-XX")
			{
				SetMove(0, 0, 'O');
				return;
			}

			if (t2 == "X-X")
			{
				SetMove(1, 1, 'O');
				return;
			}

			if (t2 == "XX-")
			{
				SetMove(1, 2, 'O');
				return;
			}

			if (t2 == "-XX")
			{
				SetMove(1, 0, 'O');
				return;
			}

			if (t3 == "X-X")
			{
				SetMove(2, 1, 'O');
				return;
			}

			if (t3 == "XX-")
			{
				SetMove(2, 2, 'O');
				return;
			}

			if (t3 == "-XX")
			{
				SetMove(2, 0, 'O');
				return;
			}

			//diags

			t1.clear();
			t2.clear();

			for (int i = 0; i < boardSize; ++i)
			{
				t1.push_back(board[i][i]);
				t2.push_back(board[boardSize-1-i][i]);
			}

			if (t2 == "X-X")
			{
				SetMove(1, 1, 'O');
				return;
			}

			if (t2 == "XX-")
			{
				SetMove(0, 2, 'O');
				return;
			}

			if (t2 == "-XX")
			{
				SetMove(2, 0, 'O');
				return;
			}

			if (t1 == "X-X")
			{
				SetMove(1, 1, 'O');
				return;
			}

			if (t1 == "XX-")
			{
				SetMove(2, 2, 'O');
				return;
			}

			if (t1 == "-XX")
			{
				SetMove(0, 0, 'O');
				return;
			}

			//else random
			int x, y;

			while (true)
			{
				x = std::rand() % 3;
				y = std::rand() % 3;

				if (ValidSpace(x, y))
					break;
				//keep doing random numbers until you get one that is within range
			}
			SetMove(x, y, 'O');

		}
		else //random ai
		{
			int x, y;

			while (true)
			{
				x = std::rand() % 3;
				y = std::rand() % 3;

				if (ValidSpace(x, y))
					break;
				//keep doing random numbers until you get one that is within range
			}
			SetMove(x, y, 'O');
		}
	}
	//check for victory, if so mark solved
}



void TicTacToe::PrintBoard()
{
	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			std::cout << board[i][j];
			if (j != boardSize - 1)
				std::cout << "|";
		}
		std::cout << std::endl;
	}
}

int main(void)
{
	TicTacToe t;
	t.PrintBoard();
	while (!t.solved)
	{
		std::cout << std::endl;
		//input, sets move
		t.GetInput(true);
		t.PrintBoard();
		t.CheckVictoryStatus();
		if (t.solved)
		{
			t.PrintVictory();
			break;
		}
		
		std::cout << std::endl;

		t.GetInput(false);
		t.PrintBoard();
		t.CheckVictoryStatus();

		if (t.solved)
		{
			t.PrintVictory();
			break;
		}
		
	}

	return 0;
}