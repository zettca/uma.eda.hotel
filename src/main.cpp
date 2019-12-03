#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include "Room.h"
#include "Hotel.h"
#include "menus.h"
#include "helpers.h"

using namespace std;

vector<int> ids;
vector<string> names, families, nationalities;

// set random generator
random_device rd;
mt19937 gen(rd());

int generateReservationId() {
	int id = gen() % 900000 + 100000; // 6 digit number
	while (find(ids.begin(), ids.end(), id) != ids.end()) {
		id = gen() % 900000 + 100000;
	}
	return id;
}

vector<Guest*> generateGuests(int numGuests) {
	vector<Guest*> guests;

	while (numGuests > 0) {
		// generate a group
		int reservationId = generateReservationId();
		int reservationDuration = gen() % 10 + 1;
		int reservationGuestNum = gen() % 8 + 1;
		numGuests -= reservationGuestNum;

		// add whole group if possible, else add remainder
		int numToAdd = (numGuests >= 0) ? reservationGuestNum : reservationGuestNum + numGuests;
		for (int i = 0; i < numToAdd; ++i) {
			string givenName = names.at(gen() % names.size());
			string familyName = families.at(gen() % families.size());
			string nationality = nationalities.at(gen() % nationalities.size());

			Guest *guest = newGuest(givenName, familyName, nationality, reservationId, reservationDuration);
			guests.push_back(guest);
		}
	}

	return guests;
}

void fillHotelWithGuests(Hotel *hotel) {
	for (int i = 0; i < hotel->numRooms; i++) {
		for (auto guest : generateGuests(hotel->rooms[i]->capacity)) {
			addGuestToRoom(hotel->rooms[i], guest);
		}
	}
}

void doHotelCycle(Hotel *hotel) {
	// decrement number of days, removing guest if 0
	for (int i = 0; i < hotel->numRooms; i++) {
		processRoom(hotel->rooms[i]);
	}

	// assign waiting guests (a FIFO queue ) to available rooms
	for (int i = 0; i < hotel->numRooms; i++) {
		if (isListEmpty(hotel->reception)) break;
		Room *room = hotel->rooms[i];
		if (isRoomAvailable(room)) {
			int numToAdd = min(room->capacity, (int)listSize(hotel->reception));
			for (int i = 0; i < numToAdd; ++i) {
				addGuestToRoom(room, listPop(hotel->reception));
			}
		}
	}

	// increment wait times, remove if waited too long
	processReceptionWaits(hotel);

	// add new guests to reception
	for (auto guest : generateGuests(hotel->numRooms / 2)) {
		addGuest(hotel->reception, guest);
	}
}

/* ========== MAIN ========== */

int main(int argc, const char *argv[]) {
	// load default names to global name vectors
	loadFileToVector(names, "values/nome.txt");
	loadFileToVector(families, "values/familia.txt");
	loadFileToVector(nationalities, "values/nacionalidade.txt");
	cout << names.size() << "  " << families.size() << " " << nationalities.size() << endl;

	Hotel *hotel;

	if (argc > 1) {
		loadHotel(hotel, argv[1]);  // load hotel from file
		cout << "Loaded hotel data from file: " << argv[1] << endl;
	} else {
		hotel = newHotel();				// initializeRandom with random values
		fillHotelWithGuests(hotel);		// fill on first iteration
	}

	menuMain(hotel);

	char cmd;
	while (true) {
		cmd = getch();

		if (cmd == 'q' || cmd == 'x') break;

		switch (cmd) {
		case 'o':
			menuOptions(hotel); // opens other menus
			break;
		case 'g':
			saveHotel(hotel, "hotel.txt");
			cout << "Hotel saved to file hotel.txt" << endl;
			waitFor0();
			break;
		case 's':
		case 'M': // code for right arrow
			doHotelCycle(hotel);
			break;
		default:
			cout << cmd << endl;
			break;
		}
		menuMain(hotel);
	}

	return 0;
}
