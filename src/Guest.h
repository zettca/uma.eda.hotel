#pragma once

#include <string>
#include <ostream>

using namespace std;

typedef struct Guest {
	string name, familyName, nationality;
	int reservationId, duration, waitTime;
} Guest;

Guest *newGuest(string name, string familyName, string nat, int reservationId, int numDays) {
	cout << "Creating Guest: " << name << familyName << nat << endl;
	Guest *guest = new Guest();
	guest->name = name;
	guest->familyName = familyName;
	guest->nationality = nat;
	guest->reservationId = reservationId;
	guest->duration = numDays;
	guest->waitTime = 0;
	return guest;
}

ostream &operator<<(ostream &os, const Guest &guest) {
	os << guest.name << " " << guest.familyName << " " << guest.reservationId << " " << guest.duration << endl;
	os << guest.nationality << endl;
	return os;
}
