/*
Customer placing largest number of orders
fibonnaci
moving average from data stream

for max number, use sort descending and take the 1st one using LIMIT

SELECT customer_number FROM orders GROUP BY customer_number ORDER BY COUNT(*) DESC LIMIT 1 

*/


//fibonacci : Binet's formula.  Note that sqrt(5) is irrational
#include <math.h>
#include <iostream>
#include <cmath>




#include <queue>

class MovingAverageFromDataStream {
	double sum = 0;
	int sizeLimit = 0;
	std::queue<int> collection;

	double next(int val) {
		sum += val;
		collection.push(val);

		if (collection.size() <= sizeLimit) {
			return sum / collection.size();
		}

		int p = collection.front();
		sum -= p;
		collection.pop();
	}
};




const double f = 5.0;
double ff = .5;

double srt5 = std::pow(5, .5);

constexpr int fib(const int i)
{
	if (i == 0)
		return 0;
	if (i == 1)
		return 1;

	return static_cast<int>((pow(1 + srt5, i) - pow(1 - srt5, i)) / (pow(2, i) * srt5));
}
int main()
{
	std::cout << fib(69);
	return 0;
}


double newton() {
	int count = 0;
	int iterations = 50;
	int res = 0;
	int prev = 5;
	while (count < iterations) {
		res = prev - (topFunc(prev) / bottomFuncDerivative(prev));
		prev = res;
	}
	return res;
}

//newtons method

constexpr double topFunc(double in) {
	return in * (in + 2) - 1;
}

constexpr double bottomFuncDerivative(double in) {
	return 2 * in + 2;
}