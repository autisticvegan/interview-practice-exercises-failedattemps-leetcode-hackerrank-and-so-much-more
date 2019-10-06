#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

using namespace std;
int find(vector<int>& ds, int i) {
	return ds[i] < 0 ? i : ds[i] = find(ds, ds[i]);
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	//see things as a graph, with transitions between words
	//go double sided since it has a tree like structure with letters
	//bfs
	//3 unordered sets - dictionary, head, and tail, also pointers to head and tail
	//sanity check: check endword is in dict
	//ladder count starts at 2, return 0 as error
	//big while loop, 3 for loops.  Head pointer is smaller set, etc
	// for each item in head:
	// for each character in that item:
	// save the char temporarily
	// for letters 0 - 26 (check all possibilities)
	// word[i] = 'a' + letter
	//if(that word exists in tail) then we found a match so return
	//if that word is in our dict, insert to temp and erase from dict
	// exit for loop.  replace back the char we used (word[i] = t)
	// exit other 2 for loops - increment ladder and swap head with temp
	// (we are using swap for constant time op)

	std::unordered_set<std::string> dictionary(wordList.begin(), wordList.end());
	std::unordered_set<std::string> head, tail, *pHead, *pTail;

	if (dictionary.count(endWord) == 0) {
		return 0;
	}

	head.insert(beginWord);
	tail.insert(endWord);
	int ladderLength = 2;
	while (!head.empty() && !tail.empty()) {

		if (head.size() < tail.size()) {
			pHead = &head;
			pTail = &tail;
		}
		else {
			pHead = &tail;
			pTail = &head;
		}

		std::unordered_set<std::string> tempSet;
		for (auto itr = pHead->begin(); itr != pHead->end(); ++itr) {
			std::string str = *itr;
			for (int i = 0; i < str.size(); ++i) {
				char temp = str[i];

				for (int j = 0; j < 26; ++j) {
					str[i] = 'a' + j;

					if (pTail->count(str)) {
						return ladderLength;
					}

					if (dictionary.count(str)) {
						tempSet.insert(str);
						dictionary.erase(str);
					}
				}


				str[i] = temp;
			}
		}

		++ladderLength;
		pHead->swap(tempSet);

	}


	return 0;
}

std::string SmallestStringWithSwaps(std::string& s, std::vector<std::vector<int>>& pairs)
{
	vector<int> ds(s.size(), -1);
	vector<vector<int>> m(s.size());
	for (auto& p : pairs) {
		auto i = find(ds, p[0]), j = find(ds, p[1]);
		if (i != j) {
			if (-ds[i] < -ds[j]) swap(i, j);
			ds[i] += ds[j];
			ds[j] = i;
		}
	}
	for (auto i = 0; i < s.size(); ++i) m[find(ds, i)].push_back(i);
	for (auto ids : m) {
		string ss = "";
		for (auto id : ids) ss += s[id];
		sort(begin(ss), end(ss));
		for (auto i = 0; i < ids.size(); ++i) s[ids[i]] = ss[i];
	}


	return s;
}


class Building {
public:
	int height = 0;
	bool isStart = false;
	int x = 0;

	bool operator<(const Building& b) {
		if (b.x != x) {
			return x < b.x;
		}
		else {
			if (b.isStart && isStart) {
				//higher height comes first
				return height > b.height;
			}
			else if (!b.isStart && !isStart) {
				//lower height comes first
				return b.height < height;
			}
			else {
				//the start one comes before the end
				if (isStart) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
};

vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
	typedef pair<int, int> Event;
	// events,  x,   h
	vector<Event> es;
	hs_.clear();

	for (const auto& b : buildings) {
		es.emplace_back(b[0], b[2]);
		es.emplace_back(b[1], -b[2]);
	}

	// Sort events by x
	sort(es.begin(), es.end(), [](const Event& e1, const Event& e2) {
		if (e1.first == e2.first) return e1.second > e2.second;
		return e1.first < e2.first;
		});

	vector<vector<int>> ans;

	// Process all the events
	for (const auto& e : es) {
		int x = e.first;
		bool entering = e.second > 0;
		int h = abs(e.second);

		if (entering) {
			if (h > this->maxHeight())
				ans.push_back({ x, h });
			hs_.insert(h);
		}
		else {
			hs_.erase(hs_.equal_range(h).first);
			if (h > this->maxHeight())
				ans.push_back({ x, this->maxHeight() });
		}
	}

	return ans;
}
private:
	int maxHeight() const {
		if (hs_.empty()) return 0;
		return *hs_.rbegin();
	}
	multiset<int> hs_;
//damnit
int maximalSquare(vector<vector<char>>& matrix) {


	if (matrix.empty() || matrix[0].empty())
		return 0;

	int res = 0;

	std::vector<std::vector<int>> dp(matrix.size() + 1,
		std::vector<int>(matrix[0].size() + 1));

	for (int i = 1; i <= matrix.size(); ++i) {
		for (int j = 1; j <= matrix[0].size(); ++j) {
			if (matrix[i - 1][j - 1] == '1') {
				dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j - 1]), dp[i - 1][j]) + 1;
				res = std::max(res, dp[i][j]);
			}
		}
	}

	//sanity check: check for empty
	//dp is min of 3 prev
	// end is res * res
	// if we see a 1 then do formula
	// remember to start form 1 and go to <=
	return res * res;
}

int main(void) {

	/*
	std::string s = "cba";
	std::vector<std::vector<int>> swaps{ {0,1}, {1,2} };
	*/
	/*
	std::string s = "zdcyxbwa";
	std::vector<std::vector<int>> swaps{{0, 3}, {4, 6}, {3, 4}, {1, 7}, {2, 5}, {5, 7}};

	auto answer = SmallestStringWithSwaps(s, swaps);
	[[0,2,3],[2,5,3]]
	*/
	std::vector<std::vector<int>> b{ {0, 2, 3}, {2, 5, 3} };
	auto bb = getSkyline(b);
	return 0;
}