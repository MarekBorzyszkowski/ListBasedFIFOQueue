#ifndef DLN_H
#define DLN_H
#include "Node.h"

template <class T> class DoubleLinkedNode : public Node<T> {
public:
	DoubleLinkedNode* previous, * next;

	DoubleLinkedNode();

	DoubleLinkedNode(T*, DoubleLinkedNode*, DoubleLinkedNode*);
};

template <class T>
DoubleLinkedNode<T>::DoubleLinkedNode() {
	previous = next = nullptr;
	this->value = nullptr;
}

template <class T>
DoubleLinkedNode<T>::DoubleLinkedNode(T* data, DoubleLinkedNode* previous, DoubleLinkedNode* next) {
	this->value = data;
	this->previous = previous;
	this->next = next;
}


#endif