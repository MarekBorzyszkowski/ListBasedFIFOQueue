#ifndef CDL_H
#define CDL_H
#include "DoubleLinkedNode.h" 

template <class T> class CircularDoubleLinkedList {
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

	T* delBack();
	T* delFront();
	T* delNode(DoubleLinkedNode<T>*);

	~CircularDoubleLinkedList();

};

template <class T>
CircularDoubleLinkedList<T>::CircularDoubleLinkedList() {
	size = 0;
	begin = end = nullptr;
}

template <class T>
void CircularDoubleLinkedList<T>::setBegin(DoubleLinkedNode<T>* newBegin) {
	begin = newBegin;
}

template <class T>
void CircularDoubleLinkedList<T>::setEnd(DoubleLinkedNode<T>* newEnd) {
	end = newEnd;
}

template <class T>
DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getBegin() {
	return begin;
}

template <class T>
DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getEnd() {
	return end;
}

template <class T>
int CircularDoubleLinkedList<T>::getSize() {
	return size;
}

template <class T>
void CircularDoubleLinkedList<T>::addFirstNode(T* data) {
	begin = new DoubleLinkedNode<T>(data, nullptr, nullptr);
	begin->next = begin->previous = begin;
	end = begin;
}

template <class T>
void CircularDoubleLinkedList<T>::addNode(T* data) {
	DoubleLinkedNode<T>* newNode;
	newNode = new DoubleLinkedNode<T>(data, end, begin);
	begin->previous = end->next = newNode;
}

template <class T>
void CircularDoubleLinkedList<T>::addBack(T* data) {
	if (!begin) {
		addFirstNode(data);
	}
	else {
		addNode(data);
		end = end->next;
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
bool CircularDoubleLinkedList<T>::delNodeInZeroOrOneElemList() {
	if (!begin) return true;
	else if (begin == end) {
		delete begin;
		begin = end = nullptr;
		return true;
	}
	return false;
}

template <class T>
T* CircularDoubleLinkedList<T>::delBack() {
	T* returnValue;
	if (!begin) return nullptr;
	else if (begin == end) {
		returnValue = begin->value;
		delete begin;
		begin = end = nullptr;
	}
	else {
		DoubleLinkedNode<T>* delNode = end;
		returnValue = delNode->value;
		end = end->previous;
		end->next = begin;
		begin->previous = end;
		delete delNode;
	}
	size--;
	return returnValue;
}

template <class T>
T* CircularDoubleLinkedList<T>::delFront() {
	T* returnValue;
	if (!begin) return nullptr;
	else if (begin == end) {
		returnValue = begin->value;
		delete begin;
		begin = end = nullptr;
	}
	else {
		DoubleLinkedNode<T>* delNode = begin;
		returnValue = delNode->value;
		begin = begin->next;
		end->next = begin;
		begin->previous = end;
		delete delNode;
	}
	size--;
	return returnValue;
}

template <class T>
T* CircularDoubleLinkedList<T>::delNode(DoubleLinkedNode<T>* nodeToDelete) {
	if (!begin) return nullptr;
	else if (begin == end) {
		if (begin == nodeToDelete) {
			return delFront();
		}
	}
	else {
		if (nodeToDelete == begin) {
			return delFront();
		}
		DoubleLinkedNode<T>* nodeToCheck = begin->next;
		while (nodeToCheck->next != begin) {
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
		if (nodeToDelete == end) {
			return delBack();
		}
	}
}

template <class T>
CircularDoubleLinkedList<T>::~CircularDoubleLinkedList() {
	if (begin) {
		if (begin == end) {
			delete begin;
			begin = end = nullptr;
		}
		else {
			DoubleLinkedNode<T>* nextToDel;
			while (begin->next != end) {
				nextToDel = begin->next;
				delete begin;
				begin = nextToDel;
			}
			delete begin;
			delete end;
			begin = end = nullptr;
		}
	}
}

#endif