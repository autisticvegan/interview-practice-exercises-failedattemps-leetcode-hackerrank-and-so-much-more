#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <iomanip>


void tokenize(std::string& in, std::vector<std::string>& out, char delim) {
	std::stringstream s(in);
	std::string temp;
	while (std::getline(s, temp, delim)) {
		out.push_back(temp);
	}
}

double CalcFillPrice(int i, std::queue<std::pair<int, double>>& q) {
	
	double total = 0;
	std::vector<std::pair<int, double>> prices;
	int div = i;
	while (true) {
		
		int qA = q.front().first;

		if (i >= qA) {
			prices.push_back({ qA, q.front().second });
			i -= qA;
		}
		else {
			prices.push_back({ i, q.front().second });
			break;
		}
		q.pop();
	}
	
	for (const auto& p : prices) {
		total += p.first * p.second;
	}

	return total / div;
}

int main() {

	std::string line;
	std::queue<std::pair<int, double>> buyQ;
	std::queue < std::pair<int, double>> sellQ;
	std::vector<int> trades;

	int iter = 0;
	double remainder = 0;
	while (std::getline(std::cin, line)) {

		if (line == "" || line == "\n")
			break;

		std::vector<std::string> toks;
		tokenize(line, toks, ' ');

		if (iter < 2) {
		
			for (int i = 0; i < 6; i += 2) {
				
				if (iter == 0) {
					buyQ.push({ std::stoi(toks[i]), std::stod(toks[i + 1]) });
				}
				else {
					sellQ.push({ std::stoi(toks[i]), std::stod(toks[i + 1]) });
				}
			}

			++iter;
			continue;
		}

		
		double risk = std::stoi(toks[0]) * std::stod(toks[1]) * -1;
		double trueRisk = risk + remainder;
		double intpart;
		remainder = std::modf(trueRisk, &intpart);
		trades.push_back(static_cast<int>(trueRisk));
	}

	if (trades.size() > 0) {
		trades[trades.size() - 1] = static_cast<int>(std::round(trades[trades.size() - 1] + remainder));
	}

	for (const auto& i : trades) {

		double fillprice;
		if (i < 0) {
			fillprice = CalcFillPrice(i, sellQ);
		}
		else {
			fillprice = CalcFillPrice(i, buyQ);
		}

		std::cout << i << " " << std::fixed << std::setprecision(2) << fillprice << std::endl;
	}


	std::cin;
	return 0;
}