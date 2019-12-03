#ifndef HOTELEDA_RECEPTION_H
#define HOTELEDA_RECEPTION_H

#include <deque>
#include "Guest.h"

class Reception {
private:
    int WAIT_THRESHOLD = 1;
public:
    deque <Guest> waitingGuests;

    Reception() {}

    void addGuest(Guest &guest) {
        waitingGuests.push_back(guest);
    }

    void processWaits() {
        deque <Guest> guests; // guests
        for (auto &guest : waitingGuests) {
            guest.waitTime++;
            if (guest.waitTime <= WAIT_THRESHOLD) {
                guests.push_back(guest);
            }
        }
        waitingGuests = guests;
    }

    Guest &popGuest() {
        Guest &guest = waitingGuests.front();
        waitingGuests.pop_front();
        return guest;
    }

    void clear() {
        waitingGuests.clear();
    }
};

#endif //HOTELEDA_RECEPTION_H
