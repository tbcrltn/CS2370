#include <iostream>
using namespace std;

int main(){
    // using arrays
    //syntax datatype array[number of elements] = {data}
    //including the data is optional but you must include the number of elements when declaring the variable.

    int a[3] = {1, 2, 3};
    // putting the 0 here initializes all of the elements to 0 otherwise it will feed garbage data
    // this is best practice
    int b[10] = {0};

    b[0] = 100;
    b[5] = 200;

    const int lenb = sizeof(b) / sizeof(b[0]);

    for (int i = 0; i < lenb; i++){
        cout << b[i] << endl;
    }

    //another way for accessing data in an array
    //same as for item in b 
    //better practice for accessing all data at once.
    //item variable is not the index like in python, it represents the actually item being stored in the array

    for (int item : b){
        cout << item << endl;
    }

    cout << endl << endl;

    //adding 1 to each element
    //to make changes to the array via the item variable the & sign must be included in the for statement otherwise the array wont be changed, only the number being printed.

    for (int & item : a){
        item ++;
        cout << item << endl;
    }

    for (int item : a){
        cout << item << endl;
    }

    //character arrays:

    char char_array[3] = {'U', 'V', 'U'};



    return 0;
}