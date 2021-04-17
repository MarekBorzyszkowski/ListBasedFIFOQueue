#pragma once
#include "DoubleLinkedNode.h" 

template <class T>class CircularDoubleLinkedList {
private:
	int size;
	DoubleLinkedNode<T> * begin, * end;
	
	void addFirstNode(T*);
	void addNode(T*);
	bool delNodeInZeroOrOneElemList();

public:
	CircularDoubleLinkedList();
	
	void setBegin(DoubleLinkedNode<T>*);
	void setEnd(DoubleLinkedNode<T>*);

	DoubleLinkedNode<T>* getBegin();
	DoubleLinkedNode<T>* getEnd();
	int getSize();

	void addBack(T*);
	void addFront(T*);

	void delBack();
	void delFront();
	void delNode(DoubleLinkedNode<T>*);

	~CircularDoubleLinkedList();

};