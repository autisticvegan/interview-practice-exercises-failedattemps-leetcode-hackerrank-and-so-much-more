#include <vector>
#include <iostream>
#include <climits>
#include <cstdlib>

class randomNumberGen {
public:
	int minL;
	int maxL;
	std::vector<int> nums;	
	int endOfIndex;

	randomNumberGen(int min, int max) : minL(min), maxL(max) {
		reset();
		std::srand(69);
	};
	void reset() {
		nums.resize(maxL - minL + 1);
		for (int i = 0; i < nums.size(); ++i) {
			nums[i] = minL + i;
		}
		endOfIndex = nums.size();
	}
	int gen() {

		if (endOfIndex == 0) {
			reset();
		}

		int index = std::rand() % endOfIndex;
		int val = nums[index];
		std::swap(nums[index], nums[endOfIndex-1]);

		endOfIndex--;

		return val;

	}
	//can also do shuffle way
};


int main(void) {

	randomNumberGen r(2,69);
	for (int i = 0; i < 100; ++i) {
		std::cout << r.gen() << std::endl;
	}
	return 0;
}