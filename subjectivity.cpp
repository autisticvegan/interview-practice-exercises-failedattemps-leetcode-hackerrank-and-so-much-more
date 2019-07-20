
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <set>
#include <queue>
#include <deque>
#include <iostream>

#include <sstream>
#include <istream>

//sudoku 1
//sudoku 2
//implement heap
//other problems from b4

// expanding sliding window approach???
// or back and forth 2 pass approach similar to subarray product less than k
//
int animals(std::vector<int>& animals, std::vector<int>& enemies) {
	
	// 1 -> 1 grouping
	// 1 2 -> 3 groupings
	// 1 2 _ enemies -> 2 groupings
	// 1 2 3 -> 6 g
	// 1 2 3 -> _ enemies -> 3 g
	// 1 2 3 -> common enemy -> 4
	// steps:
	// each step, add 1 (for the whole group)
	// moving forward, check each for enemies
	// if at any point found, break out and go back to index i
	// if none are found, add to set and increment sum
	
	// 0 1 2
	// 2 2 0
	// (1), (2), (3)
	// (1, 2), (3) // 4

	std::unordered_map<int, std::unordered_set<int>> animal2Enemies;

	for (int i = 0; i < enemies.size(); ++i){
		animal2Enemies[animals[i]].insert(enemies[i]);
		animal2Enemies[enemies[i]].insert(animals[i]);
	}

	int sum = 0;// animals.size();
	for (int i = 0; i < animals.size(); ++i) {
		sum++;
		std::unordered_set<int> animalsNow;
		animalsNow.insert(animals[i]);
		for (int j = i + 1; j < animals.size(); ++j)
		{
			
			bool good = true;
			for (const auto& a : animalsNow) {
				if (animal2Enemies[animals[j]].count(animals[i])) {

					good = false;
					break;
				}
			}

			if (!good) {
				break;
			}


			animalsNow.insert(animals[j]);
			++sum;

		}
	}
	return sum;
}


class bid {

public:
	long userId;
	long numShares;
	double price;
	long timestamp;

	bool operator<(const bid& other) {
		if (price != other.price)
		{
			price < other.price;
		}
		else {
			return timestamp < other.timestamp;
		}
	}


};

//obviously this is just a brainstorm
std::unordered_set<int> ipo(std::vector<std::vector<int>>& a) {

	//line by line
	//parse tokens
	std::vector<bid> bids;
	int totalNumShares = 9000;

	std::unordered_set<int> users; // init in beginning
	//then remove as each gets a share

	int num;
	std::cin >> num;

	for (int i = 0; i < num; ++i) {

		std::string s;
	std::cin >> s;
		std::istringstream input(s);
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(input, token, ' ')) {

			tokens.push_back(token);

		}

		bid b;
		b.numShares = std::stoi(tokens[0]); //etc etc

		bids.push_back(b);

	}

	std::sort(bids.begin(), bids.end());

	std::vector < std::vector<bid>> rankedBids;
	std::vector<bid> b;
	b.push_back(bids[0]);
	rankedBids.push_back(b);

	int i;
	for (i = 0; i < bids.size(); ++i) {
		
		std::vector<bid> c;
		c.push_back(bids[i]);
		while (i < bids.size() - 1 && bids[i].price == bids[i+1].price) {
			c.push_back(bids[i+1]);
			++i;
		}

		rankedBids.push_back(c);

	}

	for (auto& b : rankedBids) {
		//if shares == 0, quit
		//steps-take one out
		// minus the shares
		// if multi (as in, size > 1)
		// then do round robin (while shares > 0 && iter < size
		// user id remove

		//obviously do for loop in real life


		if (totalNumShares <= 0) {
			break;
		}

		if (b.size() > 1) {

			int iter = 0;
			while (totalNumShares > 0 && iter < b.size()) {
				
				if (b[iter].numShares <= 0) {
					continue;
				}

				b[iter].numShares--;
				totalNumShares--;
				users.erase(b[iter].userId);
				++iter;
			}

		}
		else {
			totalNumShares -= b[0].numShares;
			users.erase(b[0].userId);
		}

	}


	return users;
}

int smashRocks2(std::vector<int>& a) {
	return 0;
}

int smashRocks(std::vector<int>& a) {
	return 0;
}

std::string compress(std::string& a) {

	std::string result;
	for (int i = 0; i < a.size(); ) {

		int count = 0;
		char c = a[i];

		while (i < a.size() && a[i] == c) {
			++i;
			++count;
		}
		
		result += c + std::to_string(count);

	}

	return result;
}

bool simStrings(std::string& a, std::string& b) {
	
	std::unordered_map<char, int> mapA;
	std::unordered_map<char, int> mapB;

	for (int i = 0; i < a.size(); ++i) {
		mapA[a[i]]++;
	}

	for (int i = 0; i < b.size(); ++i) {
		mapB[b[i]]++;
	}

	for (const auto& t : mapA) {
		
		if (std::abs(mapB[t.first] - t.second) > 3) {
			return false;
		}
	}

	for (const auto& t : mapB) {

		if (std::abs(mapA[t.first] - t.second) > 3) {
			return false;
		}
	}

	return true;
}


int main(void) {

	std::string t = "aaassstood";
	compress(t);
	std::vector<int> tt{ 1,2,3 };
	std::vector<int> ttt{ 3,3,1 };
	animals(tt, ttt);
	char* p = new char;
	*reinterpret_cast<void**>(p) = nullptr;
	std::vector < std::vector<int>> tz{ {1,2,3}, {1,2,4} };
	ipo(tz);
	return 0;
}