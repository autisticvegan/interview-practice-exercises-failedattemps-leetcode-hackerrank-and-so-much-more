#include <vector>
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <ios>


using namespace std;

std::vector<std::string> answers;


void helper(int qmarks, int currsum, int target, std::string& str, int dayhours, std::string& currp)
{
	if (qmarks == 1)
	{
		for (int i = 0; i <= dayhours; ++i)
		{
			int testsum = i + currsum;

			if (testsum == target)
			{//found an answer
				std::string answeradd = std::to_string(i);
				currp += answeradd;
				answers.push_back(currp);
			}
		}

	}
	else
	{
		qmarks -= 1;
		for (int i = 0; i <= dayhours; ++i)
		{		
			int newcurrsum = currsum + i;
			std::string answeradd = std::to_string(i);
			string newstring = currp + answeradd;
			helper(qmarks, newcurrsum, target, str, dayhours, newstring);
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

	std::string b = "";

	helper(qmarks, 0, target, pattern, dayhour, b);

	std::vector<std::string> result;

	for each(std::string a in answers)
	{
		std::string pat = pattern;
		int j = 0;
		for (unsigned i = 0; i < pattern.length(); ++i)
		{
			if (pat[i] == '?')
			{
				pat[i] = a[j];
				++j;
			}
		}
		result.push_back(pat);
	}

	//put in answers into result;


	return result;


}

int main()
{
	int workHours = 24;
	int dayHours = 5;
	std::string pattern = "0?88?40";
	vector<string> result = findSchedules(workHours, dayHours, pattern);

	int dayhours2 = 4;
	std::string pattern2 = "08??840";
	vector<string> result2 = findSchedules(workHours, dayhours2, pattern2);

	return 0;
}



