#ifndef HOTELEDA_RECEPTION_H
#define HOTELEDA_RECEPTION_H

#include <vector>
#include "Guest.h"

class Reception {
public:
    vector<Guest> waitingGuests;

    Reception() {
    }

    void addGuests(vector<Guest> &guests) {
        for (auto guest : guests) {
            waitingGuests.push_back(guest);
        }
    }

};

#endif //HOTELEDA_RECEPTION_H
