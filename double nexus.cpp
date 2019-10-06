

//Interviewer was WRONG - they said longest common subsequence - what
//they meant was longest common substring

#include <iostream>
#include <vector>
/*
2 3 5
*/
using namespace std;
#include <algorithm>
/*
int nthUglyNumber(int n) {
	if (n <= 0) return false; // get rid of corner cases 
	if (n == 1) return true; // base case
	int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
	vector<int> k(n);
	k[0] = 1;
	for (int i = 1; i < n; i++)
	{
		k[i] = min(k[t2] * 2, min(k[t3] * 3, k[t5] * 5));
		if (k[i] == k[t2] * 2) t2++;
		if (k[i] == k[t3] * 3) t3++;
		if (k[i] == k[t5] * 5) t5++;
	}
	return k[n - 1];
}

int main(void) {

	std::vector<int> nums;
	for (int i = 1; i < 1691; ++i) {
		nums.push_back(nthUglyNumber(i));
	}

	std::cout << "{";
	for (int i = 0; i < nums.size(); ++i) {

		std::cout << " " << nums[i];
		if (i != nums.size() - 1) {
			std::cout << ",";
		}
	}
	std::cout << "}";
	return 0;


}
*/

/*
bool steppingNumber(long long i) {

	//get all digits
	std::vector<int> digits;

	long long copy = i;

	while (copy > 0) {
		int dig = copy % 10;
		digits.push_back(dig);
		copy /= 10;
	}

	for (int i = 1; i < digits.size(); ++i) {

		if (std::abs(digits[i - 1] - digits[i]) != 1) {
			return false;
		}

	}

	return true;
}
*/
#include <set>

std::vector<int> merge3Arrays(std::vector<int>& a,
	std::vector<int>& b,
	std::vector<int>& c) {

	std::vector<int> s;

	int indexA = 0;
	int indexB = 0;
	int indexC = 0;

	while (indexA < a.size() && indexB < b.size()
		&& indexC < c.size()) {

		//if all are equal, move all, otherwise move smallest one
		if (a[indexA] == b[indexB] && b[indexB] == c[indexC]) {
			
			s.push_back(a[indexA]);
			
			++indexA;
			++indexB;
			++indexC;

		}
		else if (a[indexA] < b[indexB]) {
			++indexA;
		}
		else if (b[indexB] < c[indexC]) {
			++indexB;
		}
		else {
			++indexC;
		}

	}

	return s;
}

/*
user0 = ["/start", "/pink", "/register", "/orange", "/red", "a"]
user1 = ["/start", "/green", "/blue", "/pink", "/register", "/orange", "/one/two"]
user2 = ["a", "/one", "/two"]
user3 = ["/red", "/orange", "/yellow", "/green", "/blue", "/purple", "/white", "/amber", "/HotRodPink", "/BritishRacingGreen"]
user4 = ["/red", "/orange", "/amber", "/green", "/blue", "/purple", "/white", "/lavender", "/HotRodPink", "/BritishRacingGreen"]
user5 = ["a"]

Sample output:

findContiguousHistory(user0, user1)
   /pink
   /register
   /orange

findContiguousHistory(user1, user2)
   (empty)

findContiguousHistory(user2, user0)
   a

findContiguousHistory(user5, user2)
   a

findContiguousHistory(user3, user4)
   /green
   /blue
   /purple
   /white

findContiguousHistory(user4, user3)
   /green
   /blue
   /purple
   /white

n: length of the first user's browsing history
m: length of the second user's browsing history

*/

std::vector<std::string> FindLongestCommonPath(std::vector<std::string>& user1, std::vector<std::string>& user2) {

	//2 cases: either match or dont match
	//go from 1 to +1, 1 to +1
	int maxLength = 0;
	int endIndex = user1.size();
	bool found = false;
	std::vector<std::vector<int>> dp(user1.size() + 1, std::vector<int>(user2.size() + 1));

	for (int i = 1; i <= user1.size(); ++i) {

		for (int j = 1; j <= user2.size(); ++j) {

			//if they match
			if (user1[i - 1] == user2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}

			if (dp[i][j] > maxLength) {
				found = true;
				maxLength = dp[i][j];
				endIndex = i;
			}

		}

	}

	if(found)
		return std::vector<std::string>(user1.begin() + endIndex - maxLength, user1.begin() + endIndex);
	
	return {};
}

class node {

public:
	int val = 0;
	node* left = nullptr;
	node* right = nullptr;
	node(int v) {
		val = v;
	}
	node(){}
};

void BinaryTree2DoubleLinkedList(node* root, node **head) {

	//base case of return if root is null
	//do left side
	//do this
	//set prev to root <-- important lol
	// do right side
	// for doing this:
	// if prev is null, then set head to root
	// else set root->left to prev and prev->right to root
	//

	if (!root) {
		return;
	}

	static node* prev = nullptr;

	BinaryTree2DoubleLinkedList(root->left, head);


	if (!prev) {
		*head = root;
	}
	else {
		root->left = prev;
		prev->right = root;
	}
	prev = root;


	BinaryTree2DoubleLinkedList(root->right, head);

}


void printList(node* r) {
	while (r) {

		std::cout << r->val << " ";
		r = r->right;

	}
}

//2 * 10^9
#include <cmath>
#include <string>
int main(void) {

	std::vector<std::string>	user0 = { "/start", "/pink", "/register", "/orange", "/red", "a" };
	std::vector<std::string>	user1 = { "/start", "/green", "/blue", "/pink", "/register", "/orange", "/one/two" };
	std::vector<std::string>	user2 = { "a", "/one", "/two" };
	std::vector<std::string>	user3 = { "/red", "/orange", "/yellow", "/green", "/blue", "/purple", "/white", "/amber", "/HotRodPink", "/BritishRacingGreen" };
	std::vector<std::string>	user4 = { "/red", "/orange", "/amber", "/green", "/blue", "/purple", "/white", "/lavender", "/HotRodPink", "/BritishRacingGreen" };
	std::vector<std::string>	user5 = { "a" };

	auto c = FindLongestCommonPath(user0, user1);

	for (int i = 0; i < c.size(); ++i) {
		std::cout << c[i] << " ";
	}


	node *root = new node(10);
	root->left = new node(12);
	root->right = new node(15);
	root->left->left = new node(25);
	root->left->right = new node(30);
	root->right->left = new node(36);

	// Convert to DLL 
	node *head = nullptr;
	BinaryTree2DoubleLinkedList(root, &head);

	// Print the converted list 
	printList(head);

	return 0;
}