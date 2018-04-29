#ifndef HOTELEDA_HELPERS_H
#define HOTELEDA_HELPERS_H

#include <string>
#include <vector>
#include <fstream>
#include "Hotel.h"

using namespace std;

void loadFileToVector(vector<string> &vector, const char *filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            // remove whitespace
            for (char c = line.back(); c == '\r' || c == '\t' || c == ' '; c = line.back()) {
                line.pop_back();
            }
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
    string line;

    hotel.clear();

    while (getline(infile, line)) {
        if (!line.empty()) {
            char c = line.at(0);


            //TODO: finish loading state from file
            if (c == 'H') { // H _numRooms
                // should be first, do nothing
            } else if (c == 'R') { // R _id _cap _numGuests
                // parse line, read N guests inside
                // G (person)
            } else if (c == 'W') { // W (person)
                // parse line, add
            }


        }
    }
}

#endif //HOTELEDA_HELPERS_H
