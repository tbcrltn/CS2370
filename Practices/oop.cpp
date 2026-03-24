#include <string>
#include <iostream>
#include <vector>
using namespace std;


struct GPS{
    double x;
    double y;

    GPS(double x, double y) : x(x), y(y) {}
};

class Location{
    private:
        GPS gpslocation;
        string name;

    public:
        Location() : gpslocation(0,0), name("Unknown") {}
        Location(string n, GPS g) : gpslocation(g), name(n) {}
        

        void userSetLocation(){
            cout << "Enter new x coordinate -->";
            cin >> gpslocation.x;
            cout << "Enter new y coordinate -->";
            cin >> gpslocation.y;

        }

        void userSetName(){
            cout << "Enter new location name -->";
            cin >> name;
        }

        string getName(){
            return name;
        }

        GPS getlocation(){
            return gpslocation;
        }

        double getlocation(char type){
            switch (type){
                case 'x':
                    return gpslocation.x;
                case 'y':
                    return gpslocation.y;
                default:
                    return 0.00;
            }
        }
};


void PrintVectorLocation(vector<Location> x){
    for (int i = 0; i < x.size(); i++){
        cout << x.at(i).getName() << ": location at (x" << x.at(i).getlocation('x') << ", y" << x.at(i).getlocation('y') << ")\n";
    }
}




int main(){
    vector<Location> locations(5);

    locations.at(0) = Location("loc1", GPS(1.43, 2.54));
    locations.at(1) = Location("loc2", GPS(43.2, 21.42));

    locations.at(2) = Location("loc3", GPS(32.45, 23.44));
    locations.at(2).userSetName();
    locations.at(2).userSetLocation();


    PrintVectorLocation(locations);


    return 0;
}