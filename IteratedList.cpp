#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <stdexcept>
#include <iostream>

class MyException : public std::runtime_error {
public:
    MyException(const std::string& message) : std::runtime_error(message) {}
};

using namespace std;

IteratedList::IteratedList() : head(nullptr), tail(nullptr), listSize(0) {}

int IteratedList::size() const {
    return listSize;
}

bool IteratedList::isEmpty() const {
    return listSize == 0;
}

ListIterator IteratedList::first() const {
    ListIterator it(*this);
    it.first();
    return it;
}

TElem IteratedList::getElement(ListIterator pos) const {
    return pos.getCurrent();
}

TElem IteratedList::remove(ListIterator& pos) {
    if (!pos.valid())
        throw MyException("Invalid iterator position for removal");

    Node* current = pos.getCurrentNode();
    TElem removed = current->data;

    // Removing the only element in the list
    if (current == head && current == tail) {
        head = tail = nullptr;
    }
        // Removing the head node
    else if (current == head) {
        head = head->next;
        head->prev = nullptr;
    }
        // Removing the tail node
    else if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    }
        // Removing from the middle
    else {
        Node* previous_node = current->prev;
        Node* next_node = current->next;
        previous_node->next = next_node;
        next_node->prev = previous_node;
    }

    // Advance the iterator: point to the next node if it exists,
    // otherwise mark the iterator as invalid.
    Node* next_node = current->next;
    delete current;
    listSize--;
    if (next_node != nullptr)
        pos.current = next_node;
    else
        pos.current = nullptr;

    return removed;
}

ListIterator IteratedList::search(TElem e) const {
    ListIterator it(*this);
    it.first();
    while (it.valid()){
        if (it.getCurrent() == e)
            return it;
        it.next();
    }
    // Not found: return an invalid iterator
    it.current = nullptr;
    return it;
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw MyException("Invalid iterator position for setElement");
    TElem oldValue = pos.getCurrent();
    pos.getCurrentNode()->data = e;
    return oldValue;
}

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if (!pos.valid())
        throw MyException("Invalid position for addToPosition");

    Node* current = pos.getCurrentNode();
    Node* newNode = new Node(e);

    // Insert the new node after the current node
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    else {
        // If current was the tail, update tail pointer.
        tail = newNode;
    }
    current->next = newNode;
    listSize++;

    // Advance the iterator to point to the newly inserted node
    pos.next();
}

void IteratedList::addToEnd(TElem e) {
    Node* newNode = new Node(e);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

void IteratedList::addToBeginning(TElem e) {
    Node* newNode = new Node(e);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    listSize++;
}

IteratedList::~IteratedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
