#include <iostream>
#include <bitset>
using namespace std;


enum suit {
    CLUBS = 10,
    DIAMONDS = 20,
    HEARTS = 30,
    SPADES = 40
};

enum level {
    LOW = 20,
    MEDIUM = 40,
    HIGH = 60
};

int main(){
    enum suit s2 = DIAMONDS;
    enum level l1 = LOW;

    if (s2 == l1){
        cout << "true" << endl;
    }else{
        cout << "false" << endl;
    }

    




    return 0;
}