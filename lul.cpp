//bad code should be using mutices instead

class Foo {
public:
	std::promise<void> barrier1;
	std::promise<void> barrier2;

	Foo() {

	}

	void first(function<void()> printFirst) {

		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		barrier1.set_value();
	}

	void second(function<void()> printSecond) {
		barrier1.get_future().wait();
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		barrier2.set_value();
	}

	void third(function<void()> printThird) {
		barrier2.get_future().wait();
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}
};

class FooBar {
private:
	int n;
	std::mutex m1;
	std::mutex m2;

public:
	FooBar(int n) {
		this->n = n;
		m1.lock();
	}

	void foo(function<void()> printFoo) {

		for (int i = 0; i < n; i++) {

			// printFoo() outputs "foo". Do not change or remove this line.
			m2.lock();
			printFoo();
			m1.unlock();
		}
	}

	void bar(function<void()> printBar) {

		for (int i = 0; i < n; i++) {

			// printBar() outputs "bar". Do not change or remove this line.
			m1.lock();
			printBar();
			m2.unlock();
		}
	}
};