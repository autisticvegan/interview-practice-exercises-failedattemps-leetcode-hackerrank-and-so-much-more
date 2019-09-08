
/*

apple interiew qs:
product of array except self
maximal square
maximal bordered ssquare
trapping rain water
max points on a line
median of 2 sorted arrays

snap qs:
remove k digits
k spaced array sorting
radar detection
alien dictionary
frog jump
wildcard matching

also, program to remove dups
*/

#include <experimental/filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <set>
using namespace std;
int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {

	if (arr1.empty())
		return -1;

	if (arr1.size() == 1) {
		return 0;
	}

	std::set<int> s;
	for (int i = 0; i < arr2.size(); ++i) {
		s.insert(arr2[i]);
	}

	std::vector<std::vector<int>> dp(arr1.size() + 1, std::vector<int>(arr1.size() + 1, INT_MAX));

	dp[0][0] = INT_MIN;

	for (int i = 1; i < dp.size(); ++i) {
		for (int j = 0; j <= i; ++j) {

			if (arr1[i - 1] > dp[j][i - 1]) {
				dp[j][i] = arr1[i - 1];
			}

			if (j > 0 && s.upper_bound(dp[j - 1][i - 1]) != s.end()) {
				dp[j][i] = std::min(dp[j][i], *s.upper_bound(dp[j - 1][i - 1]));
			}

			if (i == dp.size() - 1 && dp[j][i] != INT_MAX)
				return j;
		}
	}

	return -1;
}

std::string ParseFileName(std::string& s) {
	return s.substr(s.find_last_of('\\') + 1);

}


/*
	Function to take in a list of whitelisted filenames
	and delete all the files that are not in that list
	This is useful because once we have a curated list of files all together,
	we want to remove each of those files from the directories they were originally in.
	Also need to delete empty folders
*/
void RemoveDuplicateFiles(std::unordered_set<std::string>& whiteList, std::experimental::filesystem::path& actualPath) {

	for (std::experimental::filesystem::directory_entry f : std::experimental::filesystem::recursive_directory_iterator(actualPath)) {
		std::string curr_file = f.path().string();

		std::string fn = ParseFileName(curr_file);

		if (whiteList.count(fn) == 0) {
			std::experimental::filesystem::remove(f.path());
		}

	}

}

void DeleteEmptyDirs(std::experimental::filesystem::path& actualPath) {

	for (std::experimental::filesystem::directory_entry f : std::experimental::filesystem::directory_iterator(actualPath)) {
		if (std::experimental::filesystem::is_directory(f.path()) && std::experimental::filesystem::is_empty(f.path())) {
			std::experimental::filesystem::remove(f.path());
		}
	}


}

std::unordered_set<std::string> GetWhiteList(std::experimental::filesystem::path& actualPath) {

	std::unordered_set<std::string> results;

	for (std::experimental::filesystem::directory_entry f : std::experimental::filesystem::recursive_directory_iterator(actualPath)) {
		std::string curr_file = f.path().string();
		std::string fn = ParseFileName(curr_file);
		results.insert(fn);
	}

	return results;

}

int main(int argc, char **argv) {
	/*
	if (argc != 1) {
		std::cout << "Need white list dir, the removal dir will be the current dir";
		return -1;
	}
	*/
	
	//auto whiteListDir = argv[1];
	//auto whiteListDir = "C:\\Users\\stfu1\\Downloads\\tinderData\\images-ssl.gotinder.com";
	//std::experimental::filesystem::path p(whiteListDir);
	//auto s = std::experimental::filesystem::current_path();
	//auto s = std::experimental::filesystem::path ("C:\\Users\\stfu1\\Documents\\Visual Studio 2017\\Projects\\Project55\\deleteStuff");
	//auto uS = GetWhiteList(p);
	//RemoveDuplicateFiles(uS, s);
	//DeleteEmptyDirs(p);


	std::vector<int> t{ 1,5,3,6,7 };
	std::vector<int> tt{ 4,3,1 };
	makeArrayIncreasing(t, tt);

	return 0;
}