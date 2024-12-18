#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

class Order {
public:
    string country;
    string itemType;
    string salesChannel;
    string orderDate;
    string orderID;
    string shipDate;

    // Constructor with this-> style
    Order(string country, string itemType, string salesChannel, 
          string orderDate, string orderID, string shipDate);

    // Default constructor
    Order();
};

#endif // ORDER_H
