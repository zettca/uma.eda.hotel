#ifndef HOTELEDA_GUEST_H
#define HOTELEDA_GUEST_H

#include <string>
#include <ostream>

using namespace std;

class Guest {
public:
    string name, familyName, nationality;
    int reservationId, duration, waitTime = 0;

    Guest(string &name, string &familyName, string &nat, int reservationId, int numDays)
            : name(name), familyName(familyName), nationality(nat), reservationId(reservationId), duration(numDays) {}
};

ostream &operator<<(ostream &os, const Guest &guest) {
    os << guest.name << " " << guest.familyName << " " << guest.nationality << " " << guest.reservationId <<
       " " << guest.duration << endl;
    return os;
}

#endif //HOTELEDA_GUEST_H
