#pragma once

#include <string>
#include <iostream>

using namespace std;

void printHeader(const char *title) {
	system("cls");
    cout << "---------------" << endl;
    cout << title << endl;
    cout << "---------------" << endl;
}

void printRooms(Hotel *hotel) {
	for (int i = 0; i < hotel->numRooms; i++) {
		Room *room = hotel->rooms[i];
		cout << "QUARTO " << room->number << " (CAPACIDADE " << room->capacity << "): ";
		for (GuestNode *node = listPeek(room->guestList); node != nullptr; node = node->next) {
			Guest *guest = node->guest;
			cout << guest->familyName << "(" << guest->duration << "|" << guest->reservationId << ") ";
		}
		cout << endl;
	}
}

void printReception(GuestList *guestList) {
    cout << "Recepcao:" << endl;

	for (GuestNode *node = listPeek(guestList); node != nullptr; node = node->next) {
		Guest *guest = node->guest;
		cout << guest->waitTime << " " << guest->familyName << "(" << guest->reservationId << ")" << endl;
	}
}

string &getInput(string &line, const char *message) {
    cout << message;
    cin >> line;
    return line;
}

void waitFor0() {
    cout << "(pressione 0 para voltar)" << endl;
    while (getch() != '0');
}

/* ========== MENUS ========== */

void menuMain(Hotel *hotel) {
    printHeader("Hotel EDA");
    printRooms(hotel);
    cout << "**************" << endl;

    printReception(hotel->reception);

    cout << "---------------------------" << endl;
    cout << "(o)pcoes (g)ravar (s)seguinte (q)uit" << endl;
}


void menuSearchGuests(Hotel *hotel) {
    printHeader("Hotel EDA - Opcoes - Pesquisa");

    cout << "1 - Hospedes de origem estrangeira" << endl;
    cout << "2 - Hospedes de origem portuguesa ou sul-africana" << endl;
    cout << "0 - Voltar" << endl;

	getch(); // catch extra char

	string line;
	char cmd = getch();
	printHeader("Hotel EDA - Opcoes - Pesquisa");
	switch (cmd) {
	case '1': { // Hóspedes de origem estrangeira
		string name = getInput(line, "Nome do hospede: ");
		searchForeignerGuests(hotel, name);
		waitFor0();
		break;
	}
	case '2': { // Hóspedes de origem portuguesa ou sul-africana
		string name = getInput(line, "Nome do hospede: ");
		searchPortugueseSAGuests(hotel, name);
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

void menuDisplayGuests(Hotel *hotel) {
    printHeader("Hotel EDA - Opcoes - Apresentacao");

    cout << "1 - Hospedes de origem estrangeira" << endl;
    cout << "2 - Hospedes de origem portuguesa ou sul-africana" << endl;
    cout << "0 - Voltar" << endl;

	getch(); // catch extra char

    string line;
    char cmd = getch();
    printHeader("Hotel EDA - Opcoes - Apresentacao");
    switch (cmd) {
        case '1': { // Hóspedes de origem estrangeira
			displayForeignerGuests(hotel);
            waitFor0();
            break;
        }
        case '2': { // Hóspedes de origem portuguesa ou sul-africana
			displayPortugueseSAGuests(hotel);
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

void menuOptions(Hotel *hotel) {
    printHeader("Hotel EDA - Opcoes");

    cout << "1 - Limpar Quarto" << endl;
    cout << "2 - Alterar duracao de reserva" << endl;
    cout << "3 - Limpar Recepcao" << endl;
    cout << "4 - Editar Nacionalidade" << endl;
    cout << "5 - Editar Primeiro Nome" << endl;
    cout << "6 - Pesquisa de hospedes" << endl;
    cout << "7 - Apresentacao" << endl;
    cout << "0 - Voltar" << endl;

	getch(); // catch extra char

    string line;
    char cmd = getch();
    switch (cmd) {
        case '1': { // Limpar Quarto
            int roomNumber = stoi(getInput(line, "Num do quarto a limpar: "));

			clearHotelRoom(hotel, roomNumber);
            break;
        }
        case '2': { // Alterar duração de reserva
            int reservationId = stoi(getInput(line, "ID de reserva a alterar: "));
            int numDays = stoi(getInput(line, "Num de dias: "));

			changeReservation(hotel, reservationId, numDays);
            break;
        }
        case '3': { // Limpar Recepção
			clearReception(hotel);
            break;
        }
        case '4': { // Editar Nacionalidade
			string guestFamily = getInput(line, "Nome de familia do hospede: ");

			for (GuestNode *node = hotel->reception->head; node != nullptr; node = node->next) {
				Guest *guest = node->guest;
				if (guest->familyName == guestFamily) {
					string newNat = getInput(line, "Nova nacionalidade: ");
					guest->nationality = newNat;
					return;
				}
			}

			for (int i = 0; i < hotel->numRooms; i++) {
				Room *room = hotel->rooms[i];
				for (GuestNode *node = room->guestList->head; node != nullptr; node = node->next) {
					Guest *guest = node->guest;
					if (guest->familyName == guestFamily) {
						string newNat = getInput(line, "Nova nacionalidade: ");
						guest->nationality = newNat;
						return;
					}
				}
			}

			cout << "Hospede nao encontrado..." << endl;
			waitFor0();
            break;
        }
        case '5': { // Editar Primeiro Nome
			string guestFamily = getInput(line, "Nome de familia do hospede: ");

			for (GuestNode *node = hotel->reception->head; node != nullptr; node = node->next) {
				Guest *guest = node->guest;
				if (guest->familyName == guestFamily) {
					string newName = getInput(line, "Novo nome: ");
					guest->name = newName;
					return;
				}
			}

			for (int i = 0; i < hotel->numRooms; i++) {
				Room *room = hotel->rooms[i];
				for (GuestNode *node = room->guestList->head; node != nullptr; node = node->next) {
					Guest *guest = node->guest;
					if (guest->familyName == guestFamily) {
						string newName = getInput(line, "Novo nome: ");
						guest->name = newName;
						return;
					}
				}
			}

			cout << "Hospede nao encontrado..." << endl;
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
