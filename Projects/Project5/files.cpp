#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "split.h"

using namespace std;

// ===================== SAFE CHECK =====================
bool is_number(const string &s) {
    if (s.empty()) return false;
    char *end;
    strtod(s.c_str(), &end);
    return *end == '\0';
}

// ===================== STRUCTS =====================
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

struct LineItem {
    int item_id;
    int quantity;
};

// ===================== PAYMENT SYSTEM =====================
struct Payment {
    double amount = 0;
    virtual string print() = 0;
    virtual ~Payment() {}
};

struct Credit : Payment {
    string card, exp;

    string print() override {
        return "Credit Card: " + card + " Exp: " + exp +
               " Amount: $" + to_string(amount);
    }
};

struct PayPal : Payment {
    string id;

    string print() override {
        return "PayPal ID: " + id +
               " Amount: $" + to_string(amount);
    }
};

struct Wire : Payment {
    string bank, account;

    string print() override {
        return "Wire Bank: " + bank + " Account: " + account +
               " Amount: $" + to_string(amount);
    }
};

// ===================== ORDER =====================
struct Order {
    int customer_id;
    int order_num;
    string date;

    vector<LineItem> items;
    Payment* payment = nullptr;

    string print() {
        string out;

        out += "Order #" + to_string(order_num) + "\n";
        out += "Customer: " + to_string(customer_id) + "\n";
        out += "Date: " + date + "\n";

        for (auto &i : items) {
            out += "Item " + to_string(i.item_id) +
                   " Qty " + to_string(i.quantity) + "\n";
        }

        if (payment)
            out += payment->print() + "\n";
        else
            out += "INVALID PAYMENT\n";

        return out;
    }
};

// ===================== GLOBALS =====================
vector<Customer> customers;
vector<Item> items;
vector<Order> orders;



// ===================== READ CUSTOMERS =====================
void read_customers(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        auto f = split(line, ',');
        if (f.size() < 8) continue;
        if (!is_number(f[0])) continue;

        Customer c;
        c.id = stoi(f[0]);
        c.name = f[1];
        c.street = f[2];
        c.city = f[3];
        c.state = f[4];
        c.zip = f[5];
        c.phone = f[6];
        c.email = f[7];

        customers.push_back(c);
    }
}

// ===================== READ ITEMS =====================
void read_items(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        auto f = split(line, ',');
        if (f.size() < 3) continue;

        if (!is_number(f[0]) || !is_number(f[2])) continue;

        Item i;
        i.id = stoi(f[0]);
        i.description = f[1];
        i.price = stod(f[2]);

        items.push_back(i);
    }
}

// ===================== READ ORDERS (PART 2) =====================
void read_orders(const string& filename) {
    ifstream file(filename);
    string line;

    while (true) {

        // -------- ORDER LINE --------
        if (!getline(file, line)) break;
        if (line.empty()) continue;

        auto f = split(line, ',');
        if (f.size() < 3) continue;
        if (!is_number(f[0]) || !is_number(f[1])) continue;

        Order o;
        o.customer_id = stoi(f[0]);
        o.order_num = stoi(f[1]);
        o.date = f[2];

        for (int i = 3; i < f.size(); i++) {
            auto p = split(f[i], '-');
            if (p.size() < 2) continue;
            if (!is_number(p[0]) || !is_number(p[1])) continue;

            LineItem li;
            li.item_id = stoi(p[0]);
            li.quantity = stoi(p[1]);
            o.items.push_back(li);
        }

        // -------- PAYMENT LINE --------
        if (!getline(file, line)) break;

        auto p = split(line, ',');

        Payment* pay = nullptr;

        if (p.size() >= 2 && is_number(p[0])) {

            int type = stoi(p[0]);

            if (type == 1 && p.size() >= 3) {
                Credit* c = new Credit();
                c->card = p[1];
                c->exp = p[2];
                pay = c;
            }
            else if (type == 2) {
                PayPal* pp = new PayPal();
                pp->id = p[1];
                pay = pp;
            }
            else if (type == 3 && p.size() >= 3) {
                Wire* w = new Wire();
                w->bank = p[1];
                w->account = p[2];
                pay = w;
            }
        }

        o.payment = pay;

        // -------- TOTAL --------
        double total = 0;

        for (auto &li : o.items) {
            for (auto &it : items) {
                if (it.id == li.item_id) {
                    total += it.price * li.quantity;
                    break;
                }
            }
        }

        if (o.payment)
            o.payment->amount = total;

        orders.push_back(o);
    }
}

// ===================== MAIN =====================
int main() {
    read_customers("customers.txt");
    read_items("items.txt");
    read_orders("orders.txt");

    for (auto &o : orders) {
        cout << o.print() << "\n";
    }

    return 0;
}