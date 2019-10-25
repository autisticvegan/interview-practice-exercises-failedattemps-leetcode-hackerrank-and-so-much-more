//bounded blocking queue
/*
inherit from queue
Have 2 mutices, one for reading, one for writing
also have 2 cond vars, one for isFull, the other isEmpty

standard stuff:
use unique_lock to acquire the mutex


*/



//unistd.h lol?

//https://stackoverflow.com/questions/40065289/blocking-queue-using-c-std-queue
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
//unique lock is in mutex 
//unique lock follows RAII pattern
//random unrelated trivia - as of c++11 swap is now in utility not algorithm anymore
template <class T> class BBQ : public std::queue<T> {

private:
	int maxSize; //bounded
	std::mutex readMutex; //blocking
	std::mutex writeMutex;
	std::condition_variable isFull;
	std::condition_variable isEmpty;

public:


//2 funcs - push and pop
// helpers - is full, is empty

	//ctor - establish maxsize, and queue ctor
	BlockingQueue(int size) {
		maxSize = size;
		queue<T>();
	}

	/*
		push - 
		1. lock the write mutex
		2. while its full, wait
		3.push the item
		4. isEmpty notifies all

		pop - 
		1. lock the read mutex
		2. while q is empty, wait
		3. get the value from the front of the q
		4. pop
		5. if its !full, then isFull notifies all
		6. return the value

		full - check if q size is >= maxsize
		empty - return q empty
	*/

	void push(T item) {
		std::unique_lock<std::mutex> writeLock(writeMutex);
		while (IsFull()) {
			isFull.wait(writeLock);
		}
		std::queue<T>::push(item);
		if(notEmpty())
			isEmpty.notify_all();
	}

	bool notEmpty() {
		return !std::queue<T>::empty();
	}

	bool IsFull() {
		return std::queue<T>::size() >= maxSize;
	}

	T pop() {
		std::unique_lock<std::mutex> readLock(readMutex);
		while (std::queue<T>::empty()) {
			//wait
			isEmpty.wait(readLock);
		}
		T val = std::queue<T>::front();
		std::queue<T>::pop();
		if (!IsFull())
			isFull.notify_all();
		return val;
	}




};





int main(void) {





	return 0;
}