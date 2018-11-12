#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <queue>

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {

	std::sort(nums.begin(), nums.end());

	//need dic, key = sum of 2 numbers, val is any 2 numbers that add up to that sum

	std::map<int, std::set<std::pair<int,int>>> dic;

	std::set<std::vector<int>> res;

	int n = nums.size();

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			int sum = nums[i] + nums[j];

			for (std::pair<int, int> p : dic[target - sum])
			{
				std::vector<int> v(4);
				v[0] = p.first;
				v[1] = p.second;
				v[2] = nums[i];
				v[3] = nums[j];

				res.insert(v);
				//results.push_back(v);
			}
		}

		for (int k = 0; k < i; ++k)
		{
			if (dic.count(nums[i] + nums[k]))
			{
				dic[nums[i] + nums[k]].insert({ nums[i],nums[k] });
			}
			else
			{
				std::set<std::pair<int, int>> s;
				s.insert({ nums[i],nums[k] });
				dic.insert({ nums[i] + nums[k], s });
			}
		}
	}

	std::vector<std::vector<int>> results(res.size());
	auto it = res.begin();
	for (int i = 0; i < res.size(); ++i)
	{
		results[i] = *it;
		++it;
	}

	return results;

}

int main(void)
{
	std::vector<int> nums = { -3, -2, -1, 0, 0, 1, 2, 3 };
		int	target = 0;
		fourSum(nums, target);
	return 0;
}

/*
import collections

def fourSum(nums, target):
		"""
		:type nums: List[int]
		:type target: int
		:rtype: List[List[int]]
		"""

		nums.sort()
		dic = collections.defaultdict(set)
		res = set()
		n = len(nums)

		for i in range(n):
			for j in range(i + 1, n):
				sum = nums[i] + nums[j]
				for half in dic[target - sum]:
					res.add(tuple(list(half) + [nums[i], nums[j]]))

			for k in range(i):
				dic[nums[i] + nums[k]].add((nums[k], nums[i]))

		return list(res)


def main():
	nums = [-3,-2,-1,0,0,1,2,3]
	target = 0
	fourSum(nums,target)

if __name__ == "__main__":
	main()*/