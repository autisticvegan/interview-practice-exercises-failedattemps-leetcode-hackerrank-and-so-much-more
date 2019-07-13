#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>




bool isInterleave(std::string s1, std::string s2, std::string s3) {

	if (s1.empty()) {
		return (s2.empty() && s3.empty() || s2 == s3);
	}


	if (s1.size() + s2.size() != s3.size())
		return false;

	// idea, 2d array, with 1st being s1, second being s2
	// go through 3 times: 1st for s1, marking true where match s3
	// 2nd for s2, marking true where match s3
	// 3rd for s1 and s2 (nested) where we say match = match || match[i-1] 
	// for s1 or match[j-1] for s2

	std::vector<std::vector<bool>> v(s1.size() + 1,
		std::vector<bool>(s2.size() + 1, false));

	//find the start points;
	for (int i = 1; i <= s1.size(); ++i) {
		if (s1[i - 1] == s3[i - 1]) {
			v[i][0] = true;
		}
		else {
			break;
		}
	}

	for (int i = 1; i <= s2.size(); ++i) {
		if (s2[i - 1] == s3[i - 1]) {
			v[0][i] = true;
		}
		else {
			break;
		}
	}

	for (int i = 1; i <= s1.size(); ++i) {
		for (int j = 1; j <= s2.size(); ++j) {

			if (s1[i - 1] == s3[i + j - 1]) {
				v[i][j] = v[i - 1][j] || v[i][j];
			}

			if (s2[j - 1] == s3[i + j - 1]) {
				v[i][j] = v[i][j - 1] || v[i][j];
			}

		}
	}

	return v.back().back();
}


int main(void) {




	return 0;
}

