#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <set>
using namespace std;

struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	int val;
	TreeNode(int x) {
		val = x;
	}
};

TreeNode* lastNode = new TreeNode(INT_MIN);
TreeNode* firstFaulty = nullptr;
TreeNode* secondFaulty = nullptr;


void inorderTraverse(TreeNode* node) {
	if (!node)
		return;

	inorderTraverse(node->left);
	if (!firstFaulty && lastNode->val > node->val) {
		firstFaulty = lastNode;
	}

	if (firstFaulty && lastNode->val > node->val) {
		secondFaulty = node;
	}

	lastNode = node;
	inorderTraverse(node->right);
}

void recoverTree(TreeNode* root) {

	inorderTraverse(root);
	swap(firstFaulty->val, secondFaulty->val);
}


int balancedString(string s) {

	unordered_map<int, int> count;
	int n = s.length(), res = n, i = 0;
	for (int j = 0; j < n; ++j) {
		count[s[j]]++;
	}
	for (int j = 0; j < n; ++j) {
		count[s[j]]--;
		while (i < n && count['Q'] <= n / 4 && count['W'] <= n / 4 && count['E'] <= n / 4 && count['R'] <= n / 4) {
			res = min(res, j - i + 1);
			count[s[i++]] += 1;
		}
	}
	return res;

}


/*
merge intervals
*/

vector<vector<int>> merge(vector<vector<int>>& intervals) {

	std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& left, const std::vector<int>& right) {return left[0] < right[0]; });

	auto start = intervals.begin();
	auto end = intervals.begin();

	while (++end != intervals.end() && start != intervals.end()) {

		//2 cases - either over laps or doesnt
		// if it does overlap, just set the current
		// start's end to the end's end
		// else, increment start and copy end to start

		if (start->at(1) >= end->at(0)) {
			start->at(1) = std::max(end->at(1), start->at(1));
		}
		else {
			++start;
			*start = *end;
		}

	}


	intervals.erase(start + 1, end);
	return intervals;
}

/*
Given an int n. You can use only 2 operations:

multiply by 2
integer division by 3 (e.g. 10 / 3 = 3)
Find the minimum number of steps required to generate n from 1.

use bfs and keep track of states using a set of nums
*/

int jobScheduling(std::vector<int>& startTimes,
	std::vector<int>& endTimes,
	std::vector<int>& profits) {

	std::map<int, int> startTimesToProfits;
	std::unordered_map<int, std::vector<std::pair<int, int>>> startTimesToVectorOfEndTimesAndProfits;

	for (int i = 0; i < startTimes.size(); ++i) {
		startTimesToProfits[startTimes[i]] = 0;
		startTimesToVectorOfEndTimesAndProfits[startTimes[i]].push_back({
			endTimes[i], profits[i]
			});
	}

	int maxProfit = 0;

	//go backwards through time, and for each start time,
	//go through all the jobs.
	//for each job, find the lower bound in startTimes
	// of the endTime for that job.
	// update maxprofit:
	// if the lower bound was at the end (as in,
	// there are no jobs that start at or after that  ttIme)
	// then maxprofit is 0 + job.second.
	// else it is it->second + job.second

	for (auto it = startTimesToProfits.rbegin(); it != startTimesToProfits.rend(); ++it) {
		
		for (auto job : startTimesToVectorOfEndTimesAndProfits[it->first]) {
			auto lb = startTimesToProfits.lower_bound(job.first); //job.first is end time
			int possibleProfit = job.second;
			
			if (lb != startTimesToProfits.end()) {
				possibleProfit += lb->second;
			}

			maxProfit = std::max(maxProfit, possibleProfit);
		}
		it->second = maxProfit;
	}

	return maxProfit;
}

/*
// Students may decide to take different "tracks" or sequences of courses in the Computer Science curriculum.
//There may be more than one track that includes the same course, but each student follows a single linear track
//from a "root" node to a "leaf" node. In the graph below, their path always moves left to right.

// Write a function that takes a list of (source, destination) pairs, and returns the name of all 
//of the courses that the students could be taking when they are halfway through their track of courses.

// Sample input:
// all_courses = [
//     ["Logic", "COBOL"],
//     ["Data Structures", "Algorithms"],
//     ["Creative Writing", "Data Structures"],
//     ["Algorithms", "COBOL"],
//     ["Intro to Computer Science", "Data Structures"],
//     ["Logic", "Compilers"],
//     ["Data Structures", "Logic"],
//     ["Creative Writing", "System Administration"],
//     ["Databases", "System Administration"],
//     ["Creative Writing", "Databases"],
// ]

// Sample output (in any order):
//      ["Creative Writing", "Databases", "Data Structures"]

// Visual representation:
//                                           ______________
// ____________                              |            |
// |          |        ______________     -->| Algorithms |--\     _____________
// | Intro to |        |            |    /   |____________|   \    |           |
// | C.S.     |---\    | Data       |   /                      >-->| COBOL     |
// |__________|    \   | Structures |--+     ______________   /    |___________|
//                  >->|____________|   \    |            |  /
// ____________    /                     \-->| Logic      |-+      _____________
// |          |   /    ______________        |____________|  \     |           |
// | Creative |  /     |            |                         \--->| Compilers |
// | Writing  |-+----->| Databases  |                              |___________|
// |__________|  \     |____________|-\     _________________________
//                \                    \    |                       |
//                 \--------------------+-->| System Administration |
//                                          |_______________________|

*/
void launch(std::string& s, std::unordered_map<std::string, std::vector<std::string>>& items,
	std::vector<std::string>& temp, std::unordered_set<std::string>& endSet, std::vector<std::vector<std::string>>& paths) {

	if (endSet.count(s)) {
		temp.push_back(s);
		paths.push_back(temp);
		temp.pop_back();
		return;
	}

	temp.push_back(s);

	for (auto& ss : items[s]) {
		launch(ss, items, temp, endSet, paths);
	}

	temp.pop_back();
}


std::unordered_set<std::string> FindSetOfPrereqs(std::vector<std::vector<std::string>>& in)
{
	//start at each end point, find all possible paths back to start point
	//
	std::vector<std::vector<std::string>> paths;
	std::unordered_set<std::string> res;
	std::set<std::string> startPoints;
	std::set<std::string> endPoints;

	std::unordered_map<std::string, std::vector<std::string>> itemToLinks;

	for (int i = 0; i < in.size(); ++i) {
		startPoints.insert(in[i][0]);
		endPoints.insert(in[i][1]);
		itemToLinks[in[i][0]].push_back(in[i][1]);
	}
	
	std::vector<std::string> diffs;
	auto it = std::set_difference(startPoints.begin(), startPoints.end(),
		endPoints.begin(), endPoints.end(), std::back_inserter(diffs));
	std::unordered_set<std::string> startSet(diffs.begin(), diffs.end());

	diffs.clear();
	it = std::set_difference(endPoints.begin(), endPoints.end(),
		startPoints.begin(), startPoints.end(), std::back_inserter(diffs));
	std::unordered_set<std::string> endSet(diffs.begin(), diffs.end());

	for (std::string myStr : startSet) {

		std::vector<std::string> temp;
		std::vector<std::string> finalPath;
		launch(myStr, itemToLinks, temp, endSet, paths);
	}
	

	for (const auto& v : paths) {
		int si = v.size();
		if (si == 0) {
			continue;
		}
		int finalVal = si / 2;
		if (si % 2 == 0) {
			--finalVal;
		}
		res.insert(v[finalVal]);
	}

	return res;
}


int main() {
	/*
	std::vector<int> t{1,2,3,3};
	std::vector<int> tt{3,4,5,6};
	std::vector<int> ttt{50,10,40,70};

	/*
	[1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
	

	jobScheduling(t, tt, ttt);
	*/

	//std::string ss = "QQQQQQQQ";
//	int s = balancedString(ss);

	std::vector<std::vector<std::string>> in = {
		{"Logic", "COBOL"},
			{"Data Structures", "Algorithms"},
			{"Creative Writing", "Data Structures"},
			{"Algorithms", "COBOL"},
			{"Intro to Computer Science", "Data Structures"},
			{"Logic", "Compilers"},
			{"Data Structures", "Logic"},
			{"Creative Writing", "System Administration"},
			{"Databases", "System Administration"},
			{"Creative Writing", "Databases"},
	};

	auto thoue = FindSetOfPrereqs(in);

	return 0;
}
