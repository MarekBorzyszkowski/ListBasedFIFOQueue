#include "DoubleLinkedNode.h"

DoubleLinkedNode<class T>::DoubleLinkedNode() {
	previous = next = nullptr;
}

DoubleLinkedNode<class T>::DoubleLinkedNode(T* data, DoubleLinkedNode* previous, DoubleLinkedNode* next) {
	value = data;
	this->previous = previous;
	this->next = next;
}
