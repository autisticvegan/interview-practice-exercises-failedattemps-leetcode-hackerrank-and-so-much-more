#include <vector>
#include <string>
#include <algorithm>

int maxTurbulenceSize(std::vector<int>& A)
{
	//2 possible sequences - one that ends with 2 increases
	// or one that ends with 2 decreases

	int maxlength = 1;
	int decreasingSeq = 1;
	int increasingSeq = 1;

	for (int i = 1; i < A.size(); ++i)
	{
		//either increasing, decreasing, or equal

		if (A[i] > A[i - 1])
		{
			increasingSeq = 1 + decreasingSeq;
			decreasingSeq = 1;
		}
		else if (A[i] < A[i - 1])
		{
			decreasingSeq = increasingSeq + 1;
			increasingSeq = 1;

		}
		else
		{
			increasingSeq = 1;
			decreasingSeq = 1;
		}

		maxlength = std::max(maxlength, std::max(decreasingSeq, increasingSeq));
	}


	return maxlength;
}

//problem from argo.ai
// Given a sequence of intervals with weights, imagine dropping lines down.  Return the max weight that any line overlaps.
// interviewer said this could be solved in logn.  I think thats bs.
//solution: sort intervals according to end, then do linear scan (O(n)) across, adding if beginning and subtracting if
//an end.  You need a new structure for this with val, bool(end or not), and weight.
class Interval
{
public:
	int start;
	int end;
	int weight;

	bool operator <(const Interval& i) const
	{
		return end < i.end;
	}
};


class Point
{
public:
	Point(int s, bool f, int w) : point(s), isEnd(f), weight(w)
	{}
	int point;
	bool isEnd;
	int weight;
};

int GetMaxOverlappingWeightedIntervals(std::vector<Interval>& in)
{
	std::sort(in.begin(), in.end());

	std::vector<Point> points(in.size()*2);

	for (int i = 0; i < in.size(); i+=2)
	{
		points[i] = Point(in[i].start, false, in[i].weight);
		points[i + 1] = Point(in[i].end, true, in[i].weight);
	}

	int maxweight = 0;
	int curr = 0;
	for (int i = 0; i < points.size(); ++i)
	{
		if (points[i].isEnd)
		{
			curr -= points[i].weight;
		}
		else
		{
			curr += points[i].weight;
		}

		maxweight = std::max(maxweight, curr);
	}
	return maxweight;
}