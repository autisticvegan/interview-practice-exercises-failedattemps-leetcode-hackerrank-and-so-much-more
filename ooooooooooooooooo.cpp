#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <stack>
#include <deque>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>


std::string addString(std::string& s, int& index) {

	std::string result;
	// termination condition - reaching final bracket or end of string
	while (index < s.length() && s[index] != ']') {
		// if its not a digit, just add and keep going
		if (!isdigit(s[index])) {
			result += s[index];
			++index;
		}
		else {
			int iter = index;
			// if it is, get the number size (could be more than one digit)
			while (isdigit(s[index])) {
				++index;
			}
			int iterations = std::stoi(s.substr(iter, index - iter));

			// walk past the front bracket
			++index;

			// get the string we are going to add
			std::string substring = addString(s, index);
			// walk past the end bracket
			++index;

			// multiply the string we got the number of times we need it
			for (int i = 0; i < iterations; ++i) {
				result += substring;
			}
		}
	}
	return result;
}

std::string decodeString(std::string s) {
	int i = 0;
	return addString(s, i);

}
// bad problem:
class TopVotedCandidate {
public:
	TopVotedCandidate(vector<int> persons, vector<int> times) {
		int max_count = 0, candidate = 0, len = persons.size();
		int count[len + 1];
		memset(count, 0, sizeof count);
		// candidates.first is the time[i], candidates.second is the top voted candidate at time[i].
		candidates = vector<pair<int, int>>(len);
		for (int i = 0; i < len; i++) {
			count[persons[i]]++;
			if (count[persons[i]] >= max_count) {
				max_count = count[persons[i]];
				candidate = persons[i];
			}
			candidates[i].first = times[i];
			candidates[i].second = candidate;
		}
	}

	int q(int t) {
		int lo = 0, hi = candidates.size();
		// Find the largest time which <= t, this is equivalent with find the smallest time which > t, then minus 1;
		while (lo < hi) {
			int m = (lo + hi) / 2;
			if (candidates[m].first <= t) {
				lo = m + 1;
			}
			else {
				hi = m;
			}
		}
		return candidates[lo - 1].second;
	}

private:
	vector<pair<int, int>> candidates;
};


// below, someone elses solution for tle
using namespace std;
class MyHashMap{
	vector<list<pair<int,int>>> m_data;
	size_t m_size = 10000;
public:
	/** Initialize your data structure here. */
	MyHashMap() {
		m_data.resize(m_size);
	}

	/** value will always be non-negative. */
	void put(int key, int value) {
		auto &list = m_data[key % m_size];
		for (auto & val : list) {
			if (val.first == key) {
				val.second = value;
				return;
			}
		}
		list.emplace_back(key, value);
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		const auto &list = m_data[key % m_size];
		if (list.empty()) {
			return -1;
		}
		for (const auto & val : list) {
			if (val.first == key) {
				return val.second;
			}
		}
		return -1;
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		auto &list = m_data[key % m_size];
		list.remove_if([key](auto n) { return n.first == key; });
	}
};

// mine is TLE because of the string stuff...
class MyHashMap {
public:

	// tombstone = -99
	// my style: linear probing, tombstones
	std::vector<std::pair<std::string, std::string>> data;
	/** Initialize your data structure here. */
	MyHashMap() {
		data.resize(1000);
	}

	void grow() {
		data.resize((data.size() + 1) * 3);
	}

	/** value will always be non-negative. */
	void put(int key, int value) {

		std::string k = std::to_string(key);
		size_t spot = hashA(k);

		if (spot >= data.size()) {
			grow();
			data[spot].first = k;
			data[spot].second = std::to_string(value);
			return;
		}

		while (spot < data.size() && data[spot].first != ""
			&& data[spot].first != k) {
			++spot;
		}

		if (spot == data.size()) {
			grow();
		}

		data[spot].first = k;
		data[spot].second = std::to_string(value);
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		std::string k = std::to_string(key);
		size_t spot = hashA(k);

		if (spot >= data.size()) {
			return -1;
		}

		while (spot < data.size() && data[spot].first != ""
			&& data[spot].first != k) {
			++spot;
		}

		if (spot == data.size() || data[spot].first == "") {
			return -1;
		}

		return std::stoi(data[spot].second);
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		std::string k = std::to_string(key);
		size_t spot = hashA(k);

		if (spot >= data.size()) {
			return;
		}

		while (spot < data.size() && data[spot].first != ""
			&& data[spot].first != k) {
			++spot;
		}

		if (spot == data.size() || data[spot].first == "") {
			return;
		}

		data[spot].first = "TOMBSTONE";
	}


	size_t hashA(std::string& g) {
		return std::hash<std::string>{}(g) % 69;
	}
};

int main(void) {
	MyHashMap m;
	m.put(1, 1);
	m.put(2, 2);
	m.get(1);
	m.get(3);
	m.put(2, 1);
	m.get(2);
	m.remove(2);
	m.get(2);
	return 0;
}