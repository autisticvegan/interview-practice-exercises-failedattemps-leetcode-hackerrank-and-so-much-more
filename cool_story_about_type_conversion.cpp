#include <vector>
#include <iostream>
int main(void) {


	std::vector<int> nums{ 1,2,3,4,-2,2,1,-1 };
	//cool story: check what happens if you set N to int not size_t :)
	size_t N = nums.size();
	std::vector<int> nums2{ 1,2,3,4,-2,2,1,-1 };
	for (int& n : nums) {
		n %= N; // saved lots of effort for this
	}

	for (int i = 0; i < nums2.size(); ++i) {
		nums2[i] %= nums2.size();
	}

	return 0;
}

