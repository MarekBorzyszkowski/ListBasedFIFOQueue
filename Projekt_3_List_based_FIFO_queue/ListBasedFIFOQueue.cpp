#define _CRT_SECURE_NO_WARNINGS
#include "ListBasedFIFOQueue.h"
#include <stdio.h>

ListBasedFIFOQueue<class T>::ListBasedFIFOQueue() {
	list;
	firstQueueElem = lastQueueElem = nullptr;
	isQueueEmpty = 1;
}

int ListBasedFIFOQueue<T>::getListSize() {
	return list.getSize();
}

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

T* ListBasedFIFOQueue<T>::popFirst() {
	if (isQueueEmpty) {
		return nullptr;
	}
	else {
		if (firstQueueElem == lastQueueElem) {
			T* resoult = firstQueueElem->value;
			firstQueueElem = lastQueueElem = nullptr;
			isQueueEmpty = 1;
			return resoult;
		}
		else {
			T* resoult = firstQueueElem->value;
			firstQueueElem = firstQueueElem->next;
			return resoult;
		}
	}
}

void ListBasedFIFOQueue<T>::printQueue() {
	if (isQueueEmpty) {
		printf("NULL\n");
	}
	else {
		DoubleLinkedNode<T>* tmpNode = firstQueueElem;
		while (tmpNode != lastQueueElem) {
			//printf(tmpNode->value);
		}
	}
}
