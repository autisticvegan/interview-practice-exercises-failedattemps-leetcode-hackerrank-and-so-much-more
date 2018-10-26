#include <vector>
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <ios>

//This is an optimized version of my old (bad) solution
//in the old version i was creating a new vector each backtrack,
//which caused a failure in 1 testcase (abort was called)
//which meant that too much memory was being used on the stack
//this version fixes that problem, and has some other early exit
//optimizations as well :)

using namespace std;

std::vector<std::string> answers;


void helper(int qmarks, int currsum, int target, std::string& str, int dayhours, std::vector<int>& v)
{
	if (qmarks == 1)
	{
		//optimization
		if ((target > dayhours + currsum))
		{
			return;
		}

		for (int i = 0; i <= dayhours; ++i)
		{
			int testsum = i + currsum;

			if (testsum == target)
			{//found an answer
				v.push_back(i);
				std::string ans = str;
				int z = 0;
				for (int i = 0; i < str.length(); ++i)
				{
					if (str[i] == '?')
					{
						ans[i] = '0' + v[z];
						++z;
					}
				}
				answers.push_back(ans);
				v.pop_back();
				break;
			}
		}

	}
	else
	{
		qmarks -= 1;
		for (int i = 0; i <= dayhours; ++i)
		{
			int newcurrsum = currsum + i;

			if (newcurrsum > target)
			{
				break;
			}
				

			v.push_back(i);
			helper(qmarks, newcurrsum, target, str, dayhours, v);
			v.pop_back();
		}

	}


}


std::vector<std::string> findSchedules(int workhour, int dayhour, string pattern)
{
	answers.clear();

	int qmarks = 0;
	int sum = 0;
	for (unsigned i = 0; i < pattern.length(); ++i)
	{
		if (pattern[i] == '?')
			qmarks++;
		else
		{
			sum += pattern.at(i) - '0';
		}

	}

	int target = workhour - sum;

	std::vector<int> b;
	helper(qmarks, 0, target, pattern, dayhour, b);


	return answers;


}

int main()
{
	int workHours = 24;
	int dayHours = 5;
	std::string pattern = "0?88?40";
	vector<string> result = findSchedules(workHours, dayHours, pattern);

	//4,0
	//0,4
	//1,3
	//3,1
	//2,2
	//

	int dayhours2 = 4;
	std::string pattern2 = "08??840";
	vector<string> result2 = findSchedules(workHours, dayhours2, pattern2);

	int dayhours4 = 2;
	std::string pattern4 = "0???840";
	vector<string> result4 = findSchedules(15, dayhours4, pattern4);


	int dayhours3 = 8;
	int workhours2 = 35;
	std::string pattern3 = "???????";
	std::vector<std::string> result3 = findSchedules(workhours2, dayhours3, pattern3);

	return 0;
}