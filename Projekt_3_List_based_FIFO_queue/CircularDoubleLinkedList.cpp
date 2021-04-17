#include "CircularDoubleLinkedList.h";

CircularDoubleLinkedList<class T>::CircularDoubleLinkedList() {
	size = 0;
	begin = end = nullptr;
}

void CircularDoubleLinkedList<T>:: setBegin(DoubleLinkedNode<T>* newBegin) {
	begin = newBegin;
}

void CircularDoubleLinkedList<T>::setEnd(DoubleLinkedNode<T>* newEnd) {
	begin = newEnd;
}

DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getBegin() {
	return begin;
}

DoubleLinkedNode<T>* CircularDoubleLinkedList<T>::getEnd() {
	return end;
}

int CircularDoubleLinkedList<T>::getSize() {
	return size;
}

void CircularDoubleLinkedList<T>::addFirstNode(T* data) {
	begin = new DoubleLinkedNode<T>(data, nullptr, nullptr);
	begin->next = begin->previous = begin;
	end = begin;
}

void CircularDoubleLinkedList<T>::addNode(T* data) {
	DoubleLinkedNode<T>* newNode;
	newNode = (data, end, begin);
	begin->previous = end->next = newNode;
}

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

bool CircularDoubleLinkedList<T>::delNodeInZeroOrOneElemList() {
	if (!begin) return true;
	else if (begin == end) {
		delete begin;
		begin = end = nullptr;
		return true;
	}
	return false;
}

void CircularDoubleLinkedList<T>::delBack() {
	if (delNodeInZeroOrOneElemList) return;
	else {
		DoubleLinkedNode<T>* delNode = end;
		end = end->previous;
		end->next = begin;
		begin->previous = end;
		delete delNode;
	}
	size--;
}

void CircularDoubleLinkedList<T>::delFront() {
	if (delNodeInZeroOrOneElemList) return;
	else {
		DoubleLinkedNode<T>* delNode = begin;
		begin = begin->next;
		end->next = begin;
		begin->previous = end;
		delete delNode;
	}
	size--;
}

void CircularDoubleLinkedList<T>::delNode(DoubleLinkedNode<T>* nodeToDelete) {
	DoubleLinkedNode<T>* nodeToCheck = begin;
	if (begin == end && begin == nodeToDelete) {
		delete begin;
		begin = end = nullptr;
		size--;
	}
	while (nodeToCheck->next != begin) {
		if (nodeToCheck == nodeToDelete) {
			DoubleLinkedNode<T>* previousNode, * nextNode;
			previousNode = nodeToCheck->previous;
			nextNode = nodeToCheck->next;
			previousNode->next = nextNode;
			nextNode->previous = previousNode;
			delete nodeToCheck;
			size--;
			return;
		}
		nodeToCheck = nodeToCheck->next;
	}
}

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
