#pragma once

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

void saveHotel(Hotel *hotel, const char *filename) {
    ofstream outfile(filename);
    outfile << "H " << hotel;

	for (int i = 0; i < hotel->numRooms; i++) {
		outfile << "R " << hotel->rooms[i];
		for (GuestNode *node = listPeek(hotel->rooms[i]->guestList); node != nullptr; node = node->next) {
			outfile << "G " << node->guest;
		}
	}

	for (GuestNode *node = listPeek(hotel->reception); node != nullptr; node = node->next) {
		outfile << "W " << node->guest;
	}
}

void loadHotel(Hotel *hotel, const char *filename) {
    ifstream infile(filename);
    string str;
	
	clearHotel(hotel);

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
			Room *room = newRoom(number, capacity);
			addRoomToHotel(hotel, room, number-1);
        } else if (str == "W") {
            cout << "read Waiting guest" << endl;
            string name, familyName, nationality;
            int reservationId, duration;
            infile >> name >> familyName >> reservationId >> duration;
            getline(infile, nationality);
            trimLine(nationality);
			Guest *guest = newGuest(name, familyName, name, reservationId, duration);
			addGuestToReception(hotel, guest);
        }
    }
}
