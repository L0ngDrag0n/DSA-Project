#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Order.h"
using namespace std;

class LinkedList {
private:
    class Node {
    public:
        Order data;
        Node* next;

        Node(const Order& order);
    };

    Node* head;

public:
    LinkedList();
    ~LinkedList();
    void addOrder(const Order& order);
    void displayOrders() const;
    LinkedList filterByCountry(const string& country) const;
    LinkedList filterByItemType(const string& itemType) const;
};

#endif // LINKEDLIST_H
