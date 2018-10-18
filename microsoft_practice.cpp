#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <cstdio>
#include <iterator>
#include <functional>
#include <cmath>
#include <map>
#include <sstream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


std::vector<int> GetKSmallest(std::vector<int>& input, int amount)
{
	std::priority_queue<int, std::vector<int>, std::less<int>> maxheap;

	for (int i = 0; i < amount; ++i)
	{
		maxheap.push(input[i]);
	}

	for (int i = amount; i < input.size(); ++i)
	{
		if (maxheap.top() > input[i])
		{
			maxheap.pop();
			maxheap.push(input[i]);
		}
	}

	std::vector<int> result;
	while (!maxheap.empty())
	{
		result.push_back(maxheap.top());
		maxheap.pop();
	}


	std::cout << "Get Smallest\n";
	for (int i = 0; i < input.size(); ++i)
	{
		std::cout << input[i] << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < result.size(); ++i)
	{
		std::cout << result[i] << " ";
	}

	return result;
}

struct TreeNode {
	int data;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : data(x), left(NULL), right(NULL) {}
	
};

bool helperCheckIfBST(TreeNode* root, TreeNode* min, TreeNode* max)
{
	if (!root)
		return true;


	if ((min && root->data >= min->data) || (max && root->data <= max->data))
		return false;

	return helperCheckIfBST(root->left, root, max) && helperCheckIfBST(root->right, min, root);
}

bool CheckIfBST(TreeNode* root)
{
	return helperCheckIfBST(root, nullptr, nullptr);
	//bad approach helperCheckIfBST(root, INT_MIN, INT_MAX);
}

std::vector<int> GetKBiggest(std::vector<int>& input, int amount)
{
	std::priority_queue<int, std::vector<int>, std::greater<int>> minheap;

	for (int i = 0; i < amount; ++i)
	{
		minheap.push(input[i]);
	}

	for (int i = amount; i < input.size(); ++i)
	{
		if (minheap.top() < input[i])
		{
			minheap.pop();
			minheap.push(input[i]);
		}
	}

	std::vector<int> result;
	while (!minheap.empty())
	{
		result.push_back(minheap.top());
		minheap.pop();
	}


	std::cout << "Get Biggest\n";
	for (int i = 0; i < input.size(); ++i)
	{
		std::cout << input[i] << " ";
	}
	std::cout << "\n";
		
	for (int i = 0; i < result.size(); ++i)
	{
		std::cout << result[i] << " ";
	}

	return result;
}

std::vector<int> GenerateData(int length)
{
	std::vector<int> result;

	for (int i = 0; i < length; ++i)
	{
		result.push_back(std::rand() % 100);
	}


	return result;
}


void RotateArray(std::vector<int> num, int k)
{
	//print
	std::cout << "Rotate Array\n";

	for (int i = 0; i < num.size(); ++i)
	{
		std::cout << num[i] << " ";
	}
	std::cout << "\n";

	//method 1: //use standard for left, for right use rbegin etc.
//	std::rotate(num.begin(), num.begin() + k, num.end());

	if (k < 0)
	{
		k = num.size() + k;
	}

		std::reverse(num.begin(), num.begin() + num.size() - k);
		std::reverse(num.begin() + num.size()-k, num.end());
		std::reverse(num.begin(), num.end());

	//method 2:



	for (int i = 0; i < num.size(); ++i)
	{
		std::cout << num[i] << " ";
	}
	std::cout << "\n";
}

void ReverseArray(std::vector<int> arr)
{
	std::cout << "Reverse Array\n";

	for (int i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";


	for (int i = 0; i < arr.size() / 2; ++i)
	{
		std::swap(arr[i], arr[arr.size() - 1 - i]);
	}


	for (int i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";

}

void twosum(std::vector<int>& a, int target)
{
	std::unordered_map<int, int> b;

	for (int i = 0; i < a.size(); ++i)
	{
		int val = target - a[i];

		if (b.count(val))
		{
			std::cout << b[val] << " " << i << "\n";
		}
		else
		{
			b[a[i]] = i;
		}
	}
}













void ReverseWordsInString(std::string s)
{
	
		std::string::iterator word_begin = s.begin();
		std::string::iterator temp = s.begin(); /* temp is for word boundry */

		while (*temp == ' ' && temp != s.end())
			++temp;

		while (temp != s.end())
		{
			if (*temp == ' ')
			{
				
				std::reverse(word_begin, temp);

				while (*temp == ' ' && temp != s.end())
				{
					++temp;
				}

				if (temp == s.end())
				{
					return;
				}
				else
				{
					word_begin = temp;
				}
				
			}

			++temp;
		}
		
		std::reverse(word_begin, temp);

		std::cout << "string is now \n";
		std::cout << s << "\n";
}

void MergeUnderscores(std::string lol)
{
	std::cout << lol << "\n";
	std::string res;
	for (int i = 0; i < lol.length(); ++i)
	{
		if (lol[i] == '_')
		{
			res += lol[i];
			while (lol[i] == '_' && i < lol.length())
			{
				++i;
			}
			res += lol[i];
		}
		else
		{
			res += lol[i];
		}
	}
	
	std::cout << res << "\n";
}

template <typename BidirIt, typename Compare = std::less<>>
void MergeSort(BidirIt first, BidirIt last, Compare cmp = Compare{})
{
	size_t dist = std::distance(first, last);

	if (dist > 1)
	{
		auto mid = std::next(first, dist / 2);

		MergeSort(first, mid, cmp);
		MergeSort(mid, last, cmp);

		std::inplace_merge(first, mid, last, cmp);
	}
}

void Merge2ListsIterative(ListNode* a, ListNode* b)
{
	//error checking

	ListNode* head;

	if (a->val < b->val)
	{
		head = a;
		a = a->next;
	}
	else
	{
		head = b;
		b = b->next;
	}
	ListNode* curr = head;
	while (a && b)
	{
		int x = 0;
		if (a->val < b->val)
		{
			x = a->val;
			a = a->next;
		}
		else
		{
			x = b->val;
			b = b->next;
		}

		ListNode* newnode = new ListNode(x);
		curr->next = newnode;
		curr = curr->next;
	}
	//
	if (!a && b)
	{
		curr->next = b;
	}

	if (!b && a)
	{
		curr->next = a;
	}


	//print, return
}


std::vector<int> SpiralMatrixOutIn(std::vector<std::vector<int>>& input)
{
	std::vector<int> res;

	int dir = 0;
	int x = 0;
	int y = 0;

	int count = 1;
	int steps = input.size();
	bool running = true;
	int timetoupdatesteps = 0;
	int endpoint = steps * steps;
	bool firstTimeSteps = true; //need this for the first 3, then its always 2

	res.push_back(input[0][0]);

	while (running)
	{
		switch (dir)
		{
		case 0:
			for (int i = 1; i < steps; ++i)
			{
				res.push_back(input[y][x+i]);
				if (res.size() == endpoint)
				{
					running = false;
					break;
				}
			}

			x += steps - 1;
			break;

		case 1:
			for (int i = 1; i < steps; ++i)
			{
				res.push_back(input[y + i][x]);
				if (res.size() == endpoint)
				{
					running = false;
					break;
				}
			}
			y += steps - 1;
			break;

		case 2:
			for (int i = 1; i < steps; ++i)
			{
				res.push_back(input[y][x-i]);
				if (res.size() == endpoint)
				{
					running = false;
					break;
				}
			}

			x -= steps - 1;
			break;

		case 3:
			for (int i = 1; i < steps; ++i)
			{
				res.push_back(input[y - i][x]);
				if (res.size() == endpoint)
				{
					running = false;
					break;
				}
			}
			y -= steps - 1;
			break;


		}

		++timetoupdatesteps;

		if (timetoupdatesteps == 3 && firstTimeSteps)
		{
			firstTimeSteps = false;
			--steps;
			timetoupdatesteps = 0;
		}

		if (timetoupdatesteps == 2 && !firstTimeSteps)
		{
			--steps;
			timetoupdatesteps = 0;
		}

		++dir;
		dir %= 4;
	}



	return res;
}

std::vector<std::vector<int>> GenerateMatrixAcc(int n)
{
	std::vector<std::vector<int>> res(n, std::vector<int>(n));

	int dir = 0;
	int x = 0;
	int y = 0;

	int count = 1;
	int steps = n;
	bool running = true;
	int timetoupdatesteps = 0;
	int endpoint = n * n;
	bool firstTimeSteps = true; //need this for the first 3, then its always 2

	res[y][x] = 1;

	while (running)
	{
		switch (dir)
		{
		case 0:
			for (int i = 1; i < steps; ++i)
			{
				res[y][x + i] = ++count;
				if (count == endpoint)
				{
					running = false;
					break;
				}
			}

			x += steps - 1;
			break;

		case 1:
			for (int i = 1; i < steps; ++i)
			{
				res[y + i][x] = ++count;
				if (count == endpoint)
				{
					running = false;
					break;
				}
			}
			y += steps - 1;
			break;

		case 2:
			for (int i = 1; i < steps; ++i)
			{
				res[y][x - i] = ++count;
				if (count == endpoint)
				{
					running = false;
					break;
				}
			}

			x -= steps - 1;
			break;

		case 3:
			for (int i = 1; i < steps; ++i)
			{
				res[y - i][x] = ++count;
				if (count == endpoint)
				{
					running = false;
					break;
				}
			}
			y -= steps - 1;
			break;


		}

		++timetoupdatesteps;

		if (timetoupdatesteps == 3 && firstTimeSteps)
		{
			firstTimeSteps = false;
			--steps;
			timetoupdatesteps = 0;
		}

		if (timetoupdatesteps == 2 && !firstTimeSteps)
		{
			--steps;
			timetoupdatesteps = 0;
		}

		++dir;
		dir %= 4;
	}



	return res;
}

/* subarray sum
private int subarraySum(int[] arr) {
int result = 0;
for (int i = 0; i < arr.length; i++) {
result += arr[i] * (i + 1) * (arr.length - i);
}
return result;
}*/

std::vector<int> SpiralMatrixInOut(std::vector<std::vector<int>>& input)
{
	//get middle of matrix
	int start = input.size() / 2;
	std::vector<int> result;
	if (input.size() % 2 == 0)
		--start;

	//dir 0,1,2,3

	int dir = 0;
	int x = start;
	int y = start;
	result.push_back(input[y][x]);
	int steps = 2;
	bool running = true;
	int timetoupdatesteps = 0;
	while (running)
	{
		switch (dir)
		{
		case 0:
			for (int i = 1; i < steps; ++i)
			{
				if ((y >= input.size()) || ((x + i) >= input[y].size()))
				{
					running = false;
					break;
				}
				result.push_back(input[y][x+i]);
			}

			x += steps - 1;
			break;

		case 1:
			for (int i = 1; i < steps; ++i)
			{
				if ((y+i >= input.size()) || (x >= input[y+i].size()))
				{
					running = false;
					break;
				}
				result.push_back(input[y+i][x]);
			}
			y += steps - 1;
			break;

		case 2:
for (int i = 1; i < steps; ++i)
{
	if ((y >= input.size()) || ((x - i) < 0))
	{
		running = false;
		break;
	}
	result.push_back(input[y][x - i]);
}

x -= steps - 1;
break;

		case 3:
			for (int i = 1; i < steps; ++i)
			{
				if ((y - i < 0) || (x >= input[y - i].size()))
				{
					running = false;
					break;
				}
				result.push_back(input[y - i][x]);
			}
			y -= steps - 1;
			break;


		}

		++timetoupdatesteps;

		if (timetoupdatesteps == 2)
		{
			++steps;
			timetoupdatesteps = 0;
		}

		++dir;
		dir %= 4;
	}
	//go right

	//go down

	//go left

	//go up
	return result;
}

void SetColumnAndRowTo0(std::vector<std::vector<int>>& input, int col, int row)
{
	//row
	for (int i = 0; i < input.size(); ++i)
	{
		input[i][col] = 0;
	}


	//col
	for (int i = 0; i < input[row].size(); ++i)
	{
		input[row][i] = 0;
	}
}

constexpr int fib(const int i)
{
	const auto sqrt_5 = std::sqrt(5);

	if (i == 0) return 0;
	if (i == 1) return 1;

	return static_cast<int>(std::round((std::pow(1 + sqrt_5, i) - std::pow(1 - sqrt_5, i)) / (std::pow(2, i) * sqrt_5)));
}

std::vector<std::vector<int>> generateMatrix(int n)
{
	std::vector<std::vector<int>> res;
	for (int i = 0; i < n; ++i)
	{
		std::vector<int> a;
		res.push_back(a);
		for (int j = 0; j < n; ++j)
		{
			res[i].push_back(i*n + j);
		}
	}

	return res;
}


std::string LongestPalindromicSubstring(std::string s)
{

}

int main(void)
{

std::vector<int> input = GenerateData(5);

ReverseArray(input);

RotateArray(input, 2);
RotateArray(input, -2);
	
std::cout << "\n";
GetKBiggest(input, 2);
std::cout << "\n";
GetKSmallest(input, 2);
std::cout << "\n";

MergeUnderscores("u_____________poop __ pee _e _____ gas____________");
std::cout << "\n";

std::string oeu = "oeu           u .";

ReverseWordsInString(oeu);

std::vector<int> input2 = GenerateData(6);

std::cout << "before merge sort:\n";
for (int i = 0; i < input2.size(); ++i)
	std::cout << input2[i] << " ";

	std::cout << "\n";

MergeSort(input2.begin(), input2.end());

std::cout << "\n";

std::cout << "after merge sort:\n";
for (int i = 0; i < input2.size(); ++i)
	std::cout << input2[i] << " ";

std::cout << "\n";


	SpiralMatrixInOut(generateMatrix(3));
	GenerateMatrixAcc(3);

	return 0;
}

struct record
{
public:
	int hostid;
	int listid;
	float score;
	std::string city;

	bool operator < (const record& rec) const
	{
		return (score < rec.score);
	}
}; 

struct sortbyFirstHost
{
	inline bool operator() (const std::vector<record>& r1, const std::vector<record>& r2)
	{
		if (r1.empty() || r2.empty())
			return false;

		return (r1[0].score < r2[0].score);
	}
};

std::string BuildString(record r)
{
	std::string ret;
	
	std::stringstream ss;
	ss << r.hostid;
	ss << ",";
	ss << r.listid;
	ss << ",";
	ss << r.score;
	ss << ",";
	ss << r.city;
	return ss.str();

	return ret;
}

std::vector <std::string> paginate(int num, std::vector <std::string> results) {

	std::vector<std::string> res;

	/*
	map: hostid -> vector of records (sorted by score)


	iterate over hosts, insert into map along with string

for each host, sort scores vector

for each page:
  
  print unique hosts (evertime we print, delete that so we dont print again)
  count number printed
  
  if(number printed < page length)
    add non unique hosts
  
*/
	std::map<int, std::vector<record>, sortbyFirstHost()>  Data;

	std::vector<std::vector<record>> actualData;

	for (std::string a : results)
	{
		//parse each record 
		int hostid;
		int listid;
		float score;
		std::string city;

		record insertthis;

		std::istringstream ss(a);
		std::string temptoken;
		int index = 0;

		while (std::getline(ss, temptoken, ','))
		{
			if (index == 0)
			{
				hostid = std::stoi(temptoken);
			}
			else if (index == 1)
			{
				listid = std::stoi(temptoken);
			}
			else if (index == 2)
			{
				score = std::stof(temptoken);
			}
			else
			{
				city = temptoken;
			}
			++index;
		}


		insertthis.city = city;
		insertthis.score = score;
		insertthis.listid = listid;
		insertthis.hostid = hostid;

		//if we already seen this host, dont need to make new vector
		if (Data.find(hostid) == Data.end())
		{
			std::vector<record> rec;
			rec.push_back(insertthis);
			Data[hostid] = rec;
		}
		else
		{
			Data[hostid].push_back(insertthis);
		}
	}


	//now sort each vector by score //might not have to do this because already sorted

	//now sort entire vector by score

	int totalprintcount = results.size();
	int pagecount = (results.size() / num);

	for (int i = 0; i < pagecount; ++i)
	{
		int insertcount = 0;

		while (insertcount < num)
		{
			for (int j = 0; j < actualData.size(); ++j)
			{
				//skip empty vectors
				if (actualData[j].empty())
					continue;

				std::string builtstring = BuildString(*actualData[j].begin());

				res.push_back(builtstring);
				++insertcount;
				actualData[j].erase(actualData[j].begin());

				if (insertcount >= num)
					break;
			}

			res.push_back("");
		}
	}
	

	return res;
}

