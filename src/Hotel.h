#ifndef HOTELEDA_HOTEL_H
#define HOTELEDA_HOTEL_H

#include <vector>
#include "Room.h"
#include "Reception.h"

class Hotel {
public:
    int numRooms;
    std::vector<Room> rooms;
    Reception reception;

    Hotel() {}

    Hotel(int rooms) : numRooms(rooms) {
    }

    void initialize() {
        for (int i = 0; i < numRooms; ++i) {
            rooms.push_back(Room());
        }
    }

    void addRoom(Room &room) {
        rooms.push_back(room);
    }
};

ostream &operator<<(ostream &os, const Hotel &hotel) {
    os << "H " << hotel.numRooms << endl;
    return os;
}

#endif //HOTELEDA_HOTEL_H
