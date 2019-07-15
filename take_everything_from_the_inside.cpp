
static int val = 0;
int f(int a, int b) {
	val++;

	if (a == b) {
		return a;
	}

	if (a < b) {
		return f(a, b - a);
	}
	else {
		return f(a - b, b);
	}
	
}

bool f1(int val) {
	return (val | (val + 1)) == val;
}

bool f2(int val) {
	return (val & (val + 1)) == val;
}

bool f3(int val) {
	return (val & (val - 1)) == 0;
}

bool f4(int val) {
	return (val | (val - 1)) == 0;
}

bool f5(int val) {
	return (val >> 1) == (val / 2);
}

bool f6(int val) {
	return ((val >> 1) << 1) == val;
}

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T, int count>
void foo(T x) {
	T val[count];
	for (int i = 0; i < count; ++i) {
		val[i] = x++;
		cout << val[i] << " ";
	}
};

int main(void) {

	float y = 2.1;
	foo<float, 3>(y);


	return result;


	return 0;



}