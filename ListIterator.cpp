#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <stdexcept>

class MyException : public std::runtime_error {
public:
    MyException(const std::string& message) : std::runtime_error(message) {}
};

ListIterator::ListIterator(const IteratedList& list) : list(list), current(list.head){}

void ListIterator::first() {
	current=list.head;
}

void ListIterator::next() {
    current=current->next;
}

bool ListIterator::valid() const {
    return current != nullptr;
}

TElem ListIterator::getCurrent() const {
    if(current== nullptr){
        throw MyException("Current is invalid");
    }
    else
        return current->data;
}
IteratedList::Node* ListIterator::getCurrentNode() const {
    return current; // Return the pointer to the current node
}

void ListIterator::jumpForward(int k) {
    if (k < 0)
        throw MyException("Invalid jump: negative steps not allowed.");

    for (int i = 0; i < k; i++) {
        if (!valid())
            throw MyException("Cannot jump forward: iterator reached the end of the list.");
        next(); // move to the next node
    }
}






