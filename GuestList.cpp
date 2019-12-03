#include "GuestList.h"

GuestList::GuestList() {
    head = nullptr;
    tail = nullptr;
}

GuestList::~GuestList() {
    while (head != nullptr) {
        this->pop();
    }
}

node *GuestList::createNode(Guest *guest) {
    auto *new_node = new node;
    new_node->guest = guest;
    new_node->next = nullptr;
    return new_node;
}

bool GuestList::is_empty() {
    return head == nullptr;
}

void GuestList::push(Guest *guest) {
    auto node = createNode(guest);

    if (this->is_empty()) {
        head = (tail = node);
    } else {
        tail->next = node;  // add *node* element to old tail's next
        tail = node;        // make *node* new tail
    }
}

void GuestList::pop() {
    auto node = head;
    head = head->next;
    delete node;
}

Guest *GuestList::peek() {
    return head->guest;
}
