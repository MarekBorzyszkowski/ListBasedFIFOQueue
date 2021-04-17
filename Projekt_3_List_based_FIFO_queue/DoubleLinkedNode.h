#pragma once
#include "Node.h"

template <class T> class DoubleLinkedNode : public Node<T> {
public:
	DoubleLinkedNode* previous, * next;

	DoubleLinkedNode();

	DoubleLinkedNode(T*, DoubleLinkedNode*, DoubleLinkedNode*);
};