#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>


const double epsilon = .001;

// 3 cases, both on left, both on right, split

double bisectionMethodFind(double(*f)(double), double a, double b) {
	
	if (f(a) * f(b) >= 0) {
		std::cout << "err\n";
		return DBL_MAX;
	}

	double c = a;
	// could use do while here
	while ((b - a) >= epsilon) { //accounts for when b == a

		c = b + (a - b) / 2;

		double d = f(c);

		if (std::abs(d) <= epsilon) {
			break;
		}

		double trueA = f(a);

		if (trueA * d < 0) {
			b = c;
		}
		else {
			a = c;
		}

	}

	return c;

}

double f(double c) {
	return std::pow(c, 2) - 2;
}

double ff(double c) {
	return c;
}
// 0, 1 2
// 
// 10 30 20 20 30
// 10 -> 0 , 20 -> 2, 3  30 -> 1, 4
// 0, 2, 1, 1, 2
// 0, 1 , 1, 2, 2

// idea, sort, then map value to index

std::vector<int> squash1D(std::vector<int>& v) {
	std::unordered_map<int, int> value2Index;

	std::vector<int> vv = v;
	std::sort(vv.begin(), vv.end());

	for (int i = 0; i < vv.size(); ++i) {
		if (value2Index.count(vv[i]) == 0)
		{
			value2Index[vv[i]] = i;
		}
	}

	std::vector<int> result;

	for (int j = 0; j < v.size(); ++j) {
			result.push_back(value2Index[v[j]]);
	}

	return result;


}

std::vector<std::vector<int>> squash2D(std::vector<std::vector<int>>& v) {

	//can do in constant space with transpose, or put all into one array and do nlogn instead of n^2 logn

	std::vector<std::vector<int>> r = v;

	for (int i = 0; i < v.size(); ++i) {
		std::sort(r[i].begin(), r[i].end());
	}

	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v[0].size(); ++j) {
			std::swap(r[i][j], r[j][i]);
		}
	}

	for (int i = 0; i < v.size(); ++i) {
		std::sort(r[i].begin(), r[i].end());
	}

	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v[0].size(); ++j) {
			std::swap(r[i][j], r[j][i]);
		}
	}
	std::unordered_map<int, int> val2rank;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[0].size(); ++j) {
			val2rank[r[i][j]] = i * v.size() + j;
		}
	}

	std::vector<std::vector<int>> res;

	for (int i = 0; i < v.size(); ++i) {
		std::vector<int> t;
		for (int j = 0; j < v[0].size(); ++j) {
			t.push_back(val2rank[v[i][j]]);
		}
		res.push_back(t);
	}

	return res;

}

std::vector<std::vector<int>> squash2DFast(std::vector<std::vector<int>>& v) {

	//can do in constant space with transpose, or put all into one array and do nlogn instead of n^2 logn

	std::vector<int> s;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[0].size(); ++j) {
			s.push_back(v[i][j]);
		}
	}

	std::sort(s.begin(), s.end());
	
	std::unordered_map<int, int> value2HierarchySpot;

	for (int i = 0; i < s.size(); ++i) {
		if (value2HierarchySpot.count(s[i]) == 0)
		{
			value2HierarchySpot[s[i]] = i;
		}
	}

	std::vector<std::vector<int>> result;

	for (int i = 0; i < v.size(); ++i) {
		std::vector<int> t;
		for (int j = 0; j < v[0].size(); ++j) {
				
			t.push_back(value2HierarchySpot[v[i][j]]);
		}
		result.push_back(t);
	}

	return result;


}


//differ by 2 letters

bool differsBy2Letters(std::string& A, std::string& B) {
	
	if (A.length() != B.length())
		return false;
	
	std::map<char, int> letter2Count;
	std::map<char, int> letter2CountB;
	for (int i = 0; i < A.length(); ++i) {
		letter2Count[A[i]]++;
		letter2CountB[B[i]]++;
	}
	
	std::map<char, int> r;

	std::set_symmetric_difference(letter2Count.begin(), letter2Count.end(),
		letter2CountB.begin(), letter2CountB.end(),
		std::inserter(r, r.end()));

	int result = 0;
	for (const auto& p : r) {
		result += p.second;
	}

	return result == 2;
}


int main(void) {
	double x = bisectionMethodFind(&f, 0, 2);
	double xx = bisectionMethodFind(&ff, 0, 1);
	double xxx = bisectionMethodFind(&ff, 1, 1);

	std::vector<int> t{ 10, 20, 30 };
	std::vector<int> tt{ 30, 20, 10 };
	std::vector<int> ttt{ 10, 30, 20 , 20, 30 };

	std::vector<std::vector<int>> p{{10, 20},
	{31, 11} };

	std::vector<std::vector<int>> pp{ {10, 20, 30, 69}, {31, 22, 13, 22}, {34, 15, 26, 16}, {17, 38, 29, 1} };

	auto z = squash1D(t);
	auto zz = squash1D(tt);
	auto zzz = squash1D(ttt);

	auto y = squash2D(p);
	auto yy = squash2D(pp);

	auto w = squash2DFast(p);
	auto ww = squash2DFast(pp);

	_ASSERT(y == w);
	_ASSERT(yy == ww);

	return 0;
}