/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA5
 * List.cpp
 * List ADT implementation
***/

// 50 out of 53 points on List Tests

#include "List.h"
#include <stdexcept>
#include <iostream>
#include <string>

// Node constructor
List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

// Class Constructors & Destructors ----------------------------------------

List::List() : pos_cursor(0), num_elements(0) {
    frontDummy = new Node(0);  // dummy node at front
    backDummy = new Node(0);   // dummy node at back
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

List::List(const List& L) : List() {
    Node* temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        insertAfter(temp->data);
        moveNext();
        temp = temp->next;
    }
    pos_cursor = L.pos_cursor;
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (num_elements == 0) throw std::length_error("List: front(): empty List");
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (num_elements == 0) throw std::length_error("List: back(): empty List");
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (afterCursor == backDummy) throw std::range_error("List: peekNext(): at end of List");
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (beforeCursor == frontDummy) throw std::range_error("List: peekPrev(): at start of List");
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

void List::clear() {
    moveFront();
    while (num_elements > 0) eraseAfter();
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext() {
    if (afterCursor == backDummy) throw std::range_error("List: moveNext(): at end of List");
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (beforeCursor == frontDummy) throw std::range_error("List: movePrev(): at start of List");
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (afterCursor == backDummy) throw std::range_error("List: setAfter(): at end of List");
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (beforeCursor == frontDummy) throw std::range_error("List: setBefore(): at start of List");
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (afterCursor == backDummy) throw std::range_error("List: eraseAfter(): at end of List");
    Node* temp = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (beforeCursor == frontDummy) throw std::range_error("List: eraseBefore(): at start of List");
    Node* temp = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    delete temp;
    num_elements--;
    pos_cursor--;
}

// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x) {
    while (afterCursor != backDummy) {
        if (moveNext() == x) return pos_cursor;
    }
    return -1;
}

int List::findPrev(ListElement x) {
    while (beforeCursor != frontDummy) {
        if (movePrev() == x) return pos_cursor;
    }
    return -1;
}

void List::cleanup() {
    Node* curr = frontDummy->next;
    while (curr != backDummy) {
        Node* checker = curr->next;
        while (checker != backDummy) {
            if (checker->data == curr->data) {
                Node* temp = checker;
                checker->prev->next = checker->next;
                checker->next->prev = checker->prev;
                if (checker == afterCursor) afterCursor = checker->next;
                delete temp;
                num_elements--;
            }
            checker = checker->next;
        }
        curr = curr->next;
    }
}

List List::concat(const List& L) const {
    List newList;
    Node* temp = frontDummy->next;
    while (temp != backDummy) {
        newList.insertBefore(temp->data);
        temp = temp->next;
    }
    temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        newList.insertBefore(temp->data);
        temp = temp->next;
    }
    newList.moveFront();
    return newList;
}

std::string List::to_string() const {
    Node* N = frontDummy->next;
    std::string s = "(";
    while (N != backDummy) {
        s += std::to_string(N->data);
        if (N->next != backDummy) s += ", ";
        N = N->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const {
    if (num_elements != R.num_elements) return false;
    Node* N = frontDummy->next;
    Node* M = R.frontDummy->next;
    while (N != backDummy) {
        if (N->data != M->data) return false;
        N = N->next;
        M = M->next;
    }
    return true;
}

// Overridden Operators -----------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}

