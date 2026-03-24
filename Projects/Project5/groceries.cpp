#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "split.h"

using namespace std;


struct Customer {
    int id;
    string name;
    string street;
    string city;
    string state;
    string zip;
    string phone;
    string email;
};

struct Item {
    int id;
    string description;
    double price;
};


vector<Customer> customers;
vector<Item> items;


void read_customers(const string& filename);
void read_items(const string& filename);
void one_customer_order();


void read_customers(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        auto fields = split(line, ',');

        Customer c;
        c.id = stoi(fields[0]);
        c.name = fields[1];
        c.street = fields[2];
        c.city = fields[3];
        c.state = fields[4];
        c.zip = fields[5];
        c.phone = fields[6];
        c.email = fields[7];

        customers.push_back(c);
    }
}


void read_items(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        auto fields = split(line, ',');

        Item i;
        i.id = stoi(fields[0]);
        i.description = fields[1];
        i.price = stod(fields[2]);

        items.push_back(i);
    }
}


void one_customer_order() {
    cout << "Number of customers: " << customers.size() << endl;
    cout << "Number of items: " << items.size() << endl;

    int customer_id;
    cout << "Enter customer ID: ";
    cin >> customer_id;


    Customer* selected_customer = nullptr;
    for (auto& c : customers) {
        if (c.id == customer_id) {
            selected_customer = &c;
            break;
        }
    }

    if (selected_customer == nullptr) {
        cout << "Customer not found. Exiting program." << endl;
        return;
    }

    cout << "Customer found: " << selected_customer->name << endl;

    int item_id;
    int total_items = 0;
    double total_cost = 0.0;

    while (true) {
        cout << "Enter item ID (0 to finish): ";
        cin >> item_id;

        if (item_id == 0) break;

        bool found = false;

        for (const auto& item : items) {
            if (item.id == item_id) {
                cout << "Item: " << item.description
                     << " | Price: $" << fixed << setprecision(2) << item.price << endl;

                total_items++;
                total_cost += item.price;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Item not found. Try again." << endl;
        }
    }

    cout << "\nOrder Summary:" << endl;
    cout << "Total items purchased: " << total_items << endl;
    cout << "Total cost: $" << fixed << setprecision(2) << total_cost << endl;
}


int main() {
    read_customers("customers.txt");
    read_items("items.txt");
    one_customer_order();
}