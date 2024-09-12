#pragma once

#define MAX_COUNTER 1000000
#define NUM_THREADS 3

class IncrementCounter {
private:
	int counter;
	std::mutex counterMtx;

	void incrementCounter();

	void incrementCounterWithoutThreadSafe();
	void incrementCounterMutex();
	void incrementCounterSemaphore();

public:
	IncrementCounter();
	~IncrementCounter();

	void runHW();
};