
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>

#include <map>
#include <sstream>

class node {
public:
	std::string symbol = "NA";
	double exchangeRatio = -1;
	bool operator<(const node& r) const {
		return r.exchangeRatio < this->exchangeRatio;
	}
};


void FindBestPath(std::map<std::string, std::vector<node>>& nodeMap,
	std::unordered_set<std::string> visited,
	std::vector<std::pair<std::vector<node>, int>>& paths,
	std::vector<node> currentPath,
	node start,
	node target,
	double amount,
	bool firstIteration
) {

	if (visited.count(start.symbol)) {
		return;
	}

	visited.insert(start.symbol);

	double calculatedAmount = amount;
	if (!firstIteration)
		calculatedAmount = start.exchangeRatio * amount;

	currentPath.push_back(start);


	if (start.symbol == target.symbol) {
		paths.push_back({ currentPath, calculatedAmount });
		currentPath.clear();
		return;
	}


	// for each node, get exchange rate, and use calcAmount for amount.
	for (auto& p : nodeMap[start.symbol]) {
		FindBestPath(nodeMap, visited, paths, currentPath, p, target, calculatedAmount, false);
	}
}

void PrintAllPaths(std::map<std::string, std::vector<node>>& nodeMap,
	std::unordered_set<std::string> visited,
	std::vector<node> currentPath,
	node start,
	node target) {

		if (visited.count(start.symbol)) {
		return;
	}

	visited.insert(start.symbol);
	currentPath.push_back(start);

	if (start.symbol == target.symbol) {
		std::cout << std::endl;
		for (const auto& v : currentPath) {
			std::cout << v.symbol << " ";
		}
		std::cout << std::endl;
		return;
	}

	

	// for each node, get exchange rate, and use calcAmount for amount.
	for (auto& p : nodeMap[start.symbol]) {
		PrintAllPaths(nodeMap, visited, currentPath, p, target);
	}

}

int main(void) {

	std::map<std::string, std::vector<node>> nodeMap;

	node btc;
	btc.symbol = "BTC";
	std::vector<node> btcNodes;

	node usd;
	usd.symbol = "USD";
	std::vector<node> usdNodes;

	node eth;
	eth.symbol = "ETH";
	std::vector<node> ethNodes;

	node eur;
	eur.symbol = "EUR";
	std::vector<node> eurNodes;


	/*
	node xrp;
	xrp.symbol = "XRP";
	std::vector<node> xrpNodes;



	node yen;
	yen.symbol = "YEN";

	std::vector<node> yenNodes;

	/*

	
	xrp.exchangeRatio = .69;
	yenNodes.push_back(xrp);

		btc.exchangeRatio = .00005;
	usd.exchangeRatio = 2;
	eth.exchangeRatio = .001;
	xrpNodes.push_back(btc);
	xrpNodes.push_back(usd);
	xrpNodes.push_back(eth);

	*/



	eth.exchangeRatio = 10;
	//xrp.exchangeRatio = 50000;
	eur.exchangeRatio = 6000;
	usd.exchangeRatio = 7000;
	btcNodes.push_back(eth);
	//btcNodes.push_back(xrp);
	btcNodes.push_back(eur);
	//btcNodes.push_back(usd);

	//xrp.exchangeRatio = 1000;
	eur.exchangeRatio = 400;
	usd.exchangeRatio = 500;
//	ethNodes.push_back(xrp);
	ethNodes.push_back(eur);
	ethNodes.push_back(usd);

	/*
		USD 7000 1 BTC  BTC 1 6000 EUR
	USD  300 1 ETH  ETH 1 400 EUR
	*/

	eth.exchangeRatio = 1.0 / 300;
	btc.exchangeRatio = 0.00014285714;
//	xrp.exchangeRatio = 2;
	eur.exchangeRatio = .9;
	usdNodes.push_back(eth);
	usdNodes.push_back(btc);
//	usdNodes.push_back(eur);


	btc.exchangeRatio = .0007;
//	usd.exchangeRatio = .0008;
	eth.exchangeRatio = .01;
	eurNodes.push_back(btc);
//	eurNodes.push_back(usd);
	eurNodes.push_back(eth);

	nodeMap.insert({ btc.symbol, btcNodes });
	nodeMap.insert({ eth.symbol, ethNodes });
	nodeMap.insert({ usd.symbol, usdNodes });
	nodeMap.insert({ eur.symbol, eurNodes });
	//nodeMap.insert({ yen, yenNodes });
	//nodeMap.insert({ xrp, xrpNodes });

	std::vector<std::pair<std::vector<node>, int>> paths;
	std::vector<node> currPath;
	int finalAmount = 0;
	std::unordered_set<std::string> visited;
	node start = usd;
	node target = eur;

	PrintAllPaths(nodeMap, visited, currPath, start, target);

	visited.clear();
	currPath.clear();

	std::cout << "Finding best path...\n\n";

	FindBestPath(nodeMap, visited, paths, currPath, start, target, 1000, true);

	std::vector<node> bestPath;
	for (const auto & p : paths) {
		if (p.second > finalAmount) {
			bestPath = p.first;
			finalAmount = p.second;
		}
	}
	std::cout << "The best amount, " << finalAmount << " with the path is: " << std::endl;
	for (const auto& v : bestPath) {
		std::cout << v.symbol << " ";
	}
	std::cout << std::endl;

	return 0;
}