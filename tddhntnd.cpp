#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>
#include <istream>
#include <iterator>
#include <iostream>
#include <sstream>

std::vector<std::string> uncommonFromSentences(std::string A, std::string B) {

	std::unordered_map<std::string, int> sa;

	std::vector<std::string> res;

	std::istringstream is(A);

	std::vector<std::string> toks{ std::istream_iterator<std::string>{is},
								  std::istream_iterator<std::string>{} };

	for (std::string ss : toks)
	{
		sa[ss]++;
	}

	std::istringstream iss(B);
	std::vector<std::string> toksB{ std::istream_iterator<std::string>{iss},
								  std::istream_iterator<std::string>{} };

	for (std::string ss : toksB)
	{
		sa[ss]++;
	}


	for (const auto& it : sa)
	{
		if (it.second == 1)
		{
			res.push_back(it.first);
		}
	}


	return res;
}

std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& nums, int r, int c) {

	std::vector<std::vector<int>> res(r, std::vector<int>(c));

	if (nums.empty())
		return nums;

	int rows = nums.size();
	int cols = nums[0].size();

	int dim = rows * cols;

	int newdim = r * c;

	if (newdim != dim)
		return nums;

	int rr = 0;
	int cc = 0;
	for (int i = 0; i < r; ++i)
	{


		for (int j = 0; j < c; ++j)
		{
			res[i][j] = nums[rr][cc];
			++cc;

			if (cols == cc)
			{
				cc = 0;
				++rr;
			}

		}
	}

	return res;
}

int main(void)
{
	std::vector<std::vector<int>> t(2);
	t[0].push_back(1);
	t[0].push_back(2);

	t[1].push_back(3);
	t[1].push_back(4);

	matrixReshape(t, 1, 4);

	return 0;
}