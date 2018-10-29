#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>

int GetClosestIndex(int index, std::string& input)
{
	std::unordered_map<char, std::vector<int>> Letter2Indices;

	for (int i = 0; i < input.length(); ++i)
	{
		char c = input[i];
		if (Letter2Indices.count(c) == 0)
		{
			std::vector<int> a;
			a.push_back(i);
			Letter2Indices.insert({ c,a });
		}
		else
		{
			Letter2Indices[c].push_back(i);
		}
	
	}
	//now everything is inserted.

	char te = input[index];

	//3 cases: 
	//1. there is only one index, so return -1
	//2. there are 2, so return the only one
	//3. there are more than 2, compare smaller and bigger, and return smaller
	//3. equidistant, return smallest one
	if (Letter2Indices[te].size() == 1)
	{
		return -1;
	}
	else if (Letter2Indices[te].size() == 2)
	{
		int r = *Letter2Indices[te].begin();
		if (r != index)
			return r;
		else
			return *Letter2Indices[te].crbegin();
	}
	else
	{
		std::sort(Letter2Indices[te].begin(), Letter2Indices[te].end());
		//array is now sorted

		//find the spot of the index;
		auto spot = std::lower_bound(Letter2Indices[te].begin(), Letter2Indices[te].end(), index);
		
		//if its at the front, go forward
		if (spot == Letter2Indices[te].begin())
		{
			return *Letter2Indices[te].begin() + 1;
		}//if its at the end, go back
		else if (spot == (Letter2Indices[te].begin() + Letter2Indices[te].size() - 1))
		{		
			return *(Letter2Indices[te].begin() + Letter2Indices[te].size() - 2);
		}
		else
		{
			//if its anywhere else, go forward and back, and compare distance
			int back = *(spot - 1);
			int forward = *(spot + 1);

			int bdiff = index - back;
			int fdiff = forward - index;

			//if distance is same, return back

			//else, return shorter

			if (bdiff > fdiff)
				return fdiff;

			return bdiff;
		}
	}
	return -1;
}


int main(void)
{
	std::string a = "I LIKE BIG BUTTONS AND I CANNOT LIE";
	GetClosestIndex(3, a);
	return 0;
}