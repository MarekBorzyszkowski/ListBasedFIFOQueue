#pragma once
#include "XOR_Node.h"

class XOR_List {
public:
	XOR_List();

	int getListSize();

	int ACTUAL();
	int ACTUAL_NEIGHBOR(bool neighborSelected);

	void createFirstNode(int value);
	void ADD_OUTSKIRT(int value, bool addTo);
	void ADD_ACTUAL(int value);

	int DEL_OUTSKIRT(bool delPoint);
	int DEL_ACT();
	void DEL_VAL(int value);

	void PRINT(bool startFrom);

	~XOR_List();
private:
	XOR_Node* beginning, * ending, * actual, * next, * previous;
	XOR_Node* newNode, * tmpNode;
	XOR_Node** pointerToPointer;
	int listSize;
};