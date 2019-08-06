int mctFromLeafValues(vector<int>& arr) {

	/*
	ideas: use a vector, similar to a stack for first part.

	iterate through each number, if its less than the back
	WARNING: DO AFTER POPPING
	of our vector, res += mid * min(a, stack.back)
	reason for mid: it is the "mid" node between the 2
	we are comparing, a and the vec.back()

	push onto the stack

	at end, multiply stack[i] * stack[i-1]
	DONT FORGET to set i = 2, i < stack.size(); ++i
	*/

	int result = 0;
	std::vector<int> vStack;
	vStack.push_back(INT_MAX);

	for (const auto& a : arr) {

		while (a >= vStack.back()) {
			int mid = vStack.back();
			vStack.pop_back();
			result += mid * std::min(vStack.back(), a);
		}


		vStack.push_back(a);
	}

	for (int i = 2; i < vStack.size(); ++i) {
		result += vStack[i] * vStack[i - 1];
	}


	return result;
}