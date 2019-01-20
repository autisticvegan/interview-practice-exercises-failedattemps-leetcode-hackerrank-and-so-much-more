#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <queue>

int networkDelayTime(std::vector<std::vector<int>>& times, int N, int K)
{
	//use djikstra, initialize everything to INT_MAX

	//keep track of 

	//keep track of all distances

	//find time to longest one, if its INT_MAX, not reachable

	std::vector<int> distances(N + 1, INT_MAX);

	distances[K] = 0;

	std::queue<int> q;

	q.push(K);

	while (!q.empty())
	{
		int t = q.front();
		q.pop();

		for (int i = 0; i < times.size(); ++i)
		{
			if (times[i][0] == t)
			{
				//if we found our node, look at its target
				if (distances[t] + times[i][2] < distances[times[i][1]])
				{
					//lower the distance to the new min
					distances[times[i][1]] = distances[t] + times[i][2];
					q.push(times[i][1]);
				}
			}
		}
	}


	int res = *std::max_element(distances.begin() + 1, distances.end());
	if (res == INT_MAX)
		return -1;

	return res;
}

int largestPerimeter(std::vector<int>& A) {

	if (A.empty() || A.size() < 3)
		return 0;

	// Get 3 biggest

	std::sort(A.begin(), A.end(), std::greater<int>());
	// check if valid

	for (int i = 0; i < A.size() - 2; ++i)
	{
		int f = A[i];
		int d = A[i + 1];
		int g = A[i + 2];

		if (f < d + g)
		{
			return f + g + d;
		}
	}

	// while not valid, get rid of smallest and take next

	return 0;
}

class Solution22 {
public:





	// 1,10,100
	// I V X, X L C, C D M
	// power *= 10
	int romanToInt(std::string s) {



		int power = 1;

		//go in reverse order
		auto first = s.crbegin();
		auto last = s.crend();

		std::vector<std::string> h;
		h.push_back("IVX");
		h.push_back("XLC");
		h.push_back("CDM");


		auto helper = [&](char ones, char fives, char tens)
		{


			//first count up ones
			int res = 0;

			while (first != last && (*first == ones))
			{
				++res;
				++first;
			}

			//then fives and tens
			while (first != last && (*first == fives || *first == tens))
			{
				if (*first == fives)
				{
					res += 5;
				}
				else if (*first == tens)
				{
					res += 10;
				}

				++first;
				//subtract off ones inside
				while (first != last && (*first == ones))
				{
					++first;
					--res;
				}
			}

			return res;
		};


		int result = 0;

		for (int i = 0; i < 3; ++i)
		{
			result += helper(h[i][0], h[i][1], h[i][2]) * power;
			power *= 10;
		}

		return result;
	}
};