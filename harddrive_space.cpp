#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <chrono>

/*
  Interesting findings: for small window size redblacktree (map) is worse, but it is better
  than deque in bigger window sizes.  ?_?
  Shoutouts to coinbase for a good question, no shoutouts to hackerrank for having a trash
  platform that changes testcases based on whether comments are in code or not LOL
*/

using namespace std::chrono; //LOL BAD CODE

int findMaxOfMins(int windowSize, std::vector<int>& arr) {

	std::map<int,int> num2Count;
	
	if (windowSize > arr.size()) {
		windowSize = arr.size();
	}
	
	for(int i = 0; i < windowSize; ++i) {
		num2Count[arr[i]]++;
	}
	
	if (windowSize == arr.size()) {
		return num2Count.rbegin()->first;
	}
	
	int currmin = num2Count.begin()->first;
	int maxSoFar = currmin;
	
	for(int i = 1; i + windowSize <= arr.size(); ++i) {
		
		num2Count[arr[i-1]]--;
		
		if (num2Count[arr[i-1]] == 0) {
			num2Count.erase(arr[i-1]);
		}
		
		//add next
		num2Count[arr[i + windowSize - 1]]++;
		currmin = num2Count.begin()->first;
		
		maxSoFar = std::max(currmin, maxSoFar);
	}
	
	return maxSoFar;

}

int findMaxOfMinsDeque(int windowsize, std::vector<int>& input) {

  std::deque<int> myD;

  for(int i = 0; i < windowsize; ++i) {
    myD.push_back(input[i]);
  }

  int currMin = *std::min_element(myD.begin(), myD.end());
  int maxSoFar = currMin;

  for(int i = 1; i + windowsize <= input.size(); ++i) {
    myD.pop_front();
    myD.push_back(input[i + windowsize - 1]);
    currMin = *std::min_element(myD.begin(), myD.end());
    maxSoFar = std::max(currMin, maxSoFar);
  }

  return maxSoFar;

}

int main() {
  std::vector<int> t = {1,1,1}; // 2
  std::vector<int> tt = {1,2,3,1,2}; // 1
  std::vector<int> ttt = {8,2,4}; // 3

  std::cout << findMaxOfMins(2, t) << std::endl;
std::cout << findMaxOfMins(1, tt) << std::endl;
std::cout << findMaxOfMins(3, ttt) << std::endl;

  std::vector<int> hugeOne;

  for(int i = 0; i < 100000; ++i) {
    int num = rand() % 100000000 + 1;
    hugeOne.push_back(num);
  }

  int smallWindowSize = 10;
  int bigWindowSize = 100;

  auto start = high_resolution_clock::now(); 
  int res = findMaxOfMins(smallWindowSize, hugeOne);
  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start); 

  std::cout << "time taken using redblack tree for small: " << duration.count() << std::endl;

  start = high_resolution_clock::now(); 
  res = findMaxOfMinsDeque(smallWindowSize, hugeOne);
  stop = high_resolution_clock::now(); 
  duration = duration_cast<microseconds>(stop - start); 

  std::cout << "time taken using deque for small: " << duration.count() << std::endl;

  start = high_resolution_clock::now(); 
  res = findMaxOfMinsDeque(bigWindowSize, hugeOne);
  stop = high_resolution_clock::now(); 
  duration = duration_cast<microseconds>(stop - start); 

  std::cout << "time taken using deque for big: " << duration.count() << std::endl;

  start = high_resolution_clock::now(); 
  res = findMaxOfMins(bigWindowSize, hugeOne);
  stop = high_resolution_clock::now(); 
  duration = duration_cast<microseconds>(stop - start); 

  std::cout << "time taken using redblack tree for big: " << duration.count() << std::endl;



}