#include <string>
#include <random>
#include <chrono>
#include <iterator>
#include <iostream>
#include <algorithm>

//silly string timing tests

int main(void)
{
	std::string t;
	std::string s;

	char c = 'd';

	auto t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10000000; ++i)
	{
		t += c;
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "f() took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n\n";

	t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10000000; ++i)
	{

		s.push_back(c);
	}

	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "f() took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n\n";


	std::string o;
	std::string g;
	std::string finall;
	finall.resize(10000000);
	o.reserve(100000000);
	g.reserve(100000000);
	t1 = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < 10000000; ++i)
	{

		o.push_back(c);
	}

	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "f() took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n\n";

	t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10000000; ++i)
	{

		g += c;
	}

	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "f() took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n\n";


	t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10000000; ++i)
	{

		finall[i] = c;
	}

	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "f() took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n\n";


	return 0;
}