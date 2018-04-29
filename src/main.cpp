#include <string>
#include <iostream>
#include <vector>
#include "Room.h"
#include "../GuestList.h"
#include "Hotel.h"
#include "menus.h"
#include "helpers.h"

using namespace std;

vector<int> ids;
vector<string> names, families, nationalities;
Hotel hotel;

int generateReservationId() {
    int id = rand() % 900000 + 100000; // 6 digit number
    while (find(ids.begin(), ids.end(), id) != ids.end()) {
        id = rand() % 900000 + 100000;
    }
    return id;
}

vector<Guest> generateGuests(int numGuests) {
    vector<Guest> guests;

    while (numGuests > 0) {
        // generate a group
        int reservationId = generateReservationId();
        int reservationDuration = rand() % 10 + 1;
        int reservationGuestNum = rand() % 8 + 1;
        numGuests -= reservationGuestNum;

        // add whole group if possible, else add remainder
        int numToAdd = (numGuests >= 0) ? reservationGuestNum : reservationGuestNum + numGuests;
        for (int i = 0; i < numToAdd; ++i) {
            string givenName = names.at(rand() % names.size());
            string familyName = families.at(rand() % families.size());
            string nationality = nationalities.at(rand() % nationalities.size());

            Guest guest(givenName, familyName, nationality, reservationId, reservationDuration);
            guests.push_back(guest);
        }
    }

    return guests;
}

void fillHotelWithGuests() {
    for (auto &room : hotel.rooms) {
        for (auto &guest : generateGuests(room.capacity)) {
            room.addGuest(guest);
        }
    }
}

void doHotelCycle() {
    // decrement number of days, removing guest if 0
    for (auto &room : hotel.rooms) {
        for (unsigned long i = 0; i < room.guests.size(); ++i) {
            auto &guest = room.guests.at(i);
            guest.duration -= 1;
            if (guest.duration <= 0) {
                room.guests.erase(room.guests.begin() + i);
            }
        }
    }

    // assign waiting guests (a FIFO queue ) to available rooms
    for (auto &room : hotel.rooms) {
        if (hotel.reception.waitingGuests.empty()) break;
        if (room.isAvailable()) {
            int numToAdd = min(room.capacity, (int) hotel.reception.waitingGuests.size());
            for (int i = 0; i < numToAdd; ++i) {
                room.addGuest(hotel.reception.popGuest());
            }
        }
    }

    // increment wait times, remove if waited too long
    hotel.reception.processWaits();

    // add new guests to reception
    for (auto &guest : generateGuests(hotel.numRooms / 2)) {
        hotel.reception.addGuest(guest);
    }
}

/* ========== MAIN ========== */

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    // load default names to global name vectors
    loadFileToVector(names, "values/nome.txt");
    loadFileToVector(families, "values/familia.txt");
    loadFileToVector(nationalities, "values/nacionalidade.txt");

    if (argc > 1) {
        loadHotel(hotel, argv[1]);  // load hotel from file
        cout << "Loaded hotel data from file: " << argv[1] << endl;
    } else {
        hotel.initializeRandom();   // initializeRandom with random values
        fillHotelWithGuests();  // fill on first iteration
    }

    menuMain(hotel);

    string line;
    while (true) {
        cin >> line;
        char cmd = line.front();

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
                doHotelCycle();
                break;
            default:
                break;
        }
        menuMain(hotel);
    }

    return 0;
}
