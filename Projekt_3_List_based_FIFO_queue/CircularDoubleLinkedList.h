#ifndef CDL_H
#define CDL_H
#include "DoubleLinkedNode.h" 

template <class T> class CircularDoubleLinkedList {
private:
	int size;
	DoubleLinkedNode<T> * begin;
	
	void addFirstNode(T*);
	void addNode(T*);

public:
	CircularDoubleLinkedList();
	
	void setBegin(DoubleLinkedNode<T>*);

	DoubleLinkedNode<T>* getBegin();
	DoubleLinkedNode<T>* getEnd();
	int getSize();

	void addBeforeNode(T*, DoubleLinkedNode<T>*);
	void addBack(T*);
	void addFront(T*);

	T* delBack();
	T* delFront();
	T* delNode(DoubleLinkedNode<T>*);

	~CircularDoubleLinkedList();

};

template <class T>
CircularDoubleLinkedList<T>::CircularDoubleLinkedList() {
	size = 0;
	begin = nullptr;
}

template <class T>
void CircularDoubleLinkedList<T>::setBegin(DoubleLinkedNode<T>* newBegin) {
	begin = newBegin;
}

template <class T>
DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getBegin() {
	return begin;
}

template <class T>
DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getEnd() {
	return begin->previous;
}

template <class T>
int CircularDoubleLinkedList<T>::getSize() {
	return size;
}

template <class T>
void CircularDoubleLinkedList<T>::addBeforeNode(T* data, DoubleLinkedNode<T>* node) {
	DoubleLinkedNode<T>* newNode;
	newNode = new DoubleLinkedNode<T>(data, node->previous, node);
	node->previous->next = newNode;
	node->previous = newNode;
	size++;
}

template <class T>
void CircularDoubleLinkedList<T>::addFirstNode(T* data) {
	begin = new DoubleLinkedNode<T>(data, nullptr, nullptr);
	begin->next = begin->previous = begin;
}

template <class T>
void CircularDoubleLinkedList<T>::addNode(T* data) {
	DoubleLinkedNode<T>* newNode;
	newNode = new DoubleLinkedNode<T>(data, begin->previous, begin);
	begin->previous->next = newNode;
	begin->previous = newNode;
}

template <class T>
void CircularDoubleLinkedList<T>::addBack(T* data) {
	if (!begin) {
		addFirstNode(data);
	}
	else {
		addNode(data);
	}
	size++;
}

template <class T>
void CircularDoubleLinkedList<T>::addFront(T* data) {
	if (!begin) {
		addFirstNode(data);
	}
	else {
		addNode(data);
		begin = begin->previous;
	}
	size++;
}


template <class T>
T* CircularDoubleLinkedList<T>::delBack() {
	T* returnValue;
	if (!begin) return nullptr;
	else if (size==1) {
		returnValue = begin->value;
		delete begin;
		begin = nullptr;
	}
	else {
		DoubleLinkedNode<T>* delNode = begin->previous;
		returnValue = delNode->value;
		delNode->previous->next = begin;
		begin->previous = delNode->previous;
		delete delNode;
	}
	size--;
	return returnValue;
}

template <class T>
T* CircularDoubleLinkedList<T>::delFront() {
	T* returnValue;
	if (!begin) return nullptr;
	else if (size == 1) {
		returnValue = begin->value;
		delete begin;
		begin = nullptr;
	}
	else {
		DoubleLinkedNode<T>* delNode = begin;
		returnValue = delNode->value;
		begin = begin->next;
		delNode->previous->next = begin;
		begin->previous = delNode->previous;
		delete delNode;
	}
	size--;
	return returnValue;
}

template <class T>
T* CircularDoubleLinkedList<T>::delNode(DoubleLinkedNode<T>* nodeToDelete) {
	if (!begin) return nullptr;
	else if (size==1) {
		if (begin == nodeToDelete) {
			return delFront();
		}
	}
	else {
		if (nodeToDelete == begin) {
			return delFront();
		}
		DoubleLinkedNode<T>* nodeToCheck = begin->next;
		while (nodeToCheck != begin) {
			if (nodeToCheck == nodeToDelete) {
				DoubleLinkedNode<T>* previousNode, * nextNode;
				T* returnValue = nodeToCheck->value;
				previousNode = nodeToCheck->previous;
				nextNode = nodeToCheck->next;
				previousNode->next = nextNode;
				nextNode->previous = previousNode;
				delete nodeToCheck;
				size--;
				return returnValue;
			}
			nodeToCheck = nodeToCheck->next;
		}
	}
	return nullptr;
}

template <class T>
CircularDoubleLinkedList<T>::~CircularDoubleLinkedList() {
	if (begin) {
		
		if (size == 1) {
			delete begin;
			begin = nullptr;
		}
		else {
			begin->previous->next = nullptr;
			while (begin->next != nullptr) {
				begin = begin->next;
				delete begin->previous;
			}
			delete begin;
			begin = nullptr;
		}
	}
}

#endif