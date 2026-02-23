#include <iostream>
using namespace std;


void print_vars(int a, int b){

    cout << "a: " << a << "   b: " << b << endl;
}

//use pointers when making functions to update local variables

void swap_vars(int& a, int& b){
    int swap = a;
    a = b;
    b = swap;

    
}

int main(){
    
    int a = 6;
    int b = 9;

    print_vars(a, b);
    swap_vars(a, b);
    print_vars(a, b);



    return 0;
}