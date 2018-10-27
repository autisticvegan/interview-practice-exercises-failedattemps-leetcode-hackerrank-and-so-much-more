#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
//score to path
std::map<int, std::vector<int>> results;

std::unordered_map<int, int> node2score;

//visit all nodes:
//first visit is special
//after that:
//minus cost
//if cost is < 0, abort
//else if we havent visited this one yet, add score
//
//if current node is exit point, end
//
//and pushback your path and score to the results
//final result is at end of map

void dfs(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int vertex, int fuelpoints, int score, std::vector<int>& path)
{
	bool dontaddscore = false;

	//if weve been here before, dont add the score
	if (visited[vertex])
	{
		dontaddscore = true;
	}

	//if we ran out of fuel, abort
	if (fuelpoints < 0)
		return;

	path.push_back(vertex);

	visited[vertex] = true;

	if (!dontaddscore)
	{
		score += node2score[vertex];
	}

	//if we are back at origin, push to answers
	if (vertex == 0)
	{
		results.insert({ score, path });
	}

	int currentfuel = fuelpoints;

	for (int i = 0; i < graph[vertex].size(); ++i)
	{
		//if ! 0, then we have a path
		if (graph[vertex][i] != 0)
		{
			int newfuel = currentfuel - graph[vertex][i];
			if (newfuel < 0)
				continue;
			//dont know how to do this without a copy - Please help me smarter developers~ uwu
			std::vector<int> z = path;
			dfs(graph, visited, i, newfuel, score, z);
			//do we popback here?
			//path.pop_back();
		}
	}

}

int main(void)
{
	//adjust this
	int initial_fuel_points = 10;
	
	//scores:
	//0-20
	//1-5
	//2-10
	//3-15

	//costs:
	//0-1: 5
	//0-2: 6
	//1-3: 7

	//store nodes 
	node2score.insert({ 0,20 });
	node2score.insert({ 1,5 });
	node2score.insert({ 2,10 });
	node2score.insert({ 3,15 });

	//adjacency matrix, costs
	std::vector<std::vector<int>> graph(4,std::vector<int>(4));

	graph[0][1] = 5;
	graph[1][0] = 5;

	graph[0][2] = 6;
	graph[2][0] = 6;

	graph[1][3] = 7;
	graph[3][1] = 7;


	//visited already
	std::vector<bool> visited(4,false);
	std::vector<int> path;
	dfs(graph, visited, 0, initial_fuel_points, 0, path);

	//max score
	std::cout << results.rbegin()->first << std::endl;
	//path
	for (int i : results.rbegin()->second)
	{
		std::cout << i << " ";
	}

	return 0;
}