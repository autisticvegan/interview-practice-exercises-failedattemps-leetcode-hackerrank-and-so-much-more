#include <list>
#include <vector>
#include <unordered_set>

class ListNode
{
public:
	ListNode* next;
	int val;
};

bool LoopExists(ListNode* h);

//better way to do this: use the STL LOL
void RemoveDuplicates(std::vector<int>& in)
{
	std::unordered_set<int> seen;

	for (int i = 0; i < (int)in.size()-1; ++i)
	{
		if (seen.count(in[i]) == 0)
		{
			seen.insert(in[i]);
		}
		else
		{
			in.erase(in.begin() + i);
			i--;
		}
	}


}

ListNode *detectCycle(ListNode *head) {

	if (!head || head->next == nullptr)
		return nullptr;

	if (head->next == head)
		return head;

	if (head->next->next == head)
		return head;

	ListNode* fast = head;
	ListNode* slow = head;
	ListNode* ret = head;
	//once we have fast and slow, go back again, then set it to nullptr

	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;

		if (fast == slow)
		{
			while (slow != ret)
			{
				slow = slow->next;
				ret = ret->next;
			}

			return ret;
		}

	}


	return nullptr;

}

bool LoopExists(ListNode* head)
{
	if (!head)
		return false;

	ListNode* fast = head;
	ListNode* slow = head;

	if (head->next == head)
		return true;

	if (head->next == nullptr)
		return false;

	fast = fast->next->next;
	
	while (fast != nullptr && slow != nullptr &&  fast->next != nullptr && slow != fast)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	if (fast == slow)
		return true;

	return false;

}

int main(void)
{
	ListNode* a = new ListNode;

	std::vector<int> dups(6);

	dups[0] = 1;
	dups[1] = 2;
	dups[2] = 3;
	dups[3] = 4;
	dups[4] = 2;
	dups[5] = 5;

	RemoveDuplicates(dups);

	

	return 0;
}