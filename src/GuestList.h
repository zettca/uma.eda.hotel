#pragma once

#include "Guest.h"

using namespace std;

/*
* Linked List used for Hotel Guests
* implemented as FIFO (First-in, First-out)
*/

typedef struct GuestNode {
	Guest *guest;
	GuestNode *prev, *next;
} Node;

typedef struct GuestList {
	GuestNode *head, *tail;
} GuestList;

GuestList *newGuestList() {
	GuestList *guestList = (GuestList*)malloc(sizeof(GuestList));
	guestList->head = (guestList->tail = nullptr);
	return guestList;
}

bool isListEmpty(GuestList *guestList) {
	return (guestList->head == nullptr);
}

GuestNode *createNode(Guest *guest) {
	GuestNode *node = (GuestNode*)malloc(sizeof(GuestNode));
	node->guest = guest;
	node->prev = (node->next = nullptr);
	return node;
}

void listPush(GuestList *guestList, Guest *guest) { // add node to tail (end)
	GuestNode *node = createNode(guest);

	if (isListEmpty(guestList)) {
		guestList->head = (guestList->tail = node);
	} else {
		node->prev = guestList->tail;
		guestList->tail->next = node;
		guestList->tail = guestList->tail->next;
	}
}

void addGuest(GuestList *guestList, Guest *guest) {
	listPush(guestList, guest);
}

Guest *listPop(GuestList *guestList) { // remove node from head (start)
	GuestNode *temp = guestList->head;
	guestList->head = guestList->head->next;
	return temp->guest;
}

GuestNode *listPeek(GuestList *guestList) { // get node from start, without removing it
	return guestList->head;
}

int listSize(GuestList *guestList) {
	int size = 0;

	for (GuestNode *node = listPeek(guestList); node != nullptr; node = node->next) {
		size++;
	}

	return size;
}

void listClear(GuestList *guestList) {
	while (guestList->head != nullptr) listPop(guestList);
}

void listDestroy(GuestList *guestList) {
	listClear(guestList);
	free(guestList);
}
