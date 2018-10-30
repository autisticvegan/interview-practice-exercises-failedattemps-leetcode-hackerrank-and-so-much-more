#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
//this removes the .'s in the front part, and removes everything from + forward
std::string FormatEmail(std::string& e)
{
	size_t index = e.find_first_of('@');


	//now index is @
	std::string subo = e.substr(0, index);

	size_t pupu = subo.find_first_of('+');

	std::string finalo;

	if (pupu != std::string::npos) //if there was a +
	{
		finalo = subo.substr(0, pupu );
	}
	else
	{
		finalo = subo;
	}

	finalo.erase(std::remove(finalo.begin(), finalo.end(), '.'), finalo.end());

	return finalo + e.substr(index, e.length() - index);
}


//take a sentence, either rotate words left or right
std::string RotateWords(std::string& sentence, bool goleft, int amount)
{
	std::string res;;

	//array of words, rotate the array
	std::istringstream is(sentence);
	std::vector<std::string> input{ std::istream_iterator<std::string>{is},std::istream_iterator<std::string>{} };

	//std::rotate

	if (goleft)
	{
		std::rotate(input.begin(), input.begin() + amount, input.end());
	}
	else //go right
	{//obviously unsafe, but assume user knows what they are doing
		std::rotate(input.begin(), input.begin() + input.size() - amount, input.end());
	}


	for (std::string& u : input)
	{
		res += u;
		res += " ";
	}

	res.erase(res.begin() + res.length() - 1, res.end());

	return res;
}

std::string r(std::string& a)
{
	for (int i = 0; i < a.length()/2; ++i)
	{
		std::swap(a[i], a[a.length() - i - 1]);
	}

	return a;
}

void ReverseWords(std::string& rev)
{
	//cheater way lol
	std::string::iterator begin = rev.begin();
	std::string::iterator end = rev.begin();

	//clean out front
	while (end != rev.end() && *end == ' ')
		++end;

	while (end != rev.end())
	{
		//we hit a space, need to reverse
		if (*end == ' ')
		{
			std::reverse(begin, end);
			
			while (end != rev.end() && *end == ' ')
			{
				++end;
			}

				if (end == rev.end())
				{
					return;
				}
				else
				{
					begin = end;
				}
		}

		++end;
	}

	std::reverse(begin, end);


	return;

}


int main(void)
{
	std::vector<std::string> g;
	g.push_back("ahoeu+hoeu@a.com");
	g.push_back("ahoeu@a.com");
	g.push_back("a.y.u.@pp.com");
	g.push_back("ayu@pp.com");
	g.push_back("a.@pp.com");
	g.push_back("a+@pp.com");

	std::unordered_set<std::string> FOAD;

	for (std::string& p : g)
	{
		FOAD.insert(FormatEmail(p));
	}

	std::string dookie = "hello";
	std::string d = r(dookie);

	std::string eri = "The big green frog";
	std::string donkey = "        uwu  toilets    ";

	ReverseWords(eri);
	ReverseWords(donkey);
	std::string h = "";
	std::string ho = "  ";
	ReverseWords(h);
	ReverseWords(ho);
	ReverseWords(eri);

	std::string news = RotateWords(eri, true, 1);
	std::string po = RotateWords(eri, false, 2);

	return 0;
}