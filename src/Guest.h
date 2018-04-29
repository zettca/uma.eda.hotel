#ifndef HOTELEDA_GUEST_H
#define HOTELEDA_GUEST_H

#include <string>
#include <ostream>

using namespace std;

class Guest {
public:
    string name, familyName, nationality;
    int reservationId, reservationDuration;

    Guest(string &name, string &familyName, string &nationality, int reservationId, int reservationDuration)
            : name(name), familyName(familyName), nationality(nationality), reservationId(reservationId),
              reservationDuration(reservationDuration) {}
};

ostream &operator<<(ostream &os, const Guest &guest) {
    os << "G " << guest.name << " " << guest.familyName << " " << guest.nationality << " " <<
       guest.reservationId << " " << guest.reservationDuration << endl;
    return os;
}

#endif //HOTELEDA_GUEST_H
