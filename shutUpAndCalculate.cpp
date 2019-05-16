#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <functional>
#include <stack>
#include <deque>
#include <sstream>
#include <istream>
#include <iostream>

std::string simplifyPath(std::string path) {
	//idea, use deque-4 cases-
	// "" and "." -> continue
	// ".." -> get the last item on deq
	// anything else -> add to deq
	// push them on the back
	// then when printing out, go from front to back


	// can also use just a stack
	// and when printing, just put / + .top + currRes

	std::deque<std::string> dirs;
	std::string result;
	std::string tmp;

	std::istringstream ss(path);

	while (std::getline(ss, tmp, '/')) {

		if (tmp == "" || tmp == ".") {
			continue;
		}
		else if (tmp == "..") {
			if (!dirs.empty()) {
				dirs.pop_back();
			}
			else {
				// error happened!
			}
		}
		else {
			dirs.push_back(tmp);
		}
	}

	if (dirs.empty())
		return "/";

	for (const auto& s : dirs) {
		result += "/" + s;
	}
	return result;

}


int evalRPN(std::vector<std::string>& tokens) {
	//idea: use a stack
	//cool idea: use a unordered map of
	//op to function (lamda) (as in, string)
	// function<int (int, int)> 
	// could also be char but we are leaving it
	// as string because its given to us as strings


	std::unordered_map<std::string,
		std::function<int(int, int)>> operation2FunctionMap = {
			{"+", [](int a, int b) {return a + b; }},
			{"-", [](int a, int b) {return a - b; }},
			{"*", [](int a, int b) {return a * b; }},
			{"/", [](int a, int b) {return a / b; }}
	};


	std::stack<int> result;

	for (auto& t : tokens) {
		if (operation2FunctionMap.count(t) == 0) {
			result.push(std::stoi(t));
		}
		else {

			int operand1 = result.top();
			result.pop();

			int operand2 = result.top();
			result.pop();

			// warning-watch out you might think
			// this is backwards
			result.push(
				operation2FunctionMap[t](operand2,
					operand1));
		}
	}

	return result.top();
}

void helper(std::vector<std::string>& res, int index,
	std::vector<int>& currIP, std::string& s,
	int segment) {

	if (segment == 4 && index == s.length()) {
		std::string t = std::to_string(currIP[0]) + "." +
			std::to_string(currIP[1]) + "." +
			std::to_string(currIP[2]) + "." +
			std::to_string(currIP[3]);
		res.push_back(t);
	}
	else if (segment == 4 || index == s.length()) {
		return;
	}

	for (int len = 1; len < 4 && (len + index < s.length()); ++len) {

		int currVal = std::stoi(s.substr(index, len));

		// 2 conditions to check, greater than 255,
		// or starts with a 0 (to check this,
		// check the string and make sure longer than 1)
		if (currVal > 255 || (len > 1 && s[index] == '0')) {
			break;
		}

		currIP[segment] = currVal;
		helper(res, index + len, currIP, s, segment + 1);
		currIP[segment] = -1;

	}
}

//constraints:
// not a leading zero
// greatest number is 255
// 4 subsections

std::vector<std::string> restoreIpAddresses(std::string s) {
	std::vector<std::string> result;
	std::vector<int> currIP;
	helper(result, 0, currIP, s);
	return result;
}

void helper(std::vector<std::string>& res, int index,
	std::vector<int>& currIP, std::string& s) {

	if (currIP.size() == 4 && index == s.length()) {
		std::string t = std::to_string(currIP[0]) + "." +
			std::to_string(currIP[1]) + "." +
			std::to_string(currIP[2]) + "." +
			std::to_string(currIP[3]);
		res.push_back(t);
	}
	else if (currIP.size() == 4 || index == s.length()) {
		return;
	}

	for (int len = 1; len < 4 && (len + index <= s.length()); ++len) {

		int currVal = std::stoi(s.substr(index, len));

		// 2 conditions to check, greater than 255,
		// or starts with a 0 (to check this,
		// check the string and make sure longer than 1)
		if (currVal > 255 || (len > 1 && s[index] == '0')) {
			break;
		}

		currIP.push_back(currVal);
		helper(res, index + len, currIP, s);
		currIP.pop_back();
	}
}
int main(void) {
	restoreIpAddresses("25525511135");
	return 0;
}