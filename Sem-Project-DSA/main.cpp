#include "LinkedList.h"
#include "BinarySearchTree.h"
#include "Order.h"
#include "Implementation.cpp" // Includes all implementations
#include <limits> // Include this for numeric_limits
#include <iostream> // Standard input-output
#include <string> // For string manipulations

using namespace std;

int main() {
    string filename = "C:\\Users\\4g Traders\\Desktop\\LMS\\Sem-Project-DSA\\DataSet.csv";
    LinkedList ordersList;
    BinarySearchTree ordersTree;

    readCSV(filename, ordersList, ordersTree);

    while (true) {
        cout << "\n=== Order Management System ===" << endl;
        cout << "1. Display all orders" << endl;
        cout << "2. Filter orders by Country" << endl;
        cout << "3. Filter orders by Item Type" << endl;
        cout << "4. Search order by Order ID" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        cin.ignore(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                ordersList.displayOrders();
                break;
            case 2: {
                string country;
                cout << "Enter country: ";
                getline(cin, country);

                LinkedList filteredByCountry = ordersList.filterByCountry(country);
                filteredByCountry.displayOrders();
                break;
            }
            case 3: {
                string itemType;
                cout << "Enter Item Type: ";
                getline(cin, itemType);

                LinkedList filteredByItemType = ordersList.filterByItemType(itemType);
                filteredByItemType.displayOrders();
                break;
            }
            case 4: {
                string orderID;
                cout << "Enter Order ID: ";
                getline(cin, orderID);

                ordersTree.searchOrder(orderID);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
