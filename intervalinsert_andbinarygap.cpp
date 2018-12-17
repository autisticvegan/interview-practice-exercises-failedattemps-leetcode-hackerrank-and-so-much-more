#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

class Interval
{
public:
	int start;
	int end;
};

int binaryGap(int N) {
	int res = 0;
	for (int d = -32; N != 0; N /= 2, d++)
	{
		if (N % 2)
		{
			res = std::max(res, d);
			d = 0;
		}
	}

	return res;
}

std::vector<Interval> insert(std::vector<Interval>& intervals, Interval newInterval)
{
	//find start    
	auto comparator = [](const Interval& a, const Interval& b)
	{
		return a.end < b.start;
	};

	auto rangepair = std::equal_range(intervals.begin(), intervals.end(), newInterval, comparator);

	if (rangepair.first == rangepair.second)
	{
		intervals.insert(rangepair.first, newInterval);
	}
	else
	{

		rangepair.second--;

		rangepair.second->start = std::min(newInterval.start, rangepair.first->start);
		rangepair.second->end = std::max(newInterval.end, rangepair.second->end);
		intervals.erase(rangepair.first, rangepair.second);
	}

	return intervals;
}

int main(void)
{
	binaryGap(-22);
	return 0;
}




std::vector<Interval> merge(std::vector<Interval>& intervals) {

	if (intervals.size() <= 1)
		return intervals;

	std::sort(intervals.begin(), intervals.end(), [](const Interval& left, const Interval& right) {return left.start < right.start; });

	auto start = intervals.begin();
	auto end = intervals.begin();

	while (++end != intervals.end())
	{
		//2 cases, either overlap or not
		if (start->end >= end->start)
		{
			start->end = std::max(start->end, end->end);
		}
		else
		{  //copy over
			start++;
			*start = *end;
		}
	}


	intervals.erase(start + 1, end);
	return intervals;
}