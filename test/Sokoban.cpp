#include "Sokoban.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

Sokoban::Sokoban(){
    //set present through origin
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            present[i][j]=origin[i][j];
            future[i][j]=origin[i][j];
        }
    }
}
void Sokoban::setPresent(){
    //set present through future
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            present[i][j]=future[i][j];
        }
    }
}
void Sokoban::setFuture(char direction){
    int x,y;
    //find 'C' position
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==1||present[i][j]==6){
                x=i;
                y=j;
            }
        }
    }
    if(direction=='w'||direction=='W'){
        future[x][y]-=1;
        future[x-1][y]+=1;
        if(present[x-1][y]==7||present[x-1][y]==12){
            future[x-1][y]-=7;
            future[x-2][y]+=7;
        }
    }
    else if(direction=='a'||direction=='A'){
        future[x][y]-=1;
        future[x][y-1]+=1;
        if(present[x][y-1]==7||present[x][y-1]==12){
            future[x][y-1]-=7;
            future[x][y-2]+=7;
        }
    }
    else if(direction=='s'||direction=='S'){
        future[x][y]-=1;
        future[x+1][y]+=1;
        if(present[x+1][y]==7||present[x+1][y]==12){
            future[x+1][y]-=7;
            future[x+2][y]+=7;
        }
    }
    else if(direction=='d'||direction=='D'){
        future[x][y]-=1;
        future[x][y+1]+=1;
        if(present[x][y+1]==7||present[x][y+1]==12){
            future[x][y+1]-=7;
            future[x][y+2]+=7;
        }
    }
}
void Sokoban::resetFuture(){
    //set future through present
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            future[i][j]=present[i][j];
        }
    }
}
void Sokoban::showPresent(){
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            switch(present[i][j]){
                case -1: case 0:
                    cout<<setw(4)<<" ";
                    break;
                case 1:
                    cout<<setw(4)<<"C";
                    break;
                case 3:
                    cout<<setw(4)<<"X";
                    break;
                case 5:
                    cout<<setw(4)<<"O";
                    break;
                case 7:
                    cout<<setw(4)<<"B";
                    break;
                case 8:
                    cout<<setw(4)<<"C/B";
                    break;
                case 4:
                    cout<<setw(4)<<"C/X";
                    break;
                case 6:
                    cout<<setw(4)<<"C/O";
                    break;
                case 14:
                    cout<<setw(4)<<"B/B";
                    break;
                case 10:
                    cout<<setw(4)<<"B/X";
                    break;
                case 12:
                    cout<<setw(4)<<"B/O";
                    break;
                default:
                    cout<<"XXXX";
                    exit(1);
            }
        }
        cout<<endl;
    }
}
bool Sokoban::isLegal(){
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(future[i][j]==4||future[i][j]==10||
                    future[i][j]==14)
                return false;
        }
    }
    return true;
}
bool Sokoban::isPass(){
    int count=0;
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==12)
                count++;
        }
    }
    if(count==4){
        cout<<"Congratulations!!\n";
        return true;    
    }
    return false;
}

