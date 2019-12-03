#ifndef HOTELEDA_GUESTLIST_H
#define HOTELEDA_GUESTLIST_H

#include "src/Guest.h"

struct node {
    Guest *guest;
    node *next;
};

/*
 * Linked List used for Hotel Guests
 * implemented as FIFO (First-in, First-out)
 */
class GuestList {
public:
    node *head, *tail;

    GuestList();

    virtual ~GuestList();

    node *createNode(Guest *guest);

    bool is_empty();

    void push(Guest *guest); // add node to tail (end)

    void pop(); // remove node from head (start)

    Guest *peek(); // get node from start, without removing it
};


#endif //HOTELEDA_GUESTLIST_H
