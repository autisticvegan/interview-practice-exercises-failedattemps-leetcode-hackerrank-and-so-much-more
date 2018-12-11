#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <unordered_map>
#include <istream>
#include <iterator>
#include <iostream>
#include <cctype>
#include <sstream>
#include <deque>

class ListNode
{
public:
	ListNode* next;
};

int minPathSum(std::vector<std::vector<int>>& grid) {

	std::vector<std::vector<int>> dp(grid.size(), std::vector<int>(grid[0].size()));

	dp[0][0] = grid[0][0];

	for (int i = 1; i < grid.size(); ++i)
	{
		dp[i][0] = grid[i][0] + dp[i - 1][0];
	}

	for (int i = 1; i < grid[0].size(); ++i)
	{
		dp[0][i] = grid[0][i] + dp[0][i - 1];
	}

	for (int i = 1; i < grid.size(); ++i)
	{
		for (int j = 1; j < grid[i].size(); ++j)
		{
			dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}

	return dp[grid.size() - 1][grid[0].size() - 1];

}

ListNode* rotateRight(ListNode* head, int k) {

	if (!head)
		return head;

	ListNode* slow = head;
	ListNode* fast = head;

	int length = 0;
	while (slow)
	{
		++length;
		fast = slow;
		slow = slow->next;
	}

	k %= length;

	fast->next = head;

	int dist = length - k;

	int count = 1;
	slow = head;
	while (count < dist)
	{
		++count;
		slow = slow->next;
	}

	head = slow->next;
	slow->next = nullptr;
	return head;
}

std::string getPermutation(int n, int k) {

	std::string thestring;
	for (int i = 1; i <= n; ++i)
	{
		thestring.push_back(i + '0');
	}

	int count = 1;

	while (count < k)
	{
		++count;
		std::next_permutation(thestring.begin(), thestring.end());
	}


	return thestring;

}
class Solution {
public:

	std::vector<std::string> split(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	std::string validIPAddress(std::string IP)
	{
		size_t in = IP.find_first_of(":.");

		if (in == std::string::npos)
		{
			return "Neither";
		}

		//check max length
		//check leading zeros
		//check valid numbers (hex or dec)

		size_t dcheck = IP.find_first_of('-');
		if (dcheck != std::string::npos)
			return "Neither";

		if (IP[in] == ':')
		{
			//ipv6
			std::vector<std::string> toks = split(IP, ':');

			if (toks.size() != 8)
				return "Neither";

			int length = 0;
			for (const std::string& s : toks)
			{
				if (s.length() > 4)
					return "Neither";

				if (s.empty())
					return "Neither";

				char* p;
				long n = strtoul(s.c_str(), &p, 16);

				if (*p != 0)
				{
					return "Neither";
				}
				else
				{
					if (n > 65535)
						return "Neither";
				}

				length += s.length();
			}

			if (length + 7 != IP.length())
				return "Neither";

			return "IPv6";
		}
		else
		{//ipv4

			std::vector<std::string> toks = split(IP, '.');

			if (toks.size() != 4)
				return "Neither";


			int length = 0;
			for (const std::string& s : toks)
			{
				if (s.length() > 3)
					return "Neither";

				if (s.empty())
					return "Neither";

				size_t allz = s.find_first_not_of('0');

				if (allz != std::string::npos && allz > 0)
				{//there are non zeros
					for (int i = 0; i < allz; ++i)
					{
						if (s[i] == '0')
							return "Neither";
					}
				}
				else if (allz == std::string::npos)
				{
					if (s.length() > 1)
						return "Neither";
				}

				if (!is_number(s))
					return "Neither";

				int t = std::stoi(s);

				if (t > 255)
					return "Neither";

				length += s.length();
			}

			if (length + 3 != IP.length())
				return "Neither";

			return "IPv4";
		}
	}


	bool is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
};


template<int count, char delim, decltype(std::dec) mode, int maxZeroCount, int maxNum>
static bool verify(std::string IP) {
	std::istringstream iss(IP += delim);
	int num; char c;
	for (int i = 0, pos; pos = iss.tellg(), i < count; ++i) {
		auto start0 = iss.peek() == '0';
		iss >> mode >> num >> c;
		if (iss.fail())
			return false;

		int t = iss.tellg();
		t -= pos;

		if (start0 && (t > 1 + maxZeroCount))
			return false;

		if (c != delim)
			return false;

		if (num > maxNum)
			return false;

	}
	return iss.peek() == EOF;
}

std::string validIPAddressEX(std::string IP) {
	if (IP.find_first_of('-') != std::string::npos) return "Neither";
	auto isIPv4 = verify<4, '.', std::dec, 1, 0xFF>;
	auto isIPv6 = verify<8, ':', std::hex, 4, 0xFFFF>;
	return isIPv4(IP) ? "IPv4" : isIPv6(IP) ? "IPv6" : "Neither";
}


int main(void)
{
	validIPAddress("2001:db8:85a3:0::8a2E:0370:7334");




	return 0;
}