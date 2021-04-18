#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "ListBasedFIFOQueue.h"
#define MAX_ACTION_LENGTH 14
#define BEGIN 0
#define END 1

void printIntQueue(ListBasedFIFOQueue<int>& queue) {
	if (queue.getFirstQueueElem()) {
		DoubleLinkedNode<int> *tmpNode = queue.getFirstQueueElem(),
			*endNode = queue.getLastQueueElem();
		while (tmpNode != endNode) {
			printf("%d ", *tmpNode->value);
			tmpNode = tmpNode->next;
		}
		printf("%d \n", *endNode->value);
	}
	else {
		printf("NULL\n");
	}
}

void printIntList(ListBasedFIFOQueue<int>& queue, bool direction) {
	if (queue.getFirstListElem()) {
		DoubleLinkedNode<int>* tmpNode, * endNode;
		if (direction == BEGIN) {
			tmpNode = queue.getFirstListElem();
			endNode = queue.getLastListElem();
		}
		else {
			tmpNode = queue.getLastListElem();
			endNode = queue.getFirstListElem();
		}
		while (tmpNode != endNode) {
			if (tmpNode->value == nullptr) {
				printf("0 ");
			}
			else {
				printf("%d ", *tmpNode->value);
			}
			if (direction == BEGIN) {
				tmpNode = tmpNode->next;
			}
			else if (direction == END) {
				tmpNode = tmpNode->previous;
			}
		}
		if (endNode->value == nullptr) {
			printf("0 \n");
		}
		else {
			printf("%d \n", *endNode->value);
		}
	}
	else {
		printf("NULL\n");
	}
}


int main() {
	ListBasedFIFOQueue<int>  queue;
	char* action = new char[MAX_ACTION_LENGTH];
	int input, *output;
	while (scanf("%s", action) != EOF) {
		if (!strcmp(action, "PUSH")) {
			scanf("%d", &input);
			queue.pushBack(new int(input));
		}
		else if (!strcmp(action, "POP")) {
			output = queue.popFirst();
			if (output == nullptr) {
				printf("NULL\n");
			}
			else {
				printf("%d\n",*output);
			}
		}
		else if (!strcmp(action, "PRINT_QUEUE")) {
			printIntQueue(queue);
		}
		else if (!strcmp(action, "COUNT")) {
			printf("%d\n",queue.getQueueSize());
		}
		else if (!strcmp(action, "GARBAGE_SOFT")) {
			queue.garbadeSoft();
		}
		else if (!strcmp(action, "GARBAGE_HARD")) {
			queue.garbageHard();
		}
		else if (!strcmp(action, "SIZE")) {
			printf("%d\n", queue.getListSize());
		}
		else if (!strcmp(action, "ADD_BEG")) {
			scanf("%d", &input);
			queue.addListBegin(new int(input));
		}
		else if (!strcmp(action, "ADD_END")) {
			scanf("%d", &input);
			queue.addListEnd(new int(input));
		}
		else if (!strcmp(action, "DEL_BEG")) {
			queue.delListBegin();
		}
		else if (!strcmp(action, "DEL_END")) {
			queue.delListEnd();
		}
		else if (!strcmp(action, "PRINT_FORWARD")) {
			printIntList(queue, BEGIN);
		}
		else if (!strcmp(action, "PRINT_BACKWARD")) {
			printIntList(queue, END);
		}

	}
	//ADD_BEG, ADD_END, DEL_BEG, DEL_END, PRINT_FORWARD, PRINT_BACKWARD
	return 0;
}
