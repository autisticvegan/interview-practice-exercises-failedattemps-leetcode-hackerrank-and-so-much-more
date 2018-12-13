#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iterator>
#include <istream>
#include <string>
#include <utility>


class CoinBaseInterviewHash
{
public:

	std::vector<std::pair<std::string,std::string>> store;
	bool usebadhash = true;

//WARNING NEED TO FIX - USE TOMBSTONE VALUES FOR DELETE NOT BLANK STRINGS

	std::string get(const std::string& key)
	{
		size_t spot = hash(key);

		if (spot >= store.size())
		{
			Grow();
			return "";
		}

		//need to look for the next one
		while (spot < store.size() && store[spot].first != key)
		{
			++spot;
		}

		if (spot == store.size())
		{
			Grow();
			return "";
		}
		
		return store[spot].second;


	}

	bool exists(const std::string& s)
	{
		return static_cast<bool>(get(s) != "");
	}

	void set(const std::string& k, const std::string& v)
	{
		//size_t s = findNext(k);

		size_t s = findCurr(k);

		if (store[s].first == k)
		{
			store[s].second = v;
			return;
		}

		size_t ss = findNext(k);
		//new one
		store[ss].first = k;
		store[ss].second = v;
	}

	void remove(const std::string& k)
	{
		size_t spot = findCurr(k);

		store[spot].first = "";
		store[spot].second = "";
	}

	size_t findCurr(const std::string& k)
	{
		size_t spot = hash(k);

		//if spot is outside bounds
		if (spot >= store.size())
		{
			Grow();
			return spot;
		}

		//spot is within bounds
		if (store[spot].first == k)
		{
			return spot;
		}

		//need to look for the next one
		while (spot < store.size() && store[spot].first != k)
		{
			++spot;
		}

		if (spot == store.size())
		{
			Grow();
		}

		//else found a spot
		return spot;

	}

	size_t findNext(const std::string& k)
	{
		size_t spot = hash(k);

		//if spot is outside bounds
		if (spot >= store.size())
		{
			Grow();
			return spot;
		}

		//spot is within bounds
		if (store[spot].first == "")
		{
			return spot;
		}
		
		//need to look for the next one
		while (spot < store.size() && store[spot].first != "")
		{
			++spot;
		}

		if (spot == store.size())
		{
			Grow();
		}

		//else found a spot
		return spot;

	}

	void Grow()
	{
		store.resize(10 + store.size() * 2);
	}

	size_t hash(const std::string& k)
	{
		if (usebadhash)
		{
			return badhash(k);
		}

		return goodhash(k);
	}

	size_t badhash(const std::string & g)
	{
		size_t sum = 0;

		for (int i = 0; i < g.size(); ++i)
		{
			sum += g[i];
		}

		return sum % g.length();
	}

	size_t goodhash(const std::string& g)
	{
		return std::hash<std::string>{}(g);
	}
};

int main(void)
{
	CoinBaseInterviewHash c;

	std::cout << c.get("0") << std::endl;

	std::cout << c.exists("t") << std::endl;

	std::cout << c.exists("onhteucoehurcoehuroechurcoe") << std::endl;

	c.set("t", "10");

	c.set("highasakite", "blazeit");

	std::cout << c.exists("highasakite") << std::endl;

	std::cout << c.get("highasakite") << std::endl;

	//set same thing
	c.set("highasakite", "t");

	std::cout << c.exists("highasakite") << std::endl;

	std::cout << c.get("highasakite") << std::endl;

	std::cout << c.get("t") << std::endl;

	//hash to same value
	//then check exists, get, exists old, get old
	//abc, cba

	c.set("abc", "COOL");
	c.set("bac", "NOT COOL");

	c.exists("abc");
	c.exists("bac");

	//remove, exists get, old
}