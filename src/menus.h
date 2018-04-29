#ifndef HOTELEDA_PRINTERS_H
#define HOTELEDA_PRINTERS_H

#include <string>
#include <iostream>

using namespace std;

void printSpace() {
    const int NUM_SPACES = 32;
    for (int i = 0; i < NUM_SPACES; ++i) {
        cout << endl;
    }
}

void printHeader(const char *title) {
    printSpace();
    cout << "---------------" << endl;
    cout << title << endl;
    cout << "---------------" << endl;
}

void printRooms(vector<Room> &rooms) {
    for (auto room : rooms) {
        cout << "QUARTO " << room.number << " (CAPACIDADE " << room.capacity << "): ";
        for (auto &guest : room.guests) {
            cout << guest.familyName << "(" << guest.duration << "|" << guest.reservationId << ") ";
        }
        cout << endl;
    }
}

void printReception(Reception &reception) {
    cout << "Recepção:" << endl;

    for (auto &guest : reception.waitingGuests) {
        cout << guest.familyName << "(" << guest.reservationId << ")" << endl;
    }
}

string &getInput(string &line, const char *message) {
    cout << message;
    cin >> line;
    return line;
}

void waitFor0() {
    cout << "pressione 0 para voltar" << endl;
    while (getchar() != '0');
}

/* ========== MENUS ========== */

void menuMain(Hotel &hotel) {
    printHeader("Hotel EDA");
    printRooms(hotel.rooms);
    cout << "**************" << endl;

    printReception(hotel.reception);

    cout << "---------------------------" << endl;
    cout << "(o)pções (g)ravar (s)seguinte (q)uit" << endl;
}


void menuSearchGuests(Hotel &hotel) {
    printHeader("Hotel EDA - Opções - Pesquisa");

    cout << "1 - Hóspedes de origem estrangeira" << endl;
    cout << "2 - Hóspedes de origem portuguesa ou sul-africana" << endl;
    cout << "0 - Voltar" << endl;
}

void menuDisplayGuests(Hotel &hotel) {
    printHeader("Hotel EDA - Opções - Apresentação");

    cout << "1 - Hóspedes de origem estrangeira" << endl;
    cout << "2 - Hóspedes de origem portuguesa ou sul-africana" << endl;
    cout << "0 - Voltar" << endl;

    string line;
    cin >> line;
    char cmd = line.front();
    printHeader("Hotel EDA - Opções - Apresentação");
    switch (cmd) {
        case '1': { // Hóspedes de origem estrangeira
            hotel.displayForeignerGuests();
            waitFor0();
            break;
        }
        case '2': { // Hóspedes de origem portuguesa ou sul-africana
            hotel.displayPortugueseSAGuests();
            waitFor0();
            break;
        }
        case '0': { // Voltar
            break;
        }
        default:
            break;
    }
}

void menuOptions(Hotel &hotel) {
    printHeader("Hotel EDA - Opções");

    cout << "1 - Limpar Quarto" << endl;
    cout << "2 - Alterar duração de reserva" << endl;
    cout << "3 - Limpar Recepção" << endl;
    cout << "4 - Editar Nacionalidade" << endl;
    cout << "5 - Editar Primeiro Nome" << endl;
    cout << "6 - Pesquisa de hóspedes" << endl;
    cout << "7 - Apresentação" << endl;
    cout << "0 - Voltar" << endl;

    string line;
    cin >> line;
    char cmd = line.front();
    switch (cmd) {
        case '1': { // Limpar Quarto
            int roomNumber = stoi(getInput(line, "Número do quarto a limpar: "));

            hotel.clearRoom(roomNumber);
            break;
        }
        case '2': { // Alterar duração de reserva
            int reservationId = stoi(getInput(line, "ID de reserva a alterar: "));
            int numDays = stoi(getInput(line, "Número de dias: "));

            hotel.changeReservations(reservationId, numDays);
            break;
        }
        case '3': { // Limpar Recepção
            hotel.reception.clear();
            break;
        }
        case '4': { // Editar Nacionalidade
            break;
        }
        case '5': { // Editar Primeiro Nome
            break;
        }
        case '6': { // Pesquisa de hóspedes
            menuSearchGuests(hotel);
            break;
        }
        case '7': { // Apresentação
            menuDisplayGuests(hotel);
            break;
        }
        case '0': { // Voltar
            break;
        }
        default:
            break;
    }
}

#endif //HOTELEDA_PRINTERS_H