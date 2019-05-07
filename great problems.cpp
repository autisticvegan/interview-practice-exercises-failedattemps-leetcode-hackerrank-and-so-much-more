/*
Sum of Even Numbers After Queries
Logger Rate Limiter
Divisor Game
Triangle Judgement

SELECT
	x,
	y,
	z,
	CASE
		WHEN x + y > z AND x + z > y AND y + z > x THEN 'Yes'
		ELSE 'No'
	END AS 'triangle'
FROM
	triangle

*/

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>


bool divisorGame(int N) {
	return N % 2 == 0;
}

class Logger {
public:
	Logger() {}

	bool shouldPrintMessage(int timestamp, std::string message) {
		if (timestamp < m[message]) return false;
		m[message] = timestamp + 10;
		return true;
	}

private:
	std::unordered_map<std::string, int> m;
};

std::vector<int> sumEvenAfterQueries(std::vector<int>& A, std::vector<std::vector<int>>& queries) {

	int sum = 0;

	for (const auto& i : A) {
		if (i % 2 == 0) {
			sum += i;
		}
	}
	std::vector<int> res;
	for (const auto& p : queries) {
		// for each query,
		// do the thing.  if result is odd, minus initial val from sum
		// if it is even, add it in, minus initial val

		int initialVal = A[p[1]];
		int val = p[0];
		A[p[1]] += val;

		if (A[p[1]] % 2 == 0) {
			sum += A[p[1]];
		}

		if (initialVal % 2 == 0) {
			sum -= initialVal;
		}

		res.push_back(sum);
	}
	return res;
}

int main(void) {

	std::vector<int> a{ 1,2,3,4 };
	std::vector<std::vector<int>> t;
	t.push_back(std::vector<int>{1, 0});
	t.push_back(std::vector<int>{-3, 1});
	t.push_back(std::vector<int>{-4, 0});
	t.push_back(std::vector<int>{2, 3});


	sumEvenAfterQueries(a, t);

	return 0;
}