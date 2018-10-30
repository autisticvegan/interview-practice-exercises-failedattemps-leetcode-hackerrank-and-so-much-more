#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>

/*
* Complete the 'SExpression' function below.
*
* The function is expected to return a STRING.
* The function accepts STRING nodes as parameter.
*/

const int MAXNODES = 26;

bool HelperCycle(char node, std::vector<std::vector<bool>> g, std::vector<bool>& visited)
{
	if (visited[node - 'A'])
		return true;

	visited[node - 'A'] = true;

	for (int i = 0; i < MAXNODES; ++i)
	{
		if (g[node - 'A'][i])
		{
			if (HelperCycle(i + 'A', g, visited))
				return true;
		}
	}
	return false;
}

std::string expression(char root, std::vector<std::vector<bool>>& matrix)
{
	std::string left;
	std::string right;

	for (int i = 0; i < MAXNODES; ++i)
	{
		if (matrix[root - 'A'][i])
		{
			left = expression(static_cast<char>(i + 'A'), matrix);
			for (int j = i+1; j < MAXNODES; ++j)
			{
				if (matrix[root - 'A'][j])
				{
					right = expression(static_cast<char>(j + 'A'), matrix);
					break;
				}
			}

			break;
		}
	}
	std::string ret = "(";
	ret += root;
	ret += left;
	ret += right;
	ret += ")";
	return ret;

	//WARNING - DO NOT DO THIS - IT WILL GIVE GARBAGE ON THE STACK
//	return "(" + root + left + right + ")";
}

std::string SExpression(std::string nodes) {

	//first construct the graph.  While doing that, we can check for error E2
	//26 max nodes
	//nodes separated by comma, so i, i+2, 6 chars between pairs
	std::vector<std::vector<bool>> matrix(MAXNODES, std::vector<bool>(MAXNODES, false));

	std::unordered_set<char> nodesSet;
	bool E2 = false;

	for (int i = 1; i < nodes.length(); i += 6)
	{
		int row = nodes[i] - 'A';
		int col = nodes[i + 2] - 'A';

		if (matrix[row][col])
		{
			E2 = true;
		}
		matrix[row][col] = true;

		nodesSet.insert(nodes[i]);
		nodesSet.insert(nodes[i + 2]);
	}

	//once graph is constructed, we can check for E1
	for (int i = 0; i < MAXNODES; ++i)
	{
		int children = 0;
		for (int j = 0; j < MAXNODES; ++j)
		{
			if (matrix[i][j])
				children++;
		}

		if (children > 2)
			return "E1";
	}

	if (E2)
	{
		return "E2";
	}
	//now check E3 and E4

	int numberOfRoots = 0;
	char root = '!'; //if never updated, do E5

	for (char c : nodesSet)
	{
		for (int i = 0; i < MAXNODES; ++i)
		{
			if (matrix[i][c - 'A'])
				break;

			if (i == 25)
			{
				++numberOfRoots;
				root = c;
				std::vector<bool> v(MAXNODES, false);
				if (HelperCycle(c, matrix, v))
				{
					return "E3";
				}
			}
		}
	}

	if (numberOfRoots == 0)
		return "E3";

	if (numberOfRoots > 1)
		return "E4";

	//E5 is input error
	if (root == '!')
		return "E5";

	//now make string
	return expression(root, matrix);
}

int main(void)
{
//	std::string in = "(A,B) (A,C) (B,D) (D,C)";
//	std::string out = SExpression(in);

//	std::string in2 = "(B,D) (D,E) (A,B) (C,F) (E,G) (A,C)";
//	std::string out2 = SExpression(in2);

	std::string in3 = "(A,B)";
	std::string out3 = SExpression(in3);

	return 0;
}
