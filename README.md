# Doubly-Linked List (C++)

A simple implementation of a doubly linked list with iterator support.

## Files
- **IteratedList.cpp**: Implements list operations (add, remove, search, set).
- **ListIterator.cpp**: Implements iterator methods (traverse, jump forward).
- **ListIterator.h / IteratedList.h**: Header declarations.

## Features
- **Dynamic List**: Insert at beginning, end, or a specific position.
- **Iterator**: Traverse list and jump forward with error handling.
- **Custom Exception**: Uses `MyException` for invalid operations.
- **Memory Management**: Proper deletion of nodes.

## Compilation
```bash
g++ -std=c++11 -o iterated_list main.cpp IteratedList.cpp ListIterator.cpp
