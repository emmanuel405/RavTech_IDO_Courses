#include <iostream>
#include <mutex>
#include <semaphore>
#include <vector>
#include <thread>
#include "IncrementCounter.h"

std::counting_semaphore<1> counterSemaphore{ 1 };

IncrementCounter::IncrementCounter() {
	counter = 0;
}
IncrementCounter::~IncrementCounter() {

}

void IncrementCounter::incrementCounter() {
	for (int i = 0; i < MAX_COUNTER; i++)
		counter++;
}

void IncrementCounter::incrementCounterWithoutThreadSafe() {
	incrementCounter();
}

void IncrementCounter::incrementCounterMutex() {
	// we can write only - std::lock_guard<std::mutex> lock(counterMtx); - in this scope
	counterMtx.lock();
	incrementCounter();
	counterMtx.unlock();
}

void IncrementCounter::incrementCounterSemaphore()
{
	counterSemaphore.acquire();
	incrementCounter();
	counterSemaphore.release();
}

void IncrementCounter::runHW() {

	std::vector<std::thread> threads(NUM_THREADS);
	const int NUMBER_INCREMENT_FUNCTION = 3;

	std::cout << "MAX_COUNTER = " << MAX_COUNTER << ", NUM_THREADS = " << NUM_THREADS << 
		"\nExpected result = " << (MAX_COUNTER * NUM_THREADS) << std::endl << std::endl;

	for (int ith = 0; ith < NUMBER_INCREMENT_FUNCTION; ith++)
	{
		counter = 0;
		std::cout << "exercise 1.";

		if (ith == 0)
		{
			std::cout << "1 - without lock:" << std::endl;
			for (int i = 0; i < threads.size(); i++)
				threads[i] = std::thread(&IncrementCounter::incrementCounterWithoutThreadSafe, this);
		}
		else if (ith == 1)
		{
			std::cout << "2 - lock with mutex:" << std::endl;
			for (int i = 0; i < threads.size(); i++)
				threads[i] = std::thread(&IncrementCounter::incrementCounterMutex, this);
		}
		else
		{
			std::cout << "3 - lock with semaphore:" << std::endl;
			for (int i = 0; i < threads.size(); i++)
				threads[i] = std::thread(&IncrementCounter::incrementCounterSemaphore, this);
		}

		for (std::thread& th : threads)
		{
			if (th.joinable())
				th.join();
		}

		std::cout << "counter = " << counter << std::endl;
	}
}