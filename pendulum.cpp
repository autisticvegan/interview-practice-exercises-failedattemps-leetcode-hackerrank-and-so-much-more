#include <string>
#include <iostream>
#include <vector>




/*
1. The Chosen One
find num that cant be divided by
divisor but all the other nums can be
*/


long long gcd(long long a, long long b) {
	while (a && b) {
		if (a >= b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

long long getChosenOne(std::vector<int>& a) {

	int n = a.size();
	int hugeNum = 1000000;
	std::vector<std::vector<long long>> d(2, std::vector<long long>(hugeNum));

	for (int q = 0; q < 2; ++q) {
		for (int i = 0; i < n; ++i) {
			d[q][i + 1] = gcd(d[q][i], a[i]);
		}
		std::reverse(a.begin(), a.end());
	}

	for (int i = 0; i < n; ++i) {
		long long x = gcd(d[0][i], d[1][n - i - 1]);

		if (a[i] % x != 0) {
			return x;
		}
	}
}


/*
2. Consecutive numbers sum
find how many ways to consecutively sum to a given number.
Better version
*/
int ConsSum(int N) {
	int res = 1, count;
	while (N % 2 == 0) N /= 2;
	for (int i = 3; i * i <= N; res *= count + 1, i += 2)
		for (count = 0; N % i == 0; N /= i, count++);
	return N == 1 ? res : res * 2;
}

/*
3. Number subarrays m odd numbers
*/
int countSubarrays(std::vector<int>& a, int m) {	
	int count = 0;
	int n = a.size();
	int odd = 0;
	std::vector<int> prefix(n);
	for (int i = 0; i < n; ++i) {

		prefix[odd]++;

		if (a[i] & 1) {
			++odd;
		}

		if (odd >= m) {
			count += prefix[odd - m];
		}
	}
	return count;
}



/*
5. Most Frequest substring

Construct suffix tree
Follow the path for q starting from the root.
The number of leaves under the node you end up in is the
number of occurrences of q.

https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/suffixtrees.pdf
*/



/*
6. Unique Paths III
Go from a to b, hitting every spot on the way, cant go through -1s,
count number of paths
*/

bool validCell(int x, int y, std::vector<std::vector<int>>& g) {
	return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size() || g[x][y] == -1);
}

std::vector<int> xDirs{ 0,0,1,-1 };
std::vector<int> yDirs{ 1,-1,0,0 };

int dfs(int x, int y, std::vector<std::vector<int>>& g, int currSteps, int totalSteps) {

	if (!validCell(x, y, g)) {
		return 0;
	}

	if (g[x][y] == 2) {
		if (currSteps == totalSteps) {
			return 1;
		}
		return 0;
	}

	g[x][y] = -1;

	int total = 0;

	for (int i = 0; i < 4; ++i) {
		int newX = xDirs[i] + x;
		int newY = yDirs[i] + y;
		total += dfs(newX, newY, g, currSteps + 1, totalSteps);
	}

	g[x][y] = 0;
	return total;
}

int UniquePaths3(std::vector<std::vector<int>>& v) {

	int origX, origY;
	int tSteps = 0;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {

			if (v[i][j] == 1) {
				origX = i;
				origY = j;
			}

			if (v[i][j] != -1) {
				++tSteps;
			}

		}
	}

	return dfs(origX, origY, v, 1, tSteps);
}

/*
Number 7: Longest Palindromic Substring

alg: start left and right at "start".
get rid of the right side duplicate letters
then start = right;

now figure out palindrome (minus left and plus right)

if we found a new max len, update it, and update maxleft
with left

*/

std::string longestPalindromicSubstring(std::string s) {

	int max_left = 0;
	int max_len = 1;
	int n = s.size();
	int left, right;
	for (int start = 0; start < n && n - start > max_len / 2;) {

		left = start;
		right = start;

		while (right < n - 1 && s[right] == s[right + 1]) {
			++right;
		}

		start = right + 1;

		while (left > 0 && right < n && s[left - 1] == s[right + 1]) {
			--left;
			++right;
		}

		if (right - left + 1 > max_len) {
			max_left = left;
			max_len = right - left + 1;
		}

	}

	return s.substr(max_left, max_len);
}

int main(void) {


//	std::vector<int> v{ 3,6,18,12 };
//	getChosenOne(v);
	std::vector<int> v{ 2,2,5,6,9,2,11 };
	countSubarrays(v, 2);

	return 0;
}