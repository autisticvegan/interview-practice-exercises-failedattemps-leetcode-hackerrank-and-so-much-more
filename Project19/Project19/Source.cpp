#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "json/json.h"
#include "json/json-forwards.h"

class Store
{
public:
	std::string origString;
	Json::Value json;
	std::map<std::string, std::set<int>> lists;
};


bool ContainsArrayEX(const Json::Value& needle, Store& s, const std::string& ss)
{
	for (Json::ArrayIndex i = 0; i < needle.size(); ++i)
	{
		if(s.lists[ss].find(needle[i].asInt()) == s.lists[ss].end())
			return false;
	}
	return true;
}


bool ContainsArray(const Json::Value& needle, const Json::Value& haystack)
{

	for (Json::ArrayIndex s = 0; s < needle.size(); ++s)
	{
		bool flag = false;
		for (Json::ArrayIndex t = 0; t < haystack.size(); ++t)
		{
			if (haystack[t] == needle[s])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			return false;
	}
	return true;
}

bool ContainsObjectEX(Json::Value& needle, Json::Value& haystack)
{
	//change to pointers?
	std::queue<Json::Value*> needleQ;
	std::queue<Json::Value*> haysQ;

	needleQ.push(&needle);
	haysQ.push(&haystack);
	//optimize by using pairs?
	while (!needleQ.empty() && !haysQ.empty())
	{
		Json::Value* ne2 = needleQ.front();
		Json::Value* ha2 = haysQ.front();

		needleQ.pop();
		haysQ.pop();

		if (ne2->type() == Json::nullValue)
		{
			continue;
		}
		else if (ne2->type() != Json::objectValue)
		{
			if (*ne2 != *ha2)
			{
				return false;
			}
		}
		else
		{//is an object
			//push on the new data
			Json::Value::Members mem = needle.getMemberNames();

			for (const std::string& ss : mem)
			{
				if (!ha2->isMember(ss))
					return false;

				needleQ.push(&(*ne2)[ss]);
				haysQ.push(&(*ha2)[ss]);
			}
		}
	}

	return true;
}

//get member names of current needle object
//for each name, check what it is - 3 cases
//if its an object, push on the stack
//if its null, continue
//if its a val, check it

bool ContainsObject(const Json::Value& needle, const Json::Value& haystack)
{
	Json::Value::Members mem = needle.getMemberNames();

	bool f = true;

	for (const std::string& ss : mem)
	{
		if (needle[ss].type() == Json::objectValue)
		{
			//go deeper
			if (!haystack.isMember(ss))
				return false;

			f = ContainsObject(needle[ss], haystack[ss]);
			if (!f)
				return false;
		}
		else if (needle[ss].type() == Json::nullValue)
		{
			continue;
		}
		else
		{
			if (!haystack.isMember(ss) || haystack[ss] != needle[ss])
			{
				return false;
			}
		}
	}

	return true;
}


bool RetrieveEX(std::vector<std::vector<std::string>>& paths, Store& s)
{
	return true;
}


//this function will return a bool based on whether the store satisfies the conditions or not
//then check each path on the store.  if at any point not equal, break and return false
bool Retrieve(const Json::Value& obj, Store& s)
{
	Json::Value::Members mem = obj.getMemberNames();
	//optimize, try using member and find rather than string search
	for (const std::string& ss : mem)
	{
		if (s.json.isMember(ss))
		{
			Json::Value v = obj[ss];

			if (v.type() == Json::intValue || v.type() == Json::booleanValue || v.type() == Json::realValue
				|| v.type() == Json::uintValue || v.type() == Json::stringValue)
			{
				if (s.json[ss] != v)
					return false;
			}
			else if (v.type() == Json::nullValue)
			{
				continue;
			}
			else if (v.type() == Json::arrayValue)
			{
				if (!ContainsArrayEX(v,s,ss))
					return false;
			//	if (!ContainsArray(v, s.json[ss]))
			//		return false;
			}
			else if(v.type() == Json::objectValue)
			{
			//	if (!ContainsObject(v, s.json[ss]))
			//		return false;
				if (!ContainsObjectEX(v, s.json[ss]))
					return false;
			}
			else
			{ //bad type?
				return false;
			}

		}
		else
			return false;
	}
	return true;
}

using namespace std;
int main()
{
	std::string line;

	Json::CharReaderBuilder b;
	Json::CharReader * reader = b.newCharReader();

	const int HUGESIZE = 9000;
	int storeindex = 0;

	std::vector<Store> StoreOfData;
	Json::Value obj;
	std::unordered_set<std::string> addcache;
	std::unordered_map<std::string, std::string> getcache;


	while (std::getline(std::cin, line))
	{
		//parse input
		size_t index = line.find_first_of(' '); //kinda hackish fix later
		std::string command = line.substr(0, index);
		std::string thejson = line.substr(index + 1);
		std::string errors;
		bool parsingSuccessful = reader->parse(thejson.c_str(), thejson.c_str() + thejson.size(), &obj, &errors);

		if (command == "add")
		{
			//avoid duplicates
			if (addcache.find(thejson) != addcache.end())
			{
				continue;
			}

			addcache.insert(thejson);

			Store newstore;
			newstore.origString = thejson;
			newstore.json = obj;


			//for number lookup
			std::vector<std::string> mems = obj.getMemberNames();

			std::map<std::string, std::set<int>> theset;

			for (const std::string& s : mems)
			{
				std::set<int> t;
				if (obj[s].type() == Json::arrayValue)
				{
					for (Json::ArrayIndex i = 0; i < obj[s].size(); ++i)
					{
						t.insert(obj[s][i].asInt());
					}
				}
				theset.insert({ s,t });
			}
			newstore.lists = theset;
			//end number lookup
			StoreOfData.push_back(newstore);
			//StoreOfData[storeindex++] = newstore;
		}
		else
		{

			if (obj.type() == Json::nullValue)
			{
				for (long long i = 0; i < StoreOfData.size();/*storeindex;*/ ++i)
				{
						if (command == "get")
							std::cout << StoreOfData[i].origString << "\n";
						else if (command == "delete")
							StoreOfData[i].json.clear();
				}
				continue;
			}

			//first check cache
			if (command == "get")
			{
				if (getcache.find(thejson) != getcache.end())
				{
					std::cout << getcache[thejson] << "\n";
					continue;
				}
			}

			// get some data!
			// iterate through entire collection
			for (long long i = 0; i < StoreOfData.size()/*storeindex*/; ++i)
			{
				if (Retrieve(obj, StoreOfData[i]))
				{

					if (command == "get" && !StoreOfData[i].json.empty())
					{
						std::cout << StoreOfData[i].origString << "\n";
					}				
					else if (command == "delete")
					{
						StoreOfData[i].json.clear();
						getcache.clear();
					}
						
				}
			}
		}

	}

	return 0;
}

