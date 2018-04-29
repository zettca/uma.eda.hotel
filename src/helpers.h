#ifndef HOTELEDA_HELPERS_H
#define HOTELEDA_HELPERS_H

#include <string>
#include <vector>
#include <fstream>
#include "Hotel.h"

using namespace std;

void trimLine(string &line) {
    for (char c = line.back(); c == '\r' || c == '\t' || c == ' '; c = line.back()) {
        line.pop_back();
    }
}

void loadFileToVector(vector<string> &vector, const char *filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            trimLine(line); // remove whitespace
            vector.push_back(line);
        }
    }
}

void saveHotel(Hotel &hotel, const char *file) {
    ofstream outfile(file);
    outfile << "H " << hotel;

    for (auto &room : hotel.rooms) {
        outfile << "R " << room;
        for (auto &guest : room.guests) {
            outfile << "G " << guest;
        }
    }

    for (auto &guest : hotel.reception.waitingGuests) {
        outfile << "W " << guest;
    }
}

void loadHotel(Hotel &hotel, const char *file) {
    ifstream infile(file);
    string str;

    hotel.clear();

    while (!infile.eof()) {
        infile >> str;

        if (str == "H") {
            int numRooms;
            infile >> numRooms;
            cout << "read Hotel" << endl;
        } else if (str == "R") { // read room line
            int number, capacity, numGuests;
            infile >> number >> capacity >> numGuests;
            cout << "read Room " << number << endl;
            Room room(number, capacity);
            hotel.addRoom(room);
            //TODO: fix loading room guests
            /*for (int i = 0; i < numGuests; ++i) { // read room guests
                cout << "reading Room guest " << i << endl;
                string code, name, familyName, nationality;
                int reservationId, duration;
                infile >> code >> name >> familyName >> reservationId >> duration;
                getline(infile, nationality);
                trimLine(nationality);
                cout << "read Room guest " << name << endl;
                Guest guest(name, familyName, name, reservationId, duration);
                room.addGuest(guest);
            }*/
        } else if (str == "W") {
            cout << "read Waiting guest" << endl;
            string name, familyName, nationality;
            int reservationId, duration;
            infile >> name >> familyName >> reservationId >> duration;
            getline(infile, nationality);
            trimLine(nationality);
            Guest guest(name, familyName, name, reservationId, duration);
            hotel.reception.addGuest(guest);
        }
    }
}

#endif //HOTELEDA_HELPERS_H
