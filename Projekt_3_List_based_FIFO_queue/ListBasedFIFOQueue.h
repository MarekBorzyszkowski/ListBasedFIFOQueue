#ifndef LBF_H
#define LBF_H
#include "CircularDoubleLinkedList.h"
//ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD
template <class T> class ListBasedFIFOQueue {
private:
	CircularDoubleLinkedList<T> list;
	DoubleLinkedNode<T>* firstQueueElem, * lastQueueElem;
	bool isQueueEmpty;
public:
	ListBasedFIFOQueue();

	bool isQueueEmptyFun();

	int getListSize();
	int getQueueSize();
	DoubleLinkedNode<T>* getFirstQueueElem();
	DoubleLinkedNode<T>* getLastQueueElem();
	DoubleLinkedNode<T>* getFirstListElem();
	DoubleLinkedNode<T>* getLastListElem();

	void addListBegin(T*);
	void addListEnd(T*);

	void pushBack(T*);

	T* delListBegin();
	T* delListEnd();
	T* popFirst();

	void garbadeSoft();
	void garbageHard();

	~ListBasedFIFOQueue();
};

template <class T>
ListBasedFIFOQueue<T>::ListBasedFIFOQueue() {
	firstQueueElem = lastQueueElem = nullptr;
	isQueueEmpty = 1;
}

template <class T>
bool ListBasedFIFOQueue<T>::isQueueEmptyFun() {
	return isQueueEmpty;
}
template <class T>
int ListBasedFIFOQueue<T>::getListSize() {
	return list.getSize();
}

template <class T>
int ListBasedFIFOQueue<T>::getQueueSize() {
	if (!isQueueEmpty) {
		DoubleLinkedNode<T>* tmpNode = firstQueueElem;
		int queueLenght = 1;
		while (tmpNode != lastQueueElem) {
			queueLenght++;
			tmpNode = tmpNode->previous;
		}
		return queueLenght;
	}
	else {
		return 0;
	}
}

template <class T>
DoubleLinkedNode<T>* ListBasedFIFOQueue<T>::getFirstQueueElem() {
	return firstQueueElem;
}

template <class T>
DoubleLinkedNode<T>* ListBasedFIFOQueue<T>::getLastQueueElem() {
	return lastQueueElem;
}

template <class T>
DoubleLinkedNode<T>* ListBasedFIFOQueue<T>::getFirstListElem() {
	return list.getBegin();
}

template <class T>
DoubleLinkedNode<T>* ListBasedFIFOQueue<T>::getLastListElem() {
	return list.getEnd();
}

template <class T>
void ListBasedFIFOQueue<T>::addListBegin(T* data) {
	list.addFront(data);
}

template <class T>
void ListBasedFIFOQueue<T>::addListEnd(T* data) {
	list.addBack(data);
}

template <class T>
void ListBasedFIFOQueue<T>::pushBack(T* data) {
	if (isQueueEmpty) {
		if (list.getSize()) {
			if (!firstQueueElem) {
				firstQueueElem = lastQueueElem = list.getEnd();
			}
			firstQueueElem->value = data;
		}
		else {
			list.addFront(data);
			firstQueueElem = lastQueueElem = list.getBegin();
		}
		isQueueEmpty = 0;
	}
	else {
		if (list.getSize() == getQueueSize()) {
			if (lastQueueElem == list.getBegin()) {
				list.addFront(data);
				lastQueueElem = list.getBegin();
			}
			else {
				list.addBeforeNode(data, lastQueueElem);
				lastQueueElem = lastQueueElem->previous;
			}
		}
		else {
			lastQueueElem = lastQueueElem->previous;
			lastQueueElem->value = data;
		}
	}
}

template <class T>
T* ListBasedFIFOQueue<T>::popFirst() {
	if (isQueueEmpty) {
		return nullptr;
	}
	else {
		DoubleLinkedNode<T>* resoult = firstQueueElem;
		if (firstQueueElem == lastQueueElem) {
			//firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
			return resoult->value;
		}
		else {
			firstQueueElem = firstQueueElem->previous;
			return resoult->value;
		}
	}
}

template <class T>
T* ListBasedFIFOQueue<T>::delListBegin() {
	if (!isQueueEmpty) {
		if (firstQueueElem == list.getBegin()) {
			if (firstQueueElem == lastQueueElem) {
				popFirst();
			}
			else {
				firstQueueElem = firstQueueElem->previous;
			}
		}
		else if (lastQueueElem == list.getBegin()) {
			lastQueueElem = lastQueueElem->next;
		}
		if (list.getSize() < 2) {
			firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
		}
	}
	return list.delFront();
}

template <class T>
T* ListBasedFIFOQueue<T>::delListEnd() {
	if (!isQueueEmpty) {
		if (firstQueueElem == list.getEnd()) {
			if (firstQueueElem == lastQueueElem) {
				popFirst();
			}
			else {
				firstQueueElem = firstQueueElem->previous;
			}
		}
		else if (lastQueueElem == list.getEnd()) {
			lastQueueElem = lastQueueElem->next;
		}
		if (list.getSize() < 2) {
			firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
		}
	}
	return list.delBack();
}

template <class T>
void ListBasedFIFOQueue<T>::garbadeSoft() {
	if (isQueueEmpty) {
		if (list.getSize()) {
			DoubleLinkedNode<T>* tmpNode = list.getBegin();
			while (tmpNode != list.getEnd()) {
				delete tmpNode->value;
				tmpNode->value = nullptr;
				tmpNode = tmpNode->next;
			}
			delete list.getEnd()->value;
			list.getEnd()->value = nullptr;
		}
	}
	else {
		DoubleLinkedNode<T>* tmpNode = lastQueueElem->previous;
		while (tmpNode != firstQueueElem) {
			delete tmpNode->value;
			tmpNode->value = nullptr;
			tmpNode = tmpNode->previous;
		}
	}
}

template <class T>
void ListBasedFIFOQueue<T>::garbageHard() {
	if (isQueueEmpty) {
		while (list.getSize()) {
			list.delFront();
		}
	}
	else {
		while (lastQueueElem->previous != firstQueueElem) {
			list.delNode(lastQueueElem->previous);
		}
	}
}

template <class T>
ListBasedFIFOQueue<T>::~ListBasedFIFOQueue() {
	firstQueueElem = lastQueueElem = nullptr;
}

#endif