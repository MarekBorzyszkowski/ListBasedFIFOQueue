#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "XOR_Node.h"
#include "XOR_list.h"

#define BEGINNING 0
#define ENDING 1
#define PREVIOUS 0
#define NEXT 1

XOR_List::XOR_List() {
	beginning = nullptr;
	ending = nullptr;
	actual = nullptr;
	next = nullptr;
	previous = nullptr;
	newNode = nullptr;
	listSize = 0;
}

int XOR_List::getListSize() {
	return listSize;
}

int XOR_List::ACTUAL() {
	if (actual == nullptr) {
		return NULL;
	}
	else {
		return actual->value;
	}
}

int XOR_List::ACTUAL_NEIGHBOR(bool neighborSelected) {
	if (beginning == nullptr) {
		return NULL;
	}
	else if (beginning == ending) {
		return actual->value;
	}
	else if (neighborSelected == PREVIOUS) {
		if (actual == beginning) {
			previous = (XOR_Node*)ending->xorValue;
			actual = ending;
			next = nullptr;
			return ending->value;
		}
		previous = (XOR_Node*)(previous->xorValue ^ (lint)actual);
		actual = (XOR_Node*)(actual->xorValue ^ (lint)next);
		next = (XOR_Node*)((lint)previous ^ actual->xorValue);
		return actual->value;
	}
	else if (neighborSelected == NEXT) {
		if (actual == ending) {
			previous = nullptr;
			actual = beginning;
			next = (XOR_Node*)beginning->xorValue;
			return beginning->value;
		}
		next = (XOR_Node*)(next->xorValue ^ (lint)actual);
		actual = (XOR_Node*)(actual->xorValue ^ (lint)previous);
		previous = (XOR_Node*)((lint)next ^ actual->xorValue);
		return actual->value;
	}
}

void XOR_List::createFirstNode(int value) {
	beginning = new XOR_Node;
	beginning->value = value;
	beginning->xorValue = 0;
	ending = actual = beginning;
	next = previous = nullptr;
	listSize = 1;
}

void XOR_List::ADD_OUTSKIRT(int value, bool addTo) {
	if (beginning == nullptr) {
		createFirstNode(value);
		return;
	}
	if (addTo == BEGINNING) {
		pointerToPointer = &beginning;
	}
	else if (addTo == ENDING) {
		pointerToPointer = &ending;
	}
	listSize++;
	newNode = new XOR_Node;
	newNode->value = value;
	newNode->xorValue = ((lint)nullptr ^ (lint)*pointerToPointer);
	(*pointerToPointer)->xorValue = ((lint)((*pointerToPointer)->xorValue) ^ (lint)newNode);
	*pointerToPointer = newNode;
	if ((*pointerToPointer)->xorValue == (lint)actual && addTo == BEGINNING) { previous = *pointerToPointer; }
	else if ((*pointerToPointer)->xorValue == (lint)actual && addTo == ENDING) { next = *pointerToPointer; }
}

void XOR_List::ADD_ACTUAL(int value) {
	if (beginning == nullptr) {
		createFirstNode(value);
		return;
	}
	listSize++;
	tmpNode = new XOR_Node;
	tmpNode->value = value;
	tmpNode->xorValue = (lint)previous ^ (lint)actual;
	if (actual == beginning) {
		previous = beginning = tmpNode;
	}
	else {
		lint prevOfPrev = previous->xorValue ^ (lint)actual;
		previous->xorValue = prevOfPrev ^ (lint)tmpNode;
		previous = tmpNode;
	}
	actual->xorValue = (lint)previous ^ (lint)next;
}

int XOR_List::DEL_OUTSKIRT(bool delPoint) {
	if (beginning == nullptr) { return NULL; }
	listSize--;
	int deletedValue;
	if (beginning == ending) {
		deletedValue = beginning->value;
		delete beginning;
		beginning = ending = actual = next = previous = nullptr;
	}
	else if (delPoint == BEGINNING) {
		if (actual == beginning) {
			previous = (XOR_Node*)ending->xorValue;
			actual = ending;
			next = nullptr;
		}
		if (previous == beginning) {
			previous = nullptr;
		}
		deletedValue = beginning->value;
		tmpNode = (XOR_Node*)beginning->xorValue;
		tmpNode->xorValue = tmpNode->xorValue ^ (lint)beginning;
		delete beginning;
		beginning = tmpNode;
	}
	else if (delPoint == ENDING) {
		if (actual == ending) {
			actual = (XOR_Node*)ending->xorValue;
			previous = (XOR_Node*)(actual->xorValue ^ (lint)ending);
			next = nullptr;
		}
		if (next == ending) {
			next = nullptr;
		}	
		deletedValue = ending->value;
		tmpNode = (XOR_Node*)ending->xorValue;
		tmpNode->xorValue = tmpNode->xorValue ^ (lint)ending;
		delete ending;
		ending = tmpNode;
	}
	return deletedValue;
}

int XOR_List::DEL_ACT() {
	if (beginning == nullptr) { return NULL; }
	listSize--;	
	int deletedValue;
	if (actual == beginning) {
		deletedValue = DEL_OUTSKIRT(BEGINNING);
	}
	else if (actual == ending) {
		deletedValue = DEL_OUTSKIRT(ENDING);
	}
	else {
		deletedValue = actual->value;
		lint prevOfPrev, nextOfNext;
		prevOfPrev = previous->xorValue ^ (lint)actual;
		nextOfNext = (lint)actual ^ next->xorValue;
		delete actual;
		actual = previous;
		previous = (XOR_Node*)prevOfPrev;
		actual->xorValue = (lint)previous ^ (lint)next;
		next->xorValue = (lint)actual ^ nextOfNext;
	}
	return deletedValue;
}

void XOR_List::DEL_VAL(int value) {
	while (beginning->value == value) {
		listSize--;
		DEL_OUTSKIRT(BEGINNING);
		if (beginning == nullptr) return;
	}
	XOR_Node* nodeToDelete = (XOR_Node*)beginning->xorValue;
	lint prev, nextToCheck, prevOfPrev, nextOfNext;
	prev = (lint)beginning;
	nextToCheck = prev ^ nodeToDelete->xorValue;
	while (nextToCheck != 0) {
		if (nodeToDelete->value == value) {
			listSize--;
			if (nodeToDelete == beginning) {
				DEL_OUTSKIRT(BEGINNING);
				if (beginning == nullptr) return;
				nodeToDelete = (XOR_Node*)beginning->xorValue;
				prev = (lint)beginning;
				nextToCheck = prev ^ nodeToDelete->xorValue;
				continue;
			}
			else if (nodeToDelete == actual) {
				DEL_ACT();
				prev = (lint)previous;
				nodeToDelete = actual;
				nextToCheck = (lint)next;
				if (beginning == nullptr) return;
				continue;
			}
			else if (nodeToDelete == previous) {
				prevOfPrev = (lint)(((XOR_Node*)prev)->xorValue) ^ (lint)nodeToDelete;
				((XOR_Node*)prev)->xorValue = prevOfPrev ^ (lint)actual;
				previous = (XOR_Node*)prev;
				actual->xorValue = (lint)previous ^ (lint)next;
				delete nodeToDelete;

				nodeToDelete = actual;
				nextToCheck = (lint)next;
				continue;
			}
			else if (nodeToDelete == next) {
				nextOfNext = (lint)(((XOR_Node*)nextToCheck)->xorValue) ^ (lint)nodeToDelete;
				((XOR_Node*)nextToCheck)->xorValue = (lint)actual ^ nextOfNext;
				next = (XOR_Node*)nextToCheck;

				actual->xorValue = (lint)previous ^ (lint)next;
				delete nodeToDelete;
				nodeToDelete = next;
				nextToCheck = prev ^ nodeToDelete->xorValue;
				continue;
			}
			else {
				prevOfPrev = (lint)(((XOR_Node*)prev)->xorValue) ^ (lint)nodeToDelete;
				((XOR_Node*)prev)->xorValue = prevOfPrev ^ nextToCheck;

				nextOfNext = (lint)(((XOR_Node*)nextToCheck)->xorValue) ^ (lint)nodeToDelete;
				((XOR_Node*)nextToCheck)->xorValue = prev ^ nextOfNext;

				delete nodeToDelete;
				nodeToDelete = (XOR_Node*)nextToCheck;
				nextToCheck = nextOfNext;
				continue;
			}
		}
		prev = (lint)nodeToDelete;
		nodeToDelete = (XOR_Node*)nextToCheck;
		nextToCheck = prev ^ nodeToDelete->xorValue;
	}
	while (ending->value == value) {
		listSize--;
		DEL_OUTSKIRT(ENDING);
		if (ending == nullptr) return;
	}
}

void XOR_List::PRINT(bool startFrom) {
	if (beginning == nullptr) {
		printf("NULL\n");
		return;
	}
	lint prev = 0, nextToPrint;
	if (startFrom == BEGINNING) {
		nextToPrint = beginning->xorValue;
		tmpNode = beginning;
	}
	else if (startFrom == ENDING) {
		nextToPrint = ending->xorValue;
		tmpNode = ending;
	}
	printf("%d ", tmpNode->value);
	while (nextToPrint != (prev ^ 0)) {
		nextToPrint = prev ^ nextToPrint;
		prev = (lint)tmpNode;
		tmpNode = (XOR_Node*)nextToPrint;
		nextToPrint = tmpNode->xorValue;
		printf("%d ", tmpNode->value);
	}
	printf("\n");
}

XOR_List::~XOR_List() {
	if (beginning != nullptr) {
		lint prev = 0, nextToDelete = beginning->xorValue;
		tmpNode = beginning;
		while (nextToDelete != (prev ^ 0)) {
			nextToDelete = prev ^ nextToDelete;
			prev = (lint)tmpNode;
			delete tmpNode;
			tmpNode = (XOR_Node*)nextToDelete;
			nextToDelete = tmpNode->xorValue;
		}
		delete tmpNode;
	}
	beginning = ending = actual = previous = next = tmpNode = newNode = nullptr;
	pointerToPointer = nullptr;
}