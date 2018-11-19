#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>


bool validMountainArray(std::vector<int>& A) {

	if (A.size() < 3)
		return false;

	int begin = 0;
	int end = A.size() - 1;

	while (begin < end && A[begin] < A[begin + 1])
		++begin;

	while (end > begin && A[end] < A[end - 1])
		--end;

	if (begin == 0 || end == A.size() - 1)
		return false;

	if (begin == end)
		return true;

	return false;
}

std::vector<int> diStringMatch(std::string S) {

	std::vector<int> resu(S.length() + 1);

	int low = 0;
	int high = S.length();
	for (int i = 0; i < S.size(); ++i)
	{
		if (S[i] == 'I')
		{
			resu[i] = low++;
		}
		else // is a D
		{
			resu[i] = high--;
		}
	}

	resu[S.length()] = low; //this could be either doesn't matter
	return resu;
}
};

class LFUCache {
public:

	std::unordered_map<int, std::pair<int, int>> Key2ValAndFreq;
	std::unordered_map<int, std::list<int>::iterator> Key2ListIter;
	std::unordered_map<int, std::list<int>> Freq2List;

	//using lists so iterators arent invalidated

	long long capacity = 0;
	long long minfreqkey = 0; //need this because we cant sort our maps

	LFUCache(int capacity_) {

		capacity = capacity_;
	}

	int get(int key)
	{
		//check if it exists
		if (Key2ValAndFreq.find(key) == Key2ValAndFreq.end())
			return -1;

		//get the frequency for this key, and erase it from the freq list
		int freq = Key2ValAndFreq[key].second;
		Freq2List[freq].erase(Key2ListIter[key]);

		//increase the frequency for this key
		Key2ValAndFreq[key].second++;
		freq++;
		//add to the list (since we updated the frequency)
		Freq2List[freq].push_front(key);
		Key2ListIter[key] = Freq2List[freq].begin();

		//update minfreq if 
		if (Freq2List[minfreqkey].empty())
		{
			++minfreqkey;
		}

		return Key2ValAndFreq[key].first;
	}

	void put(int key, int value)
	{
		if (capacity <= 0)
			return;

		//if the key already exists - simple - just update it
		int storedValue = get(key);
		if (storedValue != -1)
		{
			Key2ValAndFreq[key].first = value;
			return;
		}

		//check if size is >= capacity
		//if it is, erase from the minfreqkey list, and the iterator
		//also erase it from the main hash
		//update size

		if (Key2ValAndFreq.size() >= capacity)
		{
			int back = Freq2List[minfreqkey].back();
			Key2ValAndFreq.erase(back);
			Key2ListIter.erase(back);
			Freq2List[minfreqkey].pop_back();
		}

		//set the frequency to 1 for this key
		//add to list and iter
		//update minfreqkey
		//update size
		Key2ValAndFreq[key] = { value,1 };
		Freq2List[1].push_front(key);
		Key2ListIter[key] = Freq2List[1].begin();
		minfreqkey = 1;

	}
};

int main(void)
{


	return 0;
}