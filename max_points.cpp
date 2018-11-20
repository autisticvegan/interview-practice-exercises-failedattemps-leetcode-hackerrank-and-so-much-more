#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>


int maxPoints(std::vector<Point>& points) {

	//n^2, check each point against all others in terms of slope
	//to avoid double precision and vertical problems, save slope as a pair
	//divide by gcd so we dont have multiples
	//if gcd is 0, that means duplicate, so keep track of that too
	int max = 0;

	for (int i = 0; i < points.size(); ++i)
	{
		int dups = 0;
		int curmax = 0;
		std::map<std::pair<int, int>, int> Slope2Count;
		for (int j = i + 1; j < points.size(); ++j)
		{
			int xslope = points[i].x - points[j].x;
			int yslope = points[i].y - points[j].y;

			int g = __gcd(xslope, yslope);

			if (g == 0)
			{

				++dups;
				continue;
			}

			xslope /= g;
			yslope /= g;

			int thiscount = ++Slope2Count[{xslope, yslope}];

			curmax = std::max(curmax, thiscount);
		}

		max = std::max(max, curmax + dups + 1); //add one for the point itself
	}


	return max;
}
int main(void)
{


	return 0;
}