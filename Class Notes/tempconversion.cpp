#include <iostream>
using namespace std;

int main(){
    //variable declarations
    float f;
    float c;

    //read f degrees
    cout << "Please input the degrees in Faranheight: ";
    cin >> f;

    //convert f to c

    c = 5.0/9.0 * (f-32.0);

    //print c

    cout << "The temperature in celcius is: " << c << endl;


    return 0;
}