#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> queue = 0;
int max_client = 10;

void client() {
	while (queue.load() < max_client) {
		queue.store(++queue, std::memory_order_relaxed);
		std::cout << "\nclient " << queue.load() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void operationist() {
	while (queue.load() != 0) {
		queue.store(--queue, std::memory_order_relaxed);
		std::cout << "\noperationist " << queue.load() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}


int main()
{

	std::thread cl(client);
	std::thread op(operationist);

	if (cl.joinable()) {
		cl.join();
	}
	if (op.joinable()) {
		op.join();
	}


	return 0;
}
