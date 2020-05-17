#include "Sokoban.h"
#include <iostream>
using namespace std;

int main(){
    Sokoban a;
    char b;
    a.showPresent();
    for(;;){
        for(;;){
            cin>>b;
            if(b=='w'||b=='W'||b=='a'||b=='A'
                    ||b=='s'||b=='S'||b=='d'||b=='D')
                break;
            else
                cout<<"Wrong entering!\n";
        }
        a.setFuture(b);
        if(a.isLegal()){
            a.setPresent();
        }
        else a.resetFuture();
        a.showPresent();
        if(a.isPass()) break;
    }
    return 0;
}
