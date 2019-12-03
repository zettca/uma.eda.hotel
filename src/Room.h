#pragma once

#include <cstdlib>
#include <ctime>
#include "Guest.h"
#include "GuestList.h"

using namespace std;

static int counter = 0;

typedef struct Room {
	int number, capacity;
	GuestList *guestList;
} Room;

Room *newRoom(int num, int cap) {
	Room *room = new Room();
	room->number = num;
	room->capacity = cap;
	room->guestList = newGuestList();
	return room;
}

Room *newRoom() {
	random_device rd;
	mt19937 gen(rd());

	int cap = gen() % 5 + 1;
	return newRoom(++counter, cap);
}

bool isRoomAvailable(Room *room) {
	return isListEmpty(room->guestList);
}

void addGuestToRoom(Room *room, Guest *guest) {
	addGuest(room->guestList, guest);
}

void printRoom(ostream &os, Room *room) {
	os << room->number << " " << room->capacity << " " << listSize(room->guestList) << endl;
}

void processRoom(Room *room) {
	GuestList *newList = newGuestList();
	for (GuestNode *node = room->guestList->head; node != nullptr; node = node->next) {
		node->guest->duration -= 1;
		if (node->guest->duration >= 0) {
			listPush(newList, node->guest);
		}
	}
	listDestroy(room->guestList);
	room->guestList = newList;
}

void clearRoom(Room *room) {
	listClear(room->guestList);
}

ostream &operator<<(ostream &os, const Room &room) {
	os << room.number << " " << room.capacity << " " << listSize(room.guestList) << endl;
	return os;
}
