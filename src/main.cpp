#include <string>
#include <iostream>
#include <vector>
#include "Room.h"
#include "../GuestList.h"
#include "Hotel.h"
#include "menus.h"
#include "helpers.h"

using namespace std;

vector<string> nomes, familias, nacionalidades;
Hotel hotel;

vector<Guest> generateGuests(int numGuests) {
    int reservationId = rand() % 1000000;
    int reservationDuration = rand() % 10 + 1;

    vector<Guest> guests;

    for (int i = 0; i < numGuests; ++i) {
        string givenName = nomes.at(rand() % nomes.size());
        string familyName = familias.at(rand() % familias.size());
        string nationality = nacionalidades.at(rand() % nacionalidades.size());

        Guest guest(givenName, familyName, nationality, reservationId, reservationDuration);
        guests.push_back(guest);
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

int getAvailableRoom() {
    for (unsigned int i = 0; i < hotel.rooms.size(); ++i) {
        Room room = hotel.rooms.at(i);
        if (room.isAvailable()) {
            return i;
        }
    };
    return -1;
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

    // assign guests to rooms
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
    loadFileToVector(nomes, "values/nome.txt");
    loadFileToVector(familias, "values/familia.txt");
    loadFileToVector(nacionalidades, "values/nacionalidade.txt");

    if (argc > 1) {
        loadHotel(hotel, argv[1]);  // load hotel from file
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
