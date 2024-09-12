#pragma once
#include <mutex>

#define NUM_THREADS 3

struct Node {
	int data;
	Node* next;

	Node(const int _data) {
		data = _data;
		next = nullptr;
	}
	Node() {
		data = 0;
		next = nullptr;
	}
};

class MyThreadSafeList {
private:
	Node* head;
	std::mutex listMtx;

public:
	MyThreadSafeList();
	~MyThreadSafeList();

	void add(const int newData);
	void toString() const;
};