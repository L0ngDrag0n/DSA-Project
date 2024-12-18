#include "Order.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ================= Order Class Implementation =================
Order::Order(string country, string itemType, string salesChannel, 
             string orderDate, string orderID, string shipDate) {
    this->country = country;
    this->itemType = itemType;
    this->salesChannel = salesChannel;
    this->orderDate = orderDate;
    this->orderID = orderID;
    this->shipDate = shipDate;
}

Order::Order() {
    this->country = "";
    this->itemType = "";
    this->salesChannel = "";
    this->orderDate = "";
    this->orderID = "";
    this->shipDate = "";
}

// ================= LinkedList Class Implementation =================
LinkedList::Node::Node(const Order& order) : data(order), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkedList::addOrder(const Order& order) {
    Node* newNode = new Node(order);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::displayOrders() const {
    if (!head) {
        cout << "No orders found." << endl;
        return;
    }

    Node* temp = head;
    cout << "Country\t\tItem Type\tSales Channel\tOrder Date\tOrder ID\tShip Date" << endl;
    while (temp) {
        cout << temp->data.country << "\t" << temp->data.itemType << "\t"
             << temp->data.salesChannel << "\t" << temp->data.orderDate << "\t"
             << temp->data.orderID << "\t" << temp->data.shipDate << endl;
        temp = temp->next;
    }
}

LinkedList LinkedList::filterByCountry(const string& country) const {
    LinkedList filteredList;
    Node* temp = head;
    while (temp) {
        if (temp->data.country == country) {
            filteredList.addOrder(temp->data);
        }
        temp = temp->next;
    }
    return filteredList;
}

LinkedList LinkedList::filterByItemType(const string& itemType) const {
    LinkedList filteredList;
    Node* temp = head;
    while (temp) {
        if (temp->data.itemType == itemType) {
            filteredList.addOrder(temp->data);
        }
        temp = temp->next;
    }
    return filteredList;
}

// ================= BinarySearchTree Class Implementation =================
BinarySearchTree::TreeNode::TreeNode(const Order& order) : data(order), left(nullptr), right(nullptr) {}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

BinarySearchTree::TreeNode* BinarySearchTree::insert(TreeNode* node, const Order& order) {
    if (!node) {
        return new TreeNode(order);
    }

    if (order.orderID < node->data.orderID) {
        node->left = insert(node->left, order);
    } else if (order.orderID > node->data.orderID) {
        node->right = insert(node->right, order);
    }

    return node;
}

void BinarySearchTree::insertOrder(const Order& order) {
    root = insert(root, order);
}

BinarySearchTree::TreeNode* BinarySearchTree::search(TreeNode* node, const string& orderID) const {
    if (!node || node->data.orderID == orderID) {
        return node;
    }

    if (orderID < node->data.orderID) {
        return search(node->left, orderID);
    } else {
        return search(node->right, orderID);
    }
}

void BinarySearchTree::searchOrder(const string& orderID) const {
    TreeNode* result = search(root, orderID);
    if (result) {
        cout << "Order found: " << endl;
        cout << "Country: " << result->data.country << ", Item Type: " << result->data.itemType
             << ", Sales Channel: " << result->data.salesChannel
             << ", Order Date: " << result->data.orderDate
             << ", Order ID: " << result->data.orderID
             << ", Ship Date: " << result->data.shipDate << endl;
    } else {
        cout << "Order with ID " << orderID << " not found." << endl;
    }
}

// ================= readCSV Function Implementation =================
void readCSV(const string& filename, LinkedList& list, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string country, itemType, salesChannel, orderDate, orderID, shipDate;

        getline(ss, country, ',');
        getline(ss, itemType, ',');
        getline(ss, salesChannel, ',');
        getline(ss, orderDate, ',');
        getline(ss, orderID, ',');
        getline(ss, shipDate, ',');

        Order order(country, itemType, salesChannel, orderDate, orderID, shipDate);
        list.addOrder(order);
        bst.insertOrder(order);
    }

    file.close();
}
