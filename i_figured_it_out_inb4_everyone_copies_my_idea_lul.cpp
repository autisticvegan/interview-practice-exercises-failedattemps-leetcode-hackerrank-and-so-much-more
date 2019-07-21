#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution {
public:

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
	std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {

		std::vector<std::vector<int>> graph(numCourses);

		std::vector<int> empty;
		std::vector<int> res;

		for (auto& v : prerequisites) {
			graph[v[1]].push_back(v[0]);
		}

		std::unordered_set<int> visiting;
		std::unordered_set<int> visited;

		//visit all the nodes
		for (int i = 0; i < numCourses; ++i) {
			// if we havent visited it, and we see a cycle
			if (!visited.count(i) && dfs(graph, visited, visiting, res, i))
				return empty;
		}

		std::reverse(res.begin(), res.end());
		return res;

	}

	bool dfs(std::vector<std::vector<int>>& g, std::unordered_set<int>& visited, std::unordered_set<int>& visiting,
		std::vector<int>& res, int start) {

		if (visiting.count(start)) {
			return true;
		}

		if (visited.count(start)) {
			return false;
		}

		visiting.insert(start);
		//insert to visiting, then check each edge from this one.  if
		// we ever get true from dfsing, then that means we had a cycle

		for (const auto& i : g[start]) {
			if (dfs(g, visited, visiting, res, i)) {
				return true;
			}
		}

		visiting.erase(start);
		//now erase from visiting

		visited.insert(start);
		res.push_back(start);
		return false;
	}
};


// hackerrank is harder than leetcode...hmmmm lets try to figure out how to break leetcode with hackerranks test cases

int numSubArraysWithMaxProductK(std::vector<int> arr, int k) {
	// OMG I AM SUCH A NOOB LMAO I WAS THINKING IT WAS <= NOT < LOOOOL
}

// rotors problem
// n to m for each one, count how many coprime in range n + 1 to m to n
// can they be coprime to each other? 
// compile time calculate all coprimes to a given number (up to range given)
// total then is
// coprimes for that number ^ rotor count
// 
// 2 3 3
// 3 4 4
// 3 2 2
// 3 2 4
// 3 4 2
// 4 3 3
// remember to mod 100007 or w hatever.
// calculate huge vector of vectors, with each index corresponding to a vector of all its coprimes (up to some huge number)
// then at runtime we need to chop (find the spot with our min range) and count the remaining
// 


int gcd(int a, int b)
{
	int c = a % b;
	while (c != 0)
	{
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}


bool isCoprime(int a, int b) {
	return gcd(a, b) == 1;
}




void printHuge(int max) {
	
	std::cout << "std::vector<std::vector<int>> huge = {\n";

	for (int i = 2; i <= max; ++i) {
		


		std::vector<int> out;

		for (int j = 2; j <= max; ++j) {
			if (isCoprime(i, j)) {
				out.push_back(j);
			}
		}

		std::cout << "{";


		if (out.size() >= 1) {
			for (int k = 0; k < out.size() - 1; ++k) {
				std::cout << out[k] << ",";
			}

			if (out.size() > 0)
				std::cout << out[out.size() - 1];
		}

		
		std::cout << "},\n";
	}

	std::cout << "};";
}


int rotors(int min, int max, int rotorCount) {
	
	if (rotorCount == 1)
		return std::abs(max - min);

	int sum = 0;

	for (int i = min; i <= max; ++i) {
		
		int j;
		for (j = 0; j < huge[i-2].size(); ++j) {

			if (huge[i-2][j] >= min) {
				break;
			}

		}

		int k;
		for (k = huge[i-2].size() - 1; k >= 0; --k) {
			if (huge[i-2][k] <= max) {
				break;
			}
		}

		int trueSize = k - j + 1;
		unsigned long long test = std::pow(trueSize, rotorCount - 1);
		test %= 10000007;
		sum += test;

	}

	sum %= 10000007;
	return sum;
}


int scheduleCourse(std::vector<std::vector<int>>& courses) {

	//sort by d (2nd number), then use priority queue 
	// which has the t numbers.  for each course,
	// push in the t, and add it to the sum
	// if the sum is too big, then pop off the queue
	// and minus off the sum.
	// then return size of queue
	std::sort(courses.begin(), courses.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
		return a[1] < b[1];
		});
	std::priority_queue<int> q;
	int sum = 0;
	for (const auto& c : courses) {
		int t = c[0];
		int d = c[1];

		q.push(t);
		sum += t;

		if (sum > d) {

			sum -= q.top();
			q.pop();
		}
	}

	return q.size();

}


// shoutouts to my chinese buddy boyos

int main(void) {
	rotors(2, 4, 3);
	printHuge(20);
	return 0;

}
