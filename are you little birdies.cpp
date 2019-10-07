#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <algorithm>

//idea: At compile time / before running,
//prepoulate, we can get the distance
//and thus the number of interesting points
//in O(1)

class InterestingTimeChecker {
public:
	std::vector<std::string> times;

	InterestingTimeChecker() {
		Populate();
	}

	bool isInteresting(std::string& s) {
		std::unordered_set<int> aSet;

		for (int i = 0; i < s.size(); ++i) {
			if (s[i] != ':')
				aSet.insert(s[i]);
		}

		return aSet.size() <= 2;
	}

	void Populate() {

		for (int i = 0; i < 24; ++i) {
			for (int j = 0; j < 60; ++j) {
				for (int k = 0; k < 60; ++k) {

					std::string iPart, jPart, kPart;
					if (i < 10)
						iPart = "0";

					if (j < 10)
						jPart = "0";

					if (k < 10) {
						kPart = "0";
					}

					iPart += std::to_string(i);
					jPart += std::to_string(j);
					kPart += std::to_string(k);

					std::string temp = iPart + ":" + jPart + ":" + kPart;

					if (isInteresting(temp)) {
						times.push_back(temp);
					}
				}
			}
		}
	}

	//returns true if start is before end,
	//else returns false
	bool compTime(std::string& s, std::string& e) {

		int Shours = std::stoi(s.substr(0, 2));
		int Ehours = std::stoi(e.substr(0, 2));

		int sMinutes = std::stoi(s.substr(3, 2));
		int eMinutes = std::stoi(e.substr(3, 2));

		int sSecs = std::stoi(s.substr(7, 2));
		int eSecs = std::stoi(e.substr(7, 2));

		if (Shours == Ehours) {

			if (sMinutes == eMinutes) {
				return sSecs < eSecs;
			}
			return sMinutes < eMinutes;
		}

		return Shours < Ehours;
	}

	int numberOfInterestingPoints(std::string& startTime,
		std::string& endTime) {

		if (startTime > endTime) {
			//end time is before start time, wrap around
			auto b = std::upper_bound(times.begin(), times.end(), startTime);
			auto e = std::lower_bound(times.begin(), times.end(), endTime);

			auto first = std::distance(b, times.end());
			auto last = std::distance(times.begin(), e);
			return first + last;
		}
		auto b = std::lower_bound(times.begin(), times.end(), startTime);
		auto e = std::upper_bound(times.begin(), times.end(), endTime);

		return std::distance(b, e);
	}
};

int main(void) {

	InterestingTimeChecker i;
	std::string s = "23:00:00";
	std::string e = "00:00:00";
	if (s != e)
		std::cout << i.numberOfInterestingPoints(s, e);
	else
		std::cout << 0;
	return 0;
}

