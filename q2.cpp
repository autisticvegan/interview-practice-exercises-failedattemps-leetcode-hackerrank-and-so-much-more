#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
/*
double findPrice(std::map<std::string, std::pair<std::set<std::string>, double>>& mapping, std::string ing) {

	if (mapping[ing].first.empty()) {
		return mapping[ing].second;
	}

	double sumPrice = 0;

	for (const auto& a : mapping[ing].first) {
		sumPrice += findPrice(mapping, a);
	}

	return std::min(mapping[ing].second, sumPrice);
}


void tokenize(std::string& in, std::vector<std::string>& out, char delim) {
	std::stringstream s(in);
	std::string temp;
	while (std::getline(s, temp, delim)) {
		out.push_back(temp);
	}
}

int main() {

	std::string line;
	std::string target;
	std::map<std::string, std::pair<std::set<std::string>, double>> mapping;
	int iter = 0;
	while (std::getline(std::cin, line)) {

		if (iter == 0) {
			target = line;
			++iter;
			continue;
		}
		
		std::vector<std::string> tokens;
		tokenize(line, tokens, ',');

		std::set<std::string> s;
		if (tokens.size() == 4 && !tokens[3].empty()) {
			std::vector<std::string> ings;
			tokenize(tokens[3], ings, ';');
			
			for (const auto& g : ings) {
				if (g != "") 
					s.insert(g);
			}
		}
		std::pair<std::set<std::string>, double> p;
		p.first = s;
		if (tokens[1] != "") {
			p.second = std::stod(tokens[1]);
		}
		else {
			target = tokens[0];
			p.second = INT_MAX;
		}

		mapping.insert({ tokens[0], p });
	}

	std::cout << findPrice(mapping, target) << std::endl;

	return 0;
}
*/