#include <stack>
#include <vector>
#include <algorithm>


std::stack<std::pair<int, int>> s;
//StockSpanner() {

//
//int next(int price) {
//
//	int cnt = 1;
//
//	while (!s.empty() && s.top().first <= price) {
//		cnt += s.top().second;
//		s.pop();
//	}
//
//	s.push({ price, cnt });
//	return cnt;
//}

class WPS {

public:
	int weight = 0;
	int point = 0;
	bool end = false;

	bool operator<(WPS const & a)
	{
		return point < a.point;
	}
};


using namespace std; // ROFLMAO
bool carPooling(vector<vector<int>>& trips, int capacity) {
	//idea - sort, then add and subtract
	// weight, point, start or not

	std::vector<WPS> sorted;
	for (auto& t : trips) {

		WPS front;
		WPS back;

		front.weight = t[0];
		front.point = t[1];
		front.end = false;

		back.weight = t[0];
		back.point = t[2];
		back.end = true;

		sorted.push_back(front);
		sorted.push_back(back);
	}

	std::sort(sorted.begin(), sorted.end());

	int currPassengers = 0;
	for (int i = 0; i < sorted.size(); ++i) {

		int p = sorted[i].point;
		while (i < sorted.size() && sorted[i].point == p) {
			
			if (!sorted[i].end) {
				currPassengers += sorted[i].weight;
			}
			else {
				currPassengers -= sorted[i].weight;
			}
			++i;
		}
		--i;
		if (currPassengers > capacity) {
			return false;
		}

	}

	return true;

}

int main(void) {

	std::vector<std::vector<int>> t{ {4,5,6}, {6,4,7}, {4,3,5}, {2,3,5} };
	carPooling(t, 13);

	return 0;
}