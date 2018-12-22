#include <vector>
#include <string>
#include <algorithm>



const int BLACK = 1;
const int BLANK = 0;
const int WHITE = -1;

//can flip color by doing -
//starts as black, then switches each time
bool DFS(std::vector<std::vector<int>>& g, int i, std::vector<int>& colors, int currentColor)
{
	if (colors[i] != BLANK)
	{
		return colors[i] == currentColor; //we switch each time
	}

	colors[i] = currentColor;
	for (int j = 0; j < g[i].size(); ++j)
	{
		if (!DFS(g, g[i][j], colors, -currentColor))
			return false;
	}

	return true;
}


bool isBipartite(std::vector<std::vector<int>>& graph) {

	std::vector<int> colors(graph.size(), 0);

	for (int i = 0; i < graph.size(); ++i)
	{
		if (colors[i] == BLANK && !DFS(graph, i, colors, BLACK))
			return false;
	}


	return true;
}

int main(void)
{
	std::vector<std::vector<int>> t;

	std::vector<int> tt = { 1,3 };
	std::vector<int> ttt = { 0, 2 };

	t.push_back(tt);
	t.push_back(ttt);
	t.push_back(tt);
	t.push_back(ttt);

	isBipartite(t);

	return 0;
}