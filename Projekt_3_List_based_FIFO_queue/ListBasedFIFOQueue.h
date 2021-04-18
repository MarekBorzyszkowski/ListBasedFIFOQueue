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
			tmpNode = tmpNode->next;
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
			firstQueueElem = lastQueueElem = list.getBegin();
			firstQueueElem->value = data;
			isQueueEmpty = 0;
		}
		else {
			list.addFront(data);
			firstQueueElem = lastQueueElem = list.getBegin();
			isQueueEmpty = 0;
		}
	}
	else {
		if (list.getSize() == getQueueSize()) {
			list.setBegin(firstQueueElem);
			list.setEnd(lastQueueElem);
			list.addBack(data);
			lastQueueElem = list.getEnd();
		}
		else {
			lastQueueElem->next->value = data;
			lastQueueElem = lastQueueElem->next;
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
			firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
			return resoult->value;
		}
		else {
			firstQueueElem = firstQueueElem->next;
			return resoult->value;
		}
	}
}

template <class T>
T* ListBasedFIFOQueue<T>::delListBegin() {
	if (firstQueueElem && firstQueueElem == list.getBegin()) {
		if (firstQueueElem == lastQueueElem) {
			popFirst();
		}
		else {
			firstQueueElem = firstQueueElem->next;
		}
	}
	return list.delFront();
}

template <class T>
T* ListBasedFIFOQueue<T>::delListEnd() {
	if (lastQueueElem && lastQueueElem == list.getEnd()) {
		if (firstQueueElem == lastQueueElem) {
			firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
		}
		else {
			lastQueueElem = lastQueueElem->previous;
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
				tmpNode->value = nullptr;
				tmpNode = tmpNode->next;
			}
			list.getEnd()->value = nullptr;
		}
	}
	else {
		DoubleLinkedNode<T>* tmpNode = lastQueueElem->next;
		while (tmpNode != firstQueueElem) {
			tmpNode->value = nullptr;
			tmpNode = tmpNode->next;
		}
	}
}

template <class T>
void ListBasedFIFOQueue<T>::garbageHard() {
	if (isQueueEmpty) {
		if (list.getSize()) {
			while (list.getSize()) {
				list.delFront();
			}
		}
	}
	else {
		while (lastQueueElem->next != firstQueueElem) {
			list.delNode(lastQueueElem->next);
		}
	}
}

template <class T>
ListBasedFIFOQueue<T>::~ListBasedFIFOQueue() {
	firstQueueElem = lastQueueElem = nullptr;
}

#endif