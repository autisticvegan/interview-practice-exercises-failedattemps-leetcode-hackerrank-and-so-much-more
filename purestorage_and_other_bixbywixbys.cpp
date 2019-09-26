#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <random>

//num islands
//shortest ways
//maximal rectangle
//queries problem

//terrible terrible test code lol

//
class TreeNode {
	
public:
	int value = 0;
	TreeNode* right = nullptr;
	TreeNode* left = nullptr;
	TreeNode* parent = nullptr;
};

bool searchTree(TreeNode* r, int val) {
	
	if (!r)
		return false;
	
	std::queue<TreeNode*> tt;
	tt.push(r);

	while (!tt.empty()) {

		int iters = tt.size();
		for (int i = 0; i < iters; ++i) {
			auto t = tt.front();
			tt.pop();

			if (t->value == val) {
				return true;
			}

			if (t->left) {
				tt.push(t->left);
			}

			if (t->right) {
				tt.push(t->right);
			}

		}

	}

	return false;
}

//set up tree of certain size (as in 6)
//function which sets a random one to null
//get a random number
//traverse tree and see if we see that number
//do above 10k times.
void testTrees() {

	int iters = 1;
	int count = 4;
	int level = 0;
	TreeNode* root = new TreeNode();
	root->value = 0;

	int orig = 0;

	std::queue<TreeNode*> q;
	q.push(root);
	while (level < count) {

		int iters = q.size();
		for (int i = 0; i < iters; ++i) {

			++orig;
			TreeNode* p = q.front();
			q.pop();
			p->left = new TreeNode();
			p->left->value = orig;
			p->left->parent = p;
			++orig;
			p->right = new TreeNode();
			p->right->value = orig;
			p->right->parent = p;

			q.push(p->left);
			q.push(p->right);
		}

		++level;
	}
	
	std::vector<TreeNode*> v;
	std::queue<TreeNode*> tt;

	tt.push(root);

	while (!tt.empty()) {

		int iters = tt.size();
		for (int i = 0; i < iters; ++i) {
			auto t = tt.front();
			tt.pop();
			v.push_back(t);

			if (t->left) {
				tt.push(t->left);
			}

			if (t->right) {
				tt.push(t->right);
			}

		}

	}

	//pick a random node, set it to null
	//pick a random value, traverse tree and see if we find it
	//if we dont, add to bad case
	//if we do, add to good case
	//reset node back to what it originally was;

	double foundCount = 0;
	int limit = 1000000;
	for (int i = 0; i < limit; ++i) {
		int rand = std::rand() % v.size();
		auto origTN = v[rand];
		int value = origTN->value;
		auto leftO = origTN->left;
		auto rightO = origTN->right;

		origTN->value = 999;
		origTN->left = nullptr;
		origTN->right = nullptr;

		int randSearch = std::rand() % v.size();
		//search it
		bool found = searchTree(root, randSearch);

		if (found)
			++foundCount;

		origTN->value = value;
		origTN->left = leftO;
		origTN->right = rightO;
	}
	
	std::cout << "found percentage is " << (foundCount / limit) * 100 << " %" << std::endl;
	
	// SO THIS MEANS THE ANSWER IS ABOUT LOG(X+2) OK?

}



// Complete the compute_number_score function below.
int compute_number_score(int number) {

	//split into digits

	std::vector<int> digits;
	int digit = 0;
	int total = 0;
	int finalAns = 0;

	while (number > 0) {
		digit = number % 10;
		digits.push_back(digit);

		//used for seeing if divisible by 3
		total += digit;

		if (digit == 7) {
			finalAns += 1;
		}

		number /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	if (total % 3 == 0) {
		finalAns += 2;
	}

	for (int i = 0; i < digits.size() - 1; ++i) {
		if (digits[i] == 5 && digits[i + 1] == 5) {
			finalAns += 3;
		}
	}
	/*
	problem description is wrong
	for (int i = 0; i < digits.size() - 1; ++i) {
		if (digits[i] == 5 && digits[i + 1] == 5) {
			i += 2;
			while (i < digits.size() && digits[i] == 5) {
				finalAns += 3;
				++i;
			}

		}
	}
	*/
	int current = 1;
	int currNum = digits[0];
	for (int i = 1; i < digits.size(); ++i) {
		if (digits[i] == currNum - 1) {
			++current;
		}
		else {

			finalAns += current * current;
			current = 1;
		}
		currNum = digits[i];
	}
	finalAns += current * current;

	for (const auto& i : digits) {
		if (i % 2 == 0) {
			finalAns += 4;
		}
	}



	return finalAns;
}

int main(void) {
	//auto i = compute_number_score(732155568);
	testTrees();
	return 0;
}

/*

std::vector<int> queries(std::vector<int> a, std::vector<int> b, std::vector<std::vector<int>> qs) {

	//idea:
	//compute count of all a
	//compute count of all b


	//if we need to update, reupdate b map.  i.e. --, if it reaches 0, then erase it

	//since a is shorter than b, always use a
	//check all a for count, if found, multiply
	

}

https://leetcode.com/discuss/interview-question/217510/google-phone-screen-shortest-way-to-form-string

//The correct answer is using a suffix tree for B, then it can be done in O(n + m) time complexity.If you see that the problem mentions substrings, this is a suffix tree solution.
int maximalRect(std::vector<std::vector<char>>& m) {

	int cLen = m[0].size();
	int rLen = m.size();
	std::vector<int> height(cLen + 1);
	height[cLen] = 0;
	int max = 0;

	//go row by row
	for (int row / 0; row < rLen; ++row) {
		std::stack<int> s;

		for(int i = 0; i < cLen + 1; ++i) {

			if(i < cLen) {
				if(m[row][i] == '1') {
					height[i]++;
				} else {
					height[i] = 0;
				}
			}

			// if we have an empty stack or the last height is <= current height
			if(s.empty() || height[s.top()] <= height[i]) {
				s.push(i);
			} else {
				while(!s.empty() && height[i] < height[s.top()] <= height[i]) {
					
					int top = s.top();
					s.pop();
					int area = height[top] * (s.empty() ? i : (i - s.top() - 1));
					max = std::max(area, max);

				}
				s.push(i);
			}


		}

		
	}
	return max;
}


bool validCell(std::vector<std::vector<char>>& g, int x, int y) {
	return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size());
}

void markIslands(std::vector<std::vector<char>>& g, int x, int y) {

	std::stack<std::pair<int, int>> s;
	s.push({ x,y });

	std::vector<int> xDir{ 0,1,-1,0 };
	std::vector<int> yDir{ 1,0,0,-1 };


	while (!s.empty()) {

		auto p = s.top();
		s.pop();

		for (int i = 0; i < 4; ++i) {
			int newX = p.first + xDir[i];
			int newY = p.second + yDir[i];
			if (!validCell(g, newX, newY))
				continue;

			if (g[newX][newY] == '1') {
				s.push({ newX, newY });
				g[newX][newY] = 0;
			}
		}

	}

}

int numIslands(std::vector<std::vector<char>>& g) {

	int count = 0;

	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[0].size(); ++j) {
			if (g[i][j] == '1') {
				++count;
				markIslands(g, i, j);
			}
		}
	}

	return count;
}


/*
coolFeature
(
	0:00 : 07
)
Codewriting

You are developing a new programming language.You believe that ordinary dictionaries are boring, so you've decided to add a cool feature to make your language unique!

You want the cool feature to be able to perform two types of queries.With two arrays, a and b, the two types of queries are as follows :

If the query is of the form[0, i, x], then b[i] should be assigned the value of x.
If the query is of the form[1, x], then find the total number of pairs of indices i and j such that a[i] + b[j] = x.
You will be given the arrays of integers a and b, as well as query, an array of queries in either of the forms described above.Your task is to implement this cool feature, perform the given queries and return an array of the results of the queries of the second type.

Example

For a = [1, 2, 3], b = [3, 4], and query = [[1, 5], [0, 0, 1], [1, 5]], the output should be coolFeature(a, b, query) = [2, 1].

The arrays look like this before the first query :
a = [1, 2, 3] and b = [3, 4]
There are two ways to form a sum of 5 using an element from each array : 5 = 1 + 4 and 5 = 2 + 3. So the result is 2.

The second query re - assigns the value of b[0] to 1, so the arrays look like this before the third query :
a = [1, 2, 3] and b = [1, 4]
There's now only one way to form a sum of 5 using an element from each array: 5 = 1 + 4. So the result is 1.

Since the two queries of type 1 gave results of 2 and 1, the answer is[2, 1].

For a = [1, 2, 2], b = [2, 3], and query = [[1, 4], [0, 0, 3], [1, 5]], the output should be coolFeature(a, b, query) = [3, 4].

The arrays look like this before the first query :
a = [1, 2, 2] and b = [2, 3]
There are three ways to form a sum of 4 using an element from each array : 4 = 1 + 3 = a[0] + b[1], 4 = 2 + 2 = a[1] + b[0], and 4 = 2 + 2 = a[2] + b[0].So the result is 2.

The second query re - assigns the value of b[0] to 3, so the arrays look like this before the third query :
a = [1, 2, 2] and b = [3, 3]
There are now 4 ways to form a sum of 5 using an element from each array : 5 = 2 + 3 = a[1] + b[0], 5 = 2 + 3 = a[1] + b[1], 5 = 2 + 3 = a[2] + b[0], and 5 = 2 + 3 = a[2] + b[1].So the result is 4.

Input / Output

[execution time limit] 0.5 seconds(cpp)

[input] array.integer a

An array of integers.

Guaranteed constraints :
1 ? a.length ? 103,
0 ? a[i] ? 109.

[input] array.integer b

An array of integers.

Guaranteed constraints :
1 ? b.length ? 5 · 104,
0 ? b[i] ? 109.

[input] array.array.integer query

An array of queries, where query[i][0] represents the type of query, and the other elements represent the parameters of the query(i and x for type 0, and just x for type 1).

For the first type of query, it is guaranteed that 0 ? query[i][1] < b.length and 0 ? query[i][2] ? 109.
	For the second type of query, it is guaranteed that 0 ? query[i][1] ? 2 · 109

	Guaranteed constraints :
1 ? query.length ? 103.

[output] array.integer

The outputs of the queries of the second type, in the order they are given in the input.
[C++] Syntax Tips

// Prints help message to the console
// Returns a string
std::string helloWorld(std::string name) {
	std::cout << "This prints to the console when you Run Tests" << std::endl;
	return "Hello, " + name;
}

0
1
main.cpp

C++
Dark
Sublime
std::vector<int> coolFeature(std::vector<int> a, std::vector<int> b, std::vector<std::vector<int>> query) {


	std::unordered_map<int, int> num2Count;

	for (int i = 0; i < a.size(); ++i) {
		num2Count[a[i]]++;
	}

	std::unordered_map<int, int> bnum2Count;
	for (int i = 0; i < b.size(); ++i) {
		bnum2Count[b[i]]++;
	}

	std::vector<int> res;
	for (const auto& v : query) {
		if (v.size() == 3) {

			int orig = b[]
				bnum2Count[b[v[1]]]--;
			bnum2Count[

		}
		else {


			int target = v[1];
			int total = 0;
			if (changed) {
				total = 0;
				for (int i = 0; i < b.size(); ++i) {
					if (num2Count.count(target - b[i])) {
						total += num2Count[target - b[i]];
					}
				}
				origTotal = total;
			}
			else {
				total = origTotal;
			}

			res.push_back(total);
		}
	}

	return res;
}

TESTS
CUSTOM TESTS
8 / 18 sample tests passed.
Test 1
Input:
a: [1, 2, 3]
	b : [3, 4]
	query : [[1, 5],
	[0, 0, 1],
	[1, 5]]
	Output :
	[1442704160, 1]
   Expected Output :
   [2, 1]
   Console Output :
   Empty
	   Test 2
	   Test 3
	   Test 4
	   Test 5
	   Test 6
	   Test 7
	   Test 8
	   Test 9
	   Test 10
	   Test 11
	   Test 12
	   Test 13
	   Test 14
	   Test 15
	   Test 16
	   Test 17
	   Test 18
	   Test 19
	   Test 20
	   Test 21
	   Test 22
	   Test 23
	   Test 24
	   Test 25
	   Test 26
	   Test 27
	   Test 28
	   Test 29
	   Test 30
	   Test 31
	   Test 32
	   Test 33
	   Test 34
	   Test 35
	   Test 36
	   Formatting
	   Editor Mode
	   Sublime
	   Theme
	   Dark
	   Tab Size
	   Auto
	   Font Size
	   14px
	   Code Completion
	   Auto - brackets
	   Hotkeys
	   CTRL + Enter
	   Submit
	   CTRL + R
	   Run
	   CTRL + S
	   Save
	   266 / 300

*/

//print matrix different ways

/*

std::vector<int> mostFrequentDigits(std::vector<int> a) {

	std::map<int, int> digit2Count;

	for (int i = 0; i < a.size(); ++i) {

		int orig = a[i];
		while (orig > 0) {
			int v = orig % 10;
			digit2Count[v]++;
			orig /= 10;
		}

	}

	int max = INT_MIN;
	for (const auto& p : digit2Count) {
		max = std::max(max, p.second);
	}

	std::vector<int> res;

	for (const auto& p : digit2Count) {
		if (p.second == max) {
			res.push_back(p.first);
		}
	}

	return res;
}

int main(void) {

	std::vector<int> tt{ 25, 2, 3, 57, 38, 41 };
	auto t = mostFrequentDigits(tt);

	return 0;
}

*/
/*
//#include <bits/stdc++.h>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long listMax(int n, vector<vector<int>> operations)
{
	// Please write your code here.

	std::vector<int> sums(n + 1);

	for (const auto& o : operations) {

		int first = o[0] - 1;
		int second = o[1] - 1;
		sums[first] += o[2];
		sums[second + 1] -= o[2];
	}

	int sum = 0;
	int res = INT_MIN;
	for (int i = 0; i < n; ++i) {
		sum += sums[i];
		res = std::max(res, sum);
	}

	return res;
}
string ltrim(const string &str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);

	return s;
}
string rtrim(const string &str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);

	return s;
}
vector<string> split(const string &str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}

int main()
{
	string n_temp;
	getline(cin, n_temp);

	int n = stoi(ltrim(rtrim(n_temp)));

	string operations_rows_temp;
	getline(cin, operations_rows_temp);

	int operations_rows = stoi(ltrim(rtrim(operations_rows_temp)));

	string operations_columns_temp;
	getline(cin, operations_columns_temp);

	int operations_columns = stoi(ltrim(rtrim(operations_columns_temp)));

	vector<vector<int>> operations(operations_rows);

	for (int i = 0; i < operations_rows; i++) {
		operations[i].resize(operations_columns);

		string operations_row_temp_temp;
		getline(cin, operations_row_temp_temp);

		vector<string> operations_row_temp = split(rtrim(operations_row_temp_temp));

		for (int j = 0; j < operations_columns; j++) {
			int operations_row_item = stoi(operations_row_temp[j]);

			operations[i][j] = operations_row_item;
		}
	}
	cout << listMax(n, operations) << endl;
	return 0;
}
*/