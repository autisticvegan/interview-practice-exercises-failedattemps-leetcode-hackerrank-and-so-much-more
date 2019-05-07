/*
moving stones until consec
valid word abbreviation
read n characters given read 4
design linked list
*/

#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <optional>
#include <functional>
#include <cctype>


std::vector<int> numMovesStones(int a, int b, int c) {
	std::vector<int> t{ a,b,c };
	std::sort(t.begin(), t.end());

	// abs unnecessary because its sorted
	int xyDist = std::abs(t[1] - t[0]);
	int xzDist = std::abs(t[2] - t[0]);
	int yzDist = std::abs(t[2] - t[1]);

	if (xzDist == 2) {
		return { 0, 0 };
	}
	else if (std::min(xyDist, yzDist) <= 2) {
		return { 1, xzDist - 2 };
	}
	else {
		return { 2, xzDist - 2 };
	}

}

// bogus implementation since its behind a paywall (leetcode premium LOL)
int read4(char* buf) {
	return 0;
}

int read(char* buf, int n) {
	char* tmp = new char[4];

	int countThatWasRead = 0;
	int currentIndex = 0;

	while (n > 0) {
		int countThatWasRead = read4(tmp);
		int countToCopy = std::min(countThatWasRead, n);

		// copy into buffer
		currentIndex += countToCopy;
		n -= countToCopy;
		if (countThatWasRead < 4) {
			return currentIndex;
		}
	}

	return currentIndex;
}

std::optional<int> getDigitOpt(char c) {
	bool isDigit = std::isdigit(c);

	if (!isDigit) {
		return std::optional<int>();
	} else {
		int v = c - '0';
		return std::optional<int>(v);
	}
}

bool isValidWordAbbreviation(std::string& str, std::string& abbreviated) {
	// idea: check each letter with an index, in the case of numbers,
	// just increment the index that much
	int index = 0;
	for (int i = 0; i < abbreviated.size(); ++i) {
		
		std::optional<int> d = getDigitOpt(abbreviated[i]);
		if (d) {
			index += d.value();
		}
		else {

			if (index >= str.length()) {
				return false;
			}

			if (str[index] != abbreviated[i]) {
				return false;
			}

			index++;
		}
	}

	return index == str.length();
}


bool passTestAbbr(std::string& t, std::string& t2, bool target) {
	return isValidWordAbbreviation(t, t2) == target;
}

class MyLinkedList {
public:

	class Node
	{
	public:
		Node* next = nullptr;
		Node* prev = nullptr;
		int data = 0;
	};

	Node* TailP;
	Node* HeadP;
	int size = 0;

	/** Initialize your data structure here. */
	MyLinkedList() {
		TailP = nullptr;
		HeadP = nullptr;
	}

	Node* getNode(int index) {
		Node* temp = HeadP;

		if (index < 0 || !TailP || !HeadP)
			return nullptr;

		if (index == 0)
		{
			return HeadP;
		}

		bool forward = false;

		if (index < size / 2)
			forward = true;

		if (forward)
		{
			int countit = 0;
			while (temp != nullptr && countit != index)
			{
				temp = temp->next;
				++countit;
			}

			return temp;
		}
		else
		{
			temp = TailP;
			int countit = 0;
			while (temp != nullptr && countit != (size - index - 1))
			{
				temp = temp->prev;
				++countit;
			}

			return temp;
		}
	}


	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	int get(int index) {

		Node* t = getNode(index);

		if (t) {
			return t->data;
		}
		return -1;
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {

		if (HeadP)
		{
			Node* oldHead = HeadP;
			HeadP = new Node();
			HeadP->prev = nullptr;
			HeadP->next = oldHead;
			HeadP->data = val;
			oldHead->prev = HeadP;

		}
		else
		{
			HeadP = new Node();
			HeadP->next = nullptr;
			HeadP->prev = nullptr;
			TailP = HeadP;
			HeadP->data = val;
		}

		++size;
	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {

		if (TailP)
		{
			Node* oldTail = TailP;
			TailP = new Node();
			TailP->prev = oldTail;
			oldTail->next = TailP;
			TailP->next = nullptr;
			TailP->data = val;

		}
		else
		{
			TailP = new Node();
			TailP->next = nullptr;
			TailP->prev = nullptr;
			HeadP = TailP;
			TailP->data = val;
		}

		++size;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {

		if (index > size)
			return;

		//bug in leetcode test case

		if (index == 0 || index == -1) {
			addAtHead(val);
		}
		else if (index == size) {
			addAtTail(val);
		}
		else {
			Node* t = getNode(index);
			if (t == nullptr)
				return;

			Node* p = t->prev;
			Node* newNode = new Node();
			newNode->data = val;
			newNode->next = t;
			newNode->prev = p;
			t->prev = newNode;
			p->next = newNode;

			++size;
		}
	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {

		if (index < 0 || index >= size)
			return;

		if (index == 0) {

			if (!HeadP)
				return;

			Node* t = HeadP->next;

			if (HeadP == TailP)
				TailP = nullptr;

			delete HeadP;
			HeadP = t;

			if (HeadP)
				HeadP->prev = nullptr;


		}
		else if (index == size - 1) {

			if (!TailP)
				return;

			Node* t = TailP->prev;

			if (HeadP == TailP)
				HeadP = nullptr;

			delete TailP;
			TailP = t;

			if (TailP)
				TailP->next = nullptr;
		}
		else {
			Node* t = getNode(index);
			if (t == nullptr)
				return;

			Node* n = t->next;
			Node* p = t->prev;

			//we know both of these are valid,
			//because at least head and tail are present

			n->prev = p;
			p->next = n;
			delete t;
		}



		--size;
	}
};

int main(void) {

	std::string t = "abc";
	std::string t2 = "a1c";
	
	bool z = passTestAbbr(t, t2, true);

	std::string t3 = "a";
	std::string t4 = "1";

	z = passTestAbbr(t3, t4, true);

	std::string t5 = "aa";
	std::string t6 = "2";

	z = passTestAbbr(t5, t6, true);

	std::string t7 = "aAAAc";
	std::string t8 = "a3c";

	z = passTestAbbr(t7, t8, true);

	std::string t9 = "";
	std::string t10 = "0";

	z = passTestAbbr(t9, t10, true);

	std::string t11 = "baCCc";
	std::string t12 = "1a2c";

	z = passTestAbbr(t11, t12, true);

	// false cases

	std::string t13 = "abc";
	std::string t14 = "4";

	z = passTestAbbr(t13, t14, false);

	std::string t15 = "abc";
	std::string t16 = "1";

	z = passTestAbbr(t15, t16, false);


	MyLinkedList m;
	m.addAtHead(4);
	int zz = m.get(1);
	m.addAtHead(7);
	m.addAtTail(1);
	m.addAtIndex(1, 7);
	int q = m.get(4);
	int qq = m.get(3);
	m.addAtHead(2);
	m.addAtIndex(4, 1);
	m.deleteAtIndex(3);
	m.addAtHead(7);

	MyLinkedList mm;
	mm.addAtHead(1);
	mm.addAtIndex(1, 2);
	mm.get(1);
	mm.get(0);
	mm.get(2);


	/*
	["MyLinkedList","addAtHead","addAtIndex","get","get","get"]
[[],[1],[1,2],[1],[0],[2]]
	*/

	/*
	["MyLinkedList", "addAtHead", "get", "addAtHead", "addAtTail", "addAtIndex", "get", "get", "addAtHead", "addAtIndex", "deleteAtIndex", "addAtHead"]
	[[], [4], [1], [7], [1], [1, 7], [4], [3], [2], [4, 1], [3], [7]]
	*/
	return 0;
}