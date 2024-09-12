#include <iostream>
#include "MyThreadSafeList.h"

MyThreadSafeList::MyThreadSafeList() {
	head = nullptr;
}
MyThreadSafeList::~MyThreadSafeList(){}

void MyThreadSafeList::add(const int newData) {

	std::lock_guard<std::mutex> lockAddList(listMtx);

	Node* element = new Node{ newData };
	if (head == nullptr)
	{
		head = element;
		return;
	}

	else
	{
		Node* temp = head;
		while (temp->next != nullptr)
			temp = temp->next;

		temp->next = element;
	}
}

void MyThreadSafeList::toString() const {

	Node* temp = head;

	do {
		std::cout << temp->data << " ";
		temp = temp->next;
	} while (temp != nullptr);

	std::cout << std::endl;
}