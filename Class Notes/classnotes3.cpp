#include <iostream>
#include <cctype> //character type -> designed for manipulating char types
using namespace std;


int main(){
    int i = 0;
    string y;

    //using while loops demo

    while(i < 5){
        cout << i << endl;
        i++;
    }

    cout << "done with int demo" << endl;

    while (y != "q"){
        cout << "Enter anything, q to quit --> ";
        getline(cin, y);
    }


    // using do .. while statements
    // these statements are just while loops but ordered differently with the condition at the end and the code in the block at the beginning.
    cout << endl << endl;

    i = 0;

    do{
        cout << i << endl;
        i++;
    } while (i < 5);

    cout << "finished do .. while demo" << endl;



    // using for loops demo
    // syntax: (variable declaration; condition; counter;)
    // break; statements can be used in for loops as well
    for (int x = 0; x < 5; x++){
        cout << x << endl;
    }

    cout << "completed for loop demo" << endl;


    // when using increment operators these rules apply:
    // a = ++b;  a = b is true
    // a = b++;  a + 1 = b is true

    int a;
    int b = 9;

    a = ++b;
    
    cout << "a, b = " << a << ", " << b << endl;
    cout << endl << endl;

    //upper and lower functions for strings
    //libraries are needed
    //you can use isupper() islower() toupper() tolower()

    string s = "HELLO";

    for (int i = 0; i < s.size(); i++){
        s[i] = tolower(s[i]);
    }

    cout << s << endl;

    string g = "HeLlO";
    int counter = 0;

    for (int i = 0; i < g.size(); i++){
        if (isupper(g[i])){
            counter++;
        }
    }
    
    cout << "there are " << counter << " uppercase letters in g." << endl;

    return 0;
}