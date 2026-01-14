#include <iostream>
using namespace std;


// functions can be declared before the main function in order to move the bulk of the function to a different part of the code.
// if they are not declared, they must be before the main function.
int ComputeSquare(int num);


int main(){
    int numsquared;
    numsquared = ComputeSquare(7);

    cout << "7 squared is " << numsquared << endl;

    //if then while and for statements
    int grade;

    cout << "Enter the student grade(1-4): ";
    cin >> grade;

    //note: if only one instruction is below the if or elif statements, the curly braces are optional.

    if (grade == 4) {
        cout << "Excellent!" << endl;
    } else if (grade == 3) {
        cout << "Good1" << endl;
    } else if (grade == 2) {
        cout << "Poor" << endl;
    } else {
        cout << "Bad" << endl;
    }

    char loop;

    cout << "Loop?(y/n): ";
    cin >> loop;

    while (loop == 'y'){
        cout << "Loop?(y/n): ";
        cin >> loop;
    }
    
    cout << "Okay Bye!" << endl;



    int num;

    cout << "Type a number 1-5: " << endl;
    cin >> num;


    //break statements are needed in switch blocks so that the rest of the cases dont run and there is one output.

    switch (num){
        case 1:
            cout << 1 << endl; 
            break;
        case 2:
            cout << 2 << endl;
            break;
        case 3:
            cout << 3 << endl;
            break;
        case 4:
            cout << 4 << endl;
            break;
        case 5: 
            cout << 5 << endl;
            break;
        default:
            cout << "End" << endl;
    }
    





    return 0;
}

int ComputeSquare(int num){
    int square = num * num;

    return square;

}