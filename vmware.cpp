#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <numeric>
// vmware

std::pair<int,int> findPair(std::vector<int>& A, std::vector<int>& B) {
  
  int sumA = std::accumulate(A.begin(), A.end(), 0);
  int sumB = std::accumulate(B.begin(), B.end(), 0);

  int target = std::abs(sumA - sumB) / 2; //assume even, if its odd it would be no sol

  bool foundSol = false;
  std::unordered_set<int> setB(B.begin(), B.end());
  int x = 0;
  int y = 0;

  for (int i = 0; i < A.size(); ++i) {

    int lookFor = A[i] - target;
    int lookFor2 = A[i] + target;
    if (setB.count(lookFor)) {
      
      x = lookFor;
      y = A[i];
      foundSol = true;
      break;
    }

    if (setB.count(lookFor2)) {
      
      x = lookFor2;
      y = A[i];
      foundSol = true;
      break;
    }

  }
  std::pair<int,int> p = {x,y};
  std::pair<int,int> n = {-1,-1};
  return foundSol ? p : n;

}

int main() {

std::vector<int> A = {4,1,2,1,1,2};
std::vector<int> B = {3,6,3,3};
auto p = findPair(A,B);
std::cout << p.first << " " << p.second;

}