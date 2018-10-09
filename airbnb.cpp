#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include <iterator>
#include <map>
#include <algorithm>

//custom sort
/*
using namespace std;

vector< MyStruct > values;

sort( values.begin( ), values.end( ), [ ]( const auto& lhs, const auto& rhs )
{
return lhs.key < rhs.key;
});*/

std::vector<std::string> split(std::string& s)
{
	using namespace std;
	istringstream iss(s);
	vector<string> tokens{ istream_iterator<string>{iss},
		istream_iterator<string>{} };

	return tokens;
}

std::vector<std::string> taketurn(std::vector<std::string> input)
{
	std::map<std::string, std::string> Army2Location;
	std::unordered_map<std::string, std::vector<std::string>> Location2Armies;
	std::unordered_map<std::string, int> Army2Strength;
	
	std::unordered_set<std::string> InContention;
	std::unordered_map<std::string, std::string> Army2Support;
	//need support to army in case a supported army dies
	std::unordered_map<std::string, std::vector<std::string>> Support2Armies;

	//move and holds
	for (std::string w : input)
	{
		std::vector<std::string> tokens = split(w);

		std::string action = tokens[2];
		std::string army = tokens[0];
		std::string location = tokens[1];

		//fill army2location, location2armies,army2support
		//army2strength

		//tokens[3] is supported or move to
		if (action == "MOVE")
		{
			std::string destination = tokens[3];

			if (Location2Armies.count(destination))
			{
				Location2Armies[destination].push_back(army);
				InContention.insert(destination);
			}
			else
			{
				std::vector<std::string> v;
				v.push_back(army);
				Location2Armies.insert({ destination, v });
			}

			Army2Location[army] = destination;

		}
		else if (action == "HOLD")
		{
			if (Location2Armies.count(location))
			{
				Location2Armies[location].push_back(army);
		
			}
			else
			{
				std::vector<std::string> v;
				v.push_back(army);
				Location2Armies.insert({ location, v });
			}

			Army2Location[army] = location;
		
		}
		else if (action == "SUPPORT")
		{
			std::string supported = tokens[3];

			Army2Support[army] = supported; //dont know where their location is
			//

		//	Army2Location[army] = location; //does supporting army end up at original location, or where it is supporting?
			////maybe if in contention, it stays, if not, it goes
		}

		Army2Strength[army] = 1;
		
	}
	std::unordered_set<std::string> DeadArmies;
	//figure out which in contention, minus their supports
	for (const auto& it : Army2Support)
	{
		std::string loc = Army2Location[it.first];
		if (InContention.count(loc))
		{
			Army2Support.erase(it.first);
			DeadArmies.insert(it.first);
		}//else update the location
		else
		{
			if (Support2Armies.count(it.second))
			{
				Support2Armies[it.second].push_back(it.first);
			}
			else
			{
				std::vector<std::string> s;
				s.push_back(it.first);
				Support2Armies.insert({ it.second,s });
			}

		}
	}

	//add in the support strengths

	//for each support, add to strengths

	for (const auto& it : Army2Support)
	{
		Army2Strength[it.second] += 1;
	}
	//battle

	//for each location, sort the entries by strength.
	//iterate over all the armies and insert into a map, get the one at the end as the top
	//if there is more than 1 at the top, all die.  else, top one wins, and others die
	//add dead ones to a set so we can iterate over them

	for (const auto& it : Location2Armies)
	{
		if (it.second.size() > 1)
		{
			std::map<int, std::vector<std::string>> strength2armies;

			for (const auto& jt : it.second)
			{
				if (DeadArmies.count(jt))
					continue;

				int stre = Army2Strength[jt];
				if (strength2armies.count(stre))
				{
					strength2armies[stre].push_back(jt);
				}
				else
				{
					std::vector<std::string> v;
					v.push_back(jt);
					strength2armies.insert({ stre,v });
				}
			}//now all armies are inserted

			//which army is at the end?
			std::vector<std::string> strongarmies = strength2armies.rbegin()->second;

			if (strongarmies.size() == 1) //kill all others
			{
				std::string winner = strongarmies[0];


				for (const auto& zt : strength2armies)
				{
					for (const auto& gg : zt.second)
					{
						if(gg != winner)
							DeadArmies.insert(gg);
						else
						{	
							for (const auto& ff : Support2Armies[gg])
							{
								Army2Location[ff] = it.first;
							}
						}
					}
				}
			}
			else //everyone dies
			{
				for (const auto& zt : strength2armies)
				{
					for (const auto& gg : zt.second)
					{
						DeadArmies.insert(gg);
					}
				}
			}
		}
	}

	std::vector<std::string> result;
	//output results
	//iterate from top 
	for (const auto& it : Army2Location)
	{
		if (DeadArmies.count(it.first))
		{
			std::string s2push;
			s2push += it.first;
			s2push += " [dead]";
			result.push_back(s2push);
		}
		else
		{
			std::string s2push;
			s2push += it.first;
			s2push += " ";
			s2push += it.second;
			result.push_back(s2push);
		}
	}
	//can also use custom sorter in case we were given input out of order




	std::vector<std::string> testthis;
	testthis.push_back("Z");
	testthis.push_back("P");
	testthis.push_back("B");

	std::sort(testthis.begin(), testthis.end());

	std::map<char, int> u;
	u.insert({ 'c',2 });
	u.insert({ 'a',1 });


	return result;
}



int main(void)
{
	//A Munich MOVE Warsaw

	//B Warsaw HOLD

	//C Munich SUPPORT B

	//C Ass MOVE Warsaw

	std::vector<std::string> input;

	input.push_back("A Munich MOVE Warsaw");
	input.push_back("B Warsaw HOLD");
	input.push_back("C Munich SUPPORT B");
	input.push_back("D Ass MOVE Warsaw");


	taketurn(input);

	return 0;

}