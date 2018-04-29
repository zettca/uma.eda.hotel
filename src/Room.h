#ifndef HOTELEDA_ROOM_H
#define HOTELEDA_ROOM_H

#include <cstdlib>
#include <ctime>
#include "Guest.h"

class Room {
public:
    static int counter;
    const int number;
    int capacity;

    vector<Guest> guests;

    Room() : number(++counter) {
        initialize();
    }

    void initialize() {
        capacity = (rand() % 5) + 1;
    }

    void addGuests(vector<Guest> guests) {
        for (auto guest : guests) {
            this->guests.push_back(guest);
        }
    }

    void clear() {
        this->guests.clear();
    }
};

int Room::counter = 0;

ostream &operator<<(ostream &os, const Room &room) {
    os << "R " << room.number << " " << room.capacity << " " << room.guests.size() << endl;
    return os;
}

#endif //HOTELEDA_ROOM_H
