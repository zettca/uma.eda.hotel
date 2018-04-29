#ifndef HOTELEDA_PRINTERS_H
#define HOTELEDA_PRINTERS_H

#include <string>
#include <iostream>

using namespace std;

void printSpace() {
    for (int i = 0; i < 20; ++i) {
        cout << endl;
    }
}

void printHeader(const char *title) {
    printSpace();
    cout << "---------------" << endl;
    cout << "Hotel EDA" << title << endl;
    cout << "---------------" << endl;
}

void printRooms(vector<Room> &rooms) {
    for (auto room : rooms) {
        cout << "QUARTO " << room.number << "(CAPACIDADE " << room.capacity << "):" << endl;
        cout << "*to-do*" << endl;
        cout << "." << endl;
    }
}

void printReception(Reception &reception) {
    cout << "**************" << endl;
    cout << "Recepção:" << endl;

    for (auto guest : reception.waitingGuests) {
        cout << guest.familyName << "(" << guest.reservationId << ")" << endl;

    }

}

/* ========== MENUS ========== */

void menuMain(Hotel &hotel) {
    printHeader("");

    printRooms(hotel.rooms);
    printReception(hotel.reception);

    cout << "---------------------------" << endl;
    cout << "(o)pções (g)ravar (s)seguinte" << endl;
}

void menuOptions() {
    printHeader(" - opções");

    cout << "1 - Limpar Quarto" << endl;
    cout << "2 - Alterar duração de reserva" << endl;
    cout << "3 - Limpar Recepção" << endl;
    cout << "4 - Editar Nacionalidade" << endl;
    cout << "5 - Editar Primeiro Nome" << endl;
    cout << "6 - Pesquisa de hóspedes" << endl;
    cout << "7 - Apresentação" << endl;
    cout << "0 - Voltar" << endl;
}

void menuSearch() {
    printHeader(" - opções - Pesquisa");

    cout << "1 - Hóspedes de origem estrangeira" << endl;
    cout << "2 - Hóspedes de origem portuguesa ou sul-africana" << endl;
    cout << "0 - Voltar" << endl;

}

#endif //HOTELEDA_PRINTERS_H