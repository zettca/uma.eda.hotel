#pragma once

#include <vector>
#include <algorithm>
#include "Room.h"

using namespace std;

int WAIT_THRESHOLD = 1;

typedef struct Hotel {
	int numRooms;
	Room *rooms[32];
	GuestList *reception;
} Hotel;

void addRoomToHotel(Hotel *hotel, Room *room, int i) {
	hotel->rooms[i] = room;
}

Hotel *newHotel(int num) {
	Hotel *hotel = new Hotel();
	hotel->numRooms = num;
	for (int i = 0; i < num; i++) addRoomToHotel(hotel, newRoom(), i);
	hotel->reception = new GuestList();
	return hotel;
}

Hotel *newHotel() {
	random_device rd;
	mt19937 gen(rd());

	int numRooms = gen() % 10 + 10; // random between 10 and 20
	return newHotel(numRooms);
}

void clearHotelRoom(Hotel *hotel, int numRoom) {
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		if (room->number == numRoom) {
			clearRoom(room);
		}
	}
}

void addGuestToReception(Hotel *hotel, Guest *guest) {
	addGuest(hotel->reception, guest);
}

void changeReservation(Hotel *hotel, int reservationId, int numDays) {
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			if (node->guest->reservationId == reservationId) {
				node->guest->duration = numDays;
			}
		}
	}
}

bool sortByFirstName(Guest *g1, Guest *g2) {
	return g1->name < g2->name;
}

void sortAndPrint(vector<Guest*> guests) {
	sort(guests.begin(), guests.end(), sortByFirstName);

	for (auto &guest : guests) {
		cout << guest->name << " " << guest->familyName << " (" << guest->reservationId << ")" << endl;
	}
}

void sortAndPrintGuests(Hotel *hotel, GuestList *guests) {

	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			cout << node->guest;
		}
	}
}

void displayForeignerGuests(Hotel *hotel) {
	vector<Guest*> guests;
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			if (node->guest->nationality != "Portugal") {
				guests.push_back(node->guest);
			}
		}
	}

	sortAndPrint(guests);
}

void displayPortugueseSAGuests(Hotel *hotel) {
	vector<Guest*> guests;
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			string nat = node->guest->nationality;
			if (nat == "Portugal" || nat == "South Africa") {
				guests.push_back(node->guest);
			}
		}
	}
	sortAndPrint(guests);
}

void searchForeignerGuests(Hotel *hotel, string name) {
	vector<Guest*> guests;
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			if (node->guest->name == name && node->guest->nationality != "Portugal") {
				guests.push_back(node->guest);
			}
		}
	}

	sortAndPrint(guests);
}

void searchPortugueseSAGuests(Hotel *hotel, string name) {
	vector<Guest*> guests;
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			string nat = node->guest->nationality;
			if (node->guest->name == name && (nat == "Portugal" || nat == "South Africa")) {
				guests.push_back(node->guest);
			}
		}
	}

	sortAndPrint(guests);
}

void processReceptionWaits(Hotel *hotel) {
	GuestList *newList = newGuestList();
	for (GuestNode *node = listPeek(hotel->reception); node != nullptr; node = node->next) {
		Guest *guest = node->guest;
		guest->waitTime++;
		if (guest->waitTime <= WAIT_THRESHOLD) {
			listPush(newList, guest);
		}
	}

	hotel->reception = newList;
}

void clearReception(Hotel *hotel) {
	listClear(hotel->reception);
}

void clearHotel(Hotel *hotel) {
	clearReception(hotel);
	for (int i = 0; i < hotel->numRooms; i++) {
		clearHotelRoom(hotel, i);
	}
	counter = 0;
}

ostream &operator<<(ostream &os, const Hotel &hotel) {
	os << hotel.numRooms << endl;
	return os;
}
