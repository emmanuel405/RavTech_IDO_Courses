#include <iostream>
#include <thread>
#include <vector>
#include "MyThreadSafeList.h"
#include "IncrementCounter.h"

#define NUM_THREADS 3

void HW1();
void HW2();

int main() {

	std::cout << "HW 1:" << std::endl;
	//HW1();

	std::cout << "\nHW 2:" << std::endl;
	for(int i=0;i<3000;i++)
		HW2();

	return 0;
}

void HW1() {
	IncrementCounter incCounter;
	incCounter.runHW();
}

void HW2() {
	MyThreadSafeList head;

	std::vector<std::thread> threads(NUM_THREADS);

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i] = std::thread(&MyThreadSafeList::add, &head, i + 1);
	}

	for (std::thread& th : threads)
	{
		if (th.joinable())
			th.join();
	}

	head.toString();
}
