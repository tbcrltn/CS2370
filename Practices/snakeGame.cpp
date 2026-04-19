#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;
bool game_over;
const int width = 24;
const int height = 24;
int x, y, fruitx, fruity, score;
vector<vector<int>> segments = {{width/2,height/2}};

enum eDirection{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirection dir;

void setup(){    
    srand(time(NULL));
    game_over = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitx = rand() % (width-2);
    fruity = rand() % (height-2);
    score = 0;
}
void draw(){
    system("cls");
    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << endl;


    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            bool segment_added = false;
            for(int k = 0; k < segments.size(); k++){
                vector<int> segment = segments.at(k);
                if (segment.at(0) == j && segment.at(1) == i){
                    cout << "#";
                    segment_added = true;
                }
            }
            if (!segment_added){
                if (j == 0 || j == width - 1 || (j == x && i == y)){
                    cout << "#";
                }else if (j == fruitx &&i == fruity){
                    cout << "@";
                }else{
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << endl;

}
void input(){
    if (_kbhit()){
        int key = _getch();
        switch (key){
            case 72: dir = UP; break;
            case 80: dir = DOWN; break;
            case 75: dir = LEFT; break;
            case 77: dir = RIGHT; break;
        }

    }
}

void add_segment(){
    vector<int> new_segment = {x,y};
    segments.push_back(new_segment);
}

void update_tail(){
    segments.erase(segments.begin());
    add_segment();
}
void logic(){
    if (dir == UP) y--;
    else if (dir == DOWN) y++;
    else if (dir == RIGHT) x++;
    else if (dir == LEFT) x--;

    if (fruitx == x && fruity == y){
        add_segment();
    }
    update_tail();

}

int main(){
    setup();
    while (!game_over){
        draw();
        input();
        logic();
        Sleep(60);
    }

    return 0;
}