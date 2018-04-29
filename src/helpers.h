#ifndef HOTELEDA_HELPERS_H
#define HOTELEDA_HELPERS_H

#include <string>
#include <vector>
#include <fstream>
#include "Hotel.h"

using namespace std;

void loadFileToVector(vector<string> &vector, string &filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            vector.push_back(line);
        }
    }
}

void saveHotel(Hotel &hotel, const char *file) {
    ofstream outfile(file);
    outfile << hotel;

    for (auto room : hotel.rooms) {
        outfile << room;
        for (auto guest : room.guests) {
            outfile << guest;
        }
    }

    for (auto guest : hotel.reception.waitingGuests) {
        outfile << guest;
    }
}

void loadHotel(Hotel &hotel, const char *file) {
    ifstream infile(file);
    string line;

    while (getline(infile, line)) {
        if (!line.empty()) {

        }
    }
}

#endif //HOTELEDA_HELPERS_H
