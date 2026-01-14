#include <iostream>
using namespace std;

int main(){
    string str = "Hello World";

    str[0] = 'h';

    cout << str << endl;

    // size is 1 char longer because there is technicaly a "\0" at the end of the string in lower level code.
    cout << "the size of the string 'hello' is " << sizeof("hello") - 1 << " characters" << endl;
    
    
    // size of ints is measured in bytes

    int i = 5;

    cout << "The size of i is " << sizeof(i) << " bytes" << endl;


    //it is best practice to use getline(cin, var); so that no information is left in the buffer

    string input;

    cout << "input a string: ";
    getline(cin, input);
    cout << "your string was: "<< input << endl;




    return 0;
}