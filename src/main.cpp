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

vector<Guest> generateReservationGuests() {
    int reservationId = rand() % 1000000;
    int reservationDuration = rand() % 10 + 1;
    int numGuests = rand() % 8 + 1;

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

void doHotelCycle(Hotel &hotel) {
    // kickGuestsFromRooms();
    // addGuestsToRooms();
    // processIncomingGuests();
    generateReservationGuests();

}

void loadFiles() {
    string namesPath("values/nome.txt"), famsPath("values/familia.txt"), natsPath("values/nacionalidade.txt");
    loadFileToVector(nomes, namesPath);
    loadFileToVector(familias, famsPath);
    loadFileToVector(nacionalidades, natsPath);
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    loadFiles();    // load default names to global name vectors
    cout << nomes.size() << " names | " << familias.size() << " fams | " << nacionalidades.size() << " nats" << endl;

    string hotelDataFile;
    if (argc > 1) {
        loadHotel(hotel, argv[1]);
    } else {
        // initialize with random values
        hotel.initialize();
    }


    menuMain(hotel);

    int cmd;
    while (true) {
        cmd = getchar();

        if (cmd == 'x') break;

        switch (cmd) {
            case 'o':
                menuOptions();
                break;
            case 'g':
                saveHotel(hotel, "hotel.txt");
                break;
            case 's':
                doHotelCycle(hotel);
                menuMain(hotel);
                break;
            case '0':
                menuMain(hotel);
                break;
        }

    }

    return 0;
}
