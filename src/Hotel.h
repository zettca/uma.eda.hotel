#ifndef HOTELEDA_HOTEL_H
#define HOTELEDA_HOTEL_H

#include <vector>
#include <algorithm>
#include "Room.h"
#include "Reception.h"

class Hotel {
public:
    int numRooms;
    std::vector<Room> rooms;
    Reception reception;

    Hotel() {}

    Hotel(int numRooms) : numRooms(numRooms) {}

    void addRoom(Room &room) {
        rooms.push_back(room);
    }

    void initializeRandom() {
        numRooms = rand() % 10 + 10;
        for (int i = 0; i < numRooms; ++i) {
            Room room;
            room.initializeRandom();
            addRoom(room);
        }
    }

    void clearRoom(int numRoom) {
        for (auto &room : rooms) {
            if (room.number == numRoom) {
                room.clear();
                break;
            }
        }
    }

    void changeReservations(int reservationId, int numDays) {
        for (auto &room : rooms) {
            for (auto &guest : room.guests) {
                if (guest.reservationId == reservationId) {
                    guest.duration = numDays;
                }
            }
        }

        for (auto &guest : reception.waitingGuests) {
            if (guest.reservationId == reservationId) {
                guest.duration = numDays;
            }
        }
    }

    static bool sortByFirstName(Guest &g1, Guest &g2) {
        return g1.name < g2.name;
    }

    void sortAndPrint(vector<Guest> guests) {
        sort(guests.begin(), guests.end(), sortByFirstName);

        for (auto &guest : guests) {
            cout << guest.name << " " << guest.familyName << " (" << guest.reservationId << ")" << endl;
        }
    }

    void displayForeignerGuests() {
        vector<Guest> guests;
        for (auto &room : rooms) {
            for (auto &guest : room.guests) {
                if (guest.nationality != "Portugal") {
                    guests.push_back(guest);
                }
            }
        }

        sortAndPrint(guests);
    }

    void displayPortugueseSAGuests() {
        vector<Guest> guests;
        for (auto &room : rooms) {
            for (auto &guest : room.guests) {
                if (guest.nationality == "Portugal" || guest.nationality == "South Africa") {
                    guests.push_back(guest);
                }
            }
        }
        sortAndPrint(guests);
    }

    void clear() {
        rooms.clear();
        reception.clear();
    }
};

ostream &operator<<(ostream &os, const Hotel &hotel) {
    os << hotel.numRooms << endl;
    return os;
}

#endif //HOTELEDA_HOTEL_H
