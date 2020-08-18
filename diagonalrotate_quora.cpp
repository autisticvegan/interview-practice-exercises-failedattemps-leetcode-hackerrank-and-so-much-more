#include <iostream>
#include <vector>
#include <map>


void rotate(std::vector<std::vector<int>>& m, int k) {

k %= 4;
if (k == 0) {
  return;
}
int size = 3;
while (size <= m.size()) {

std::vector<int> left;
std::vector<int> right;
std::vector<int> bottom;
std::vector<int> top;

  int plusCoord = m.size() / 2 + size/2;
  int minusCoord = m.size() / 2 - size/2;

  // 1 2 3
  // 4 5 6
  // 7 8 9

  for(int i= minusCoord + 1; i < plusCoord; ++i) {
    top.push_back(m[minusCoord][i]);
    bottom.push_back(m[plusCoord][plusCoord-i]);
    left.push_back(m[plusCoord-i][minusCoord]);
    right.push_back(m[i][plusCoord]);
  }

  if (k == 2) {
    int index = 0;
      for(int i= minusCoord + 1; i < plusCoord; ++i) {

        m[minusCoord][i] = bottom[index];
        m[plusCoord][plusCoord-i] = top[index];
        m[i][plusCoord] = left[index];
        m[plusCoord-i][minusCoord] = right[index];
    ++index;
    }
  } else if (k == 1) {

    int index = 0;
      for(int i= minusCoord + 1; i < plusCoord; ++i) {

        m[minusCoord][i] = left[index];
        m[plusCoord][plusCoord-i] = right[index];
        m[i][plusCoord] = top[index];
        m[plusCoord-i][minusCoord] = bottom[index];

    ++index;
      }

  } else if (k == 3) {

    int index = 0;
      for(int i= minusCoord + 1; i < plusCoord; ++i) {

        m[minusCoord][i] = right[index];
        m[plusCoord][plusCoord-i] = left[index];
        m[i][plusCoord] = bottom[index];
        m[plusCoord-i][minusCoord] = top[index];

    ++index;
      }
  }

  size += 2;
}


}

void print(std::vector<std::vector<int>>& m) {

  std::cout << std::endl;

  for(int i = 0; i < m.size(); ++i) {
    for(int j = 0; j < m.size(); ++j) {
      std::cout << m[i][j] << "  ";
      if(m[i][j] < 10) {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

int main() {

std::vector<std::vector<int>> tt{{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},
{16,17,18,19,20},{21,22,23,24,25}};

print(tt);

rotate(tt, 2);

print(tt);

rotate(tt, 3);
print(tt);

}