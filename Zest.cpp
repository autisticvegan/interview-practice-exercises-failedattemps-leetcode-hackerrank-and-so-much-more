/*
connect all the phrases in O(N)
If we are to remove from the set once we connect,
then first insert all strings into a set, and once
we connect, erase from both the set and the map
(need a 2nd map of string to first word)
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

std::vector<std::string> getFirstAndRemainder(std::string& s) {

	auto j = s.find_first_of(" ");
	std::string first = s.substr(0,j);
	std::string remainder = s.substr(j);
	std::vector<std::string> res(2);
	res[0] = first;
	res[1] = remainder;

	return res;
}

std::vector<std::string> ConnectStrings(std::vector<std::string>& strs) {

	std::vector<std::string> res;
	std::unordered_map<std::string, std::string> firstWordToString;
	
	for (int i = 0; i < strs.size(); ++i) {
		auto g = getFirstAndRemainder(strs[i]);
		firstWordToString[g[0]] = g[1];
	}

	for (int i = 0; i < strs.size(); ++i) {
		bool found = false;
		std::string tempResult = strs[i];
		while (true) {
			std::string ending = tempResult.substr(tempResult.find_last_of(" ") + 1);
			if (firstWordToString.count(ending) == 0) {
				break;
			}
			else {
				found = true;
				tempResult += firstWordToString[ending];
			}
		}
		if (found) {
			res.push_back(tempResult);
		}
	}
	return res;
}

int main(void) {
	std::vector<std::string> testStrings = { "I like bubblegum",
"bubblegum that is pink",
"hi, how are you today",
"today on this fine day",
"day that is sunny" };
	auto v = ConnectStrings(testStrings);
	for (const auto& s : v) {
		std::cout << s << std::endl;
	}
	return 0;
}