class Solution {
public:

	int largestValsFromLabels(vector<int>& vs, vector<int>& ls, int wanted, int limit, int res = 0) {

		std::multimap<int, int> s; //values to buckets
		std::unordered_map<int, int> m; //buckets to label count used

		for (auto i = 0; i < vs.size(); ++i) {
			s.insert({ vs[i], ls[i] });
		}

		for (auto it = std::rbegin(s); it != std::rend(s) && wanted > 0; ++it) {
			if (++m[it->second] <= limit) {
				res += it->first;
				--wanted;
			}
		}
		return res;

	}

	bool isValidCell(std::pair<long long, long long>& p) {
		return !(p.first < 0 || p.first > 999999 || p.second < 0 || p.second > 999999);
	}

	const std::vector<std::pair<int, int>> dirs{ {0,1}, {1,0}, {0,-1}, {-1,0} };

	bool bfs(std::set<std::pair<long long, long long>>& visited,
		std::pair<long long, long long> source,
		std::pair<long long, long long> target,
		long long blocks
	) {

		std::queue<std::pair<long long, long long>> q;
		q.push(source);
		while (!q.empty() && q.size() <= blocks) {

			auto p = q.front();
			q.pop();

			if (p == target) {
				return true;
			}

			//push spaces on
			for (int i = 0; i < 4; ++i) {
				// if its a valid space
				long long x = dirs[i].first + p.first;
				long long y = dirs[i].second + p.second;
				std::pair<long long, long long> g{ x,y };
				if (g == target)
					return true;

				if (isValidCell(g) && visited.count(g) == 0) {
					q.push(g);
					visited.insert(g);
				}

			}

		}

		return !q.empty();
	}

	bool within400Units(std::vector<int>& b, std::vector<int>& st) {
		return (std::abs(b[0] - st[0]) + std::abs(b[1] - st[1])) < 400;
	}

	bool isEscapePossible(std::vector<std::vector<int>>& blocked,
		std::vector<int>& source, std::vector<int>& target) {
		//idea, since number of blocked is small, just bfs outward for each block

		if (blocked.empty())
			return true;

		std::set<std::pair<long long, long long>> sourceSet;
		std::set<std::pair<long long, long long>> targetSet;

		for (auto& b : blocked) {

			//only if within 400 units
			if (within400Units(b, source)) {
				sourceSet.insert({ b[0], b[1] });
			}

			if (within400Units(b, target)) {
				targetSet.insert({ b[0], b[1] });
			}
		}

		return bfs(sourceSet, { source[0], source[1] }, { target[0], target[1] }, sourceSet.size()) &&
			bfs(targetSet, { target[0], target[1] }, { source[0], source[1] }, targetSet.size());
	}



};