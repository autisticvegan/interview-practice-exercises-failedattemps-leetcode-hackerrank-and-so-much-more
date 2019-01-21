#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_set>
//can also use std::bisect
//or if you can copy then std::binary_search

	//make adjacency list

	// use dfs, to make sure we dont have cycle, we can return true (already visited)

	//have 3 things - the graph, visiting, and visited.
	//if weve seen this node while visiting, return true
	//if weve visited this node, return false
	// insert to visiting
	//check all the neighbors
	// erase from visiting
	// mark as visited and pushback to results
	//end of dfs return false;
std::vector<int> findOrder(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {


	std::vector<std::vector<int>> graph(numCourses);

	std::vector<int> empty;

	for (const auto& p : prerequisites)
	{
		graph[p.second].push_back(p.first);
	}

	std::vector<bool> visited(numCourses, false); //can also use an unordered set for this
	std::unordered_set<int> visiting;
	std::vector<int> res;

	for (int i = 0; i < numCourses; ++i)
	{
		if (!visited[i] && dfs(graph, visited, visiting, res, i))
			return empty;
	}


	std::reverse(res.begin(), res.end());
	return res;
}


bool dfs(std::vector<std::vector<int>>& g, std::vector<bool>& visited, std::unordered_set<int>& visiting, std::vector<int>& res, int start)
{
	//return true if start is on the visiting list
	if (visiting.count(start))
		return true;

	//if it has been visited, return false;
	if (visited[start])
		return false;

	visiting.insert(start);

	//if we find a cycle, return true
	for (int i : g[start])
	{
		if (dfs(g, visited, visiting, res, i))
			return true;
	}

	visiting.erase(start);
	visited[start] = true;
	res.push_back(start);
	return false;
}


int robo(int first, int last, std::vector<int>& v)
{
	int current = 0;
	int prev = 0;

	for (int i = first; i <= last; ++i)
	{
		int temp = std::max(current, prev + v[i]);
		prev = current;
		current = temp;
	}

	return current;
}

int rob(std::vector<int>& nums) {

	if (nums.size() < 2)
	{
		if (nums.size() == 1)
			return nums[0];

		return 0;
	}

	return std::max(robo(0, nums.size() - 2, nums), robo(1, nums.size() - 1, nums));


}

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 class Solution {
 public:
	 ListNode* reverseBetween(ListNode* head, int m, int n) {

		 if (!head)
			 return nullptr;

		 // n cn pc
		 int count = 0;

		 int iterations = n - m;

		 ListNode* begin = head;
		 ListNode* previous = nullptr;

		 while (count < m - 1)
		 {
			 previous = begin;
			 begin = begin->next;
			 ++count;
		 }

		 ListNode* next = nullptr;

		 ListNode* prev = previous;
		 ListNode* tail = begin;

		 while (iterations >= 0)
		 {
			 next = begin->next;
			 begin->next = previous;
			 previous = begin;
			 begin = next;

			 --iterations;
		 }

		 if (prev)
		 {
			 prev->next = previous;
		 }
		 else
		 {
			 head = previous;
		 }

		 tail->next = begin;

		 return head;
	 }
 };

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {

	// binary search
	// end is last value of last row

	/*
		f x x x x
		x x x x x
		x x x x l

		mid is vert / 2, horiz / 2

	*/

	if (matrix.empty() || matrix[0].empty())
		return false;

	int val = INT_MAX;


	int columns = matrix[0].size();
	int first = 0;
	int last = matrix.size() * columns; //what happens if overflows
	while (first < last)
	{
		int mid = last / 2 + first / 2;

		int result = matrix[mid / columns][mid % columns];
		if (result == target)
			return true;

		if (target < result)
		{
			last = mid;
		}
		else
		{
			first = mid + 1;
		}
	}



	return false;

}