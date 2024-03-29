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

    Room() : number(++counter) {}

    Room(const int number, int capacity) : number(number), capacity(capacity) {}

    void initializeRandom() {
        capacity = rand() % 5 + 1; // random between 1 and 5
    }

    bool isAvailable() {
        return guests.empty();
    }

    void addGuest(Guest &guest) {
        guests.push_back(guest);
    }

    void clear() {
        this->guests.clear();
    }
};

int Room::counter = 0;

ostream &operator<<(ostream &os, const Room &room) {
    os << room.number << " " << room.capacity << " " << room.guests.size() << endl;
    return os;
}

#endif //HOTELEDA_ROOM_H
