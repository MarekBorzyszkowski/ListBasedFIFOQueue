#pragma once
#include "CircularDoubleLinkedList.h"

template <class T> class ListBasedFIFOQueue {
private:
	CircularDoubleLinkedList<T> list;
	DoubleLinkedNode<T>* firstQueueElem, * lastQueueElem;
	bool isQueueEmpty;
public:
	ListBasedFIFOQueue();

	int getListSize();
	int getQueueSize();

	void printQueue();

	void pushBack(T*);
	T* popFirst();

	void garbadeSoft();
	void garbageHard();

	~ListBasedFIFOQueue();
};