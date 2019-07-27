// idea: see the pattern, for pluses and minuses in all the spots
// we have 4 possible equations
// + +
// + -
// - -
// - +
// with each term like so: arr1[i] + arr2[i] + i
// etc.
// sum array is each added together
// 
// once we have our 4 arrays, we also need a helper function
// that will find the max and min for that array, then return max - min
// finally, use Max( max(helper(1), helper(2)), max(helper(3), helper(4)))

int MaxMinusMin(std::vector<int>& v) {

	int max = INT_MIN;
	int min = INT_MAX;
	for (const auto& i : v) {
		max = std::max(max, i);
		min = std::min(min, i);
	}
	return (max - min);
}


int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {

	int size = arr1.size();
	std::vector<int> PlusPlus(size);
	std::vector<int> PlusMinus(size);
	std::vector<int> MinusMinus(size);
	std::vector<int> MinusPlus(size);

	for (int i = 0; i < arr1.size(); ++i) {
		PlusPlus[i] = arr1[i] + arr2[i] + i;
		PlusMinus[i] = arr1[i] + arr2[i] - i;
		MinusMinus[i] = arr1[i] - arr2[i] - i;
		MinusPlus[i] = arr1[i] - arr2[i] + i;
	}

	return std::max(std::max(MaxMinusMin(PlusPlus), MaxMinusMin(PlusMinus)),
		std::max(MaxMinusMin(MinusPlus), MaxMinusMin(MinusMinus)));
}


int main(void) {
	return 0;
}

std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {

	//hash way easy

	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	std::vector<int> res;

	auto iter1 = nums1.begin();
	auto iter2 = nums2.begin();

	while (iter1 != nums1.end() && iter2 != nums2.end())
	{
		if (*iter1 < *iter2)
		{
			++iter1;
		}
		else if (*iter1 > *iter2)
		{
			++iter2;
		}
		else
		{
			res.push_back(*iter1);
			++iter1;
			++iter2;
		}
	}

	return res;
}
int numEquivDominoPairs(std::vector<std::vector<int>>& dominoes) {

	int res = 0;
	std::map<std::vector<int>, int> count;
	for (auto& d : dominoes) {
		if (d[0] > d[1])
			std::swap(d[0], d[1]);

		res += count[d]++;
	}

	return res;
}

std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {

	//hash way easy

	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	std::vector<int> res;

	auto iter1 = nums1.begin();
	auto iter2 = nums2.begin();

	while (iter1 != nums1.end() && iter2 != nums2.end())
	{
		if (*iter1 < *iter2)
		{
			++iter1;
		}
		else if (*iter1 > *iter2)
		{
			++iter2;
		}
		else
		{
			res.push_back(*iter1);
			++iter1;
			++iter2;
		}
	}

	return res;
}

class RLEIterator {
public:
	std::vector<int> members;
	int index;
	RLEIterator(vector<int>& A) {
		members = A;
		index = 0;
	}

	int next(int n) {

		while (index < members.size() && n > members[index]) {
			n -= members[index];
			index += 2; // only even numbers are our values
		}

		// either of 2 conditions was hit, if we still have members left...
		if (index < members.size()) {
			members[index] -= n;
			return members[index + 1]; //remeber, index is our COUNT, +1 would
			// be our actual value we want
		}


		return -1;
	}
};


class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.

	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator(*this).next();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		return Iterator::next();
	}

	bool hasNext() const {
		return Iterator::hasNext();
	}
};


class H2O {
public:

	//idea, have 2 locks for the things
	// also, we can use either an atomic<int> (poverty semaphore)
	// or an actual semaphore.
	// only release oxygen when it is 0 (starting state)
	// if its 0, release a hydrogren and set to 1,
	// if its 1, release a hydrogen and set to 0,
	// note that when its 0 we unlock hydrogen, and when its not we lock hyd
	// 

	std::mutex hydroLock;
	std::mutex oxyLock;
	std::atomic<int> povertySemaphore;

	H2O() {
		hydroLock.lock();
		povertySemaphore = 0;
	}

	void hydrogen(function<void()> releaseHydrogen) {

		if (povertySemaphore.load() == 1) {
			povertySemaphore = 0;
			// releaseHydrogen() outputs "H". Do not change or remove this line.
			releaseHydrogen();
			oxyLock.unlock();
		}
		else if (povertySemaphore.load() == 0) {
			// releaseHydrogen() outputs "H". Do not change or remove this line.
			hydroLock.lock();
			releaseHydrogen();
			povertySemaphore = 1;
		}


	}

	void oxygen(function<void()> releaseOxygen) {

		// releaseOxygen() outputs "O". Do not change or remove this line.

		oxyLock.lock();

		if (povertySemaphore.load() == 0) {
			releaseOxygen();
		}

		hydroLock.unlock();

	}
};



class FooBar {
private:
	int n;
	std::mutex m1;
	std::mutex m2;

public:
	FooBar(int n) {
		this->n = n;
		m1.lock();
	}

	void foo(function<void()> printFoo) {

		for (int i = 0; i < n; i++) {

			// printFoo() outputs "foo". Do not change or remove this line.
			m2.lock();
			printFoo();
			m1.unlock();
		}
	}

	void bar(function<void()> printBar) {

		for (int i = 0; i < n; i++) {

			// printBar() outputs "bar". Do not change or remove this line.
			m1.lock();
			printBar();
			m2.unlock();
		}
	}
};


class ZeroEvenOdd {
private:
	int n;
	std::mutex mutZero;
	std::mutex mutEven;
	std::mutex mutOdd;

	// 0, odd, 0, even  x infinitity
public:
	ZeroEvenOdd(int n) {
		this->n = n;
		mutEven.lock();
		mutOdd.lock();
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		for (int i = 1; i <= n; ++i) {
			mutZero.lock();
			printNumber(0);

			if (i % 2 == 0) {
				mutEven.unlock();
			}
			else {
				mutOdd.unlock();
			}
		}
	}

	void even(function<void(int)> printNumber) {
		for (int i = 2; i <= n; i += 2) {
			mutEven.lock();
			printNumber(i);
			mutZero.unlock();
		}
	}

	void odd(function<void(int)> printNumber) {
		for (int i = 1; i <= n; i += 2) {
			mutOdd.lock();
			printNumber(i);
			mutZero.unlock();
		}
	}
};