#include "player.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <QDebug>
using namespace std;

player::player(){
    //set present through stage_1, unstarted
    state=0;
    stage=1;
    eat=false;
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            present[i][j]=stage_1[i][j];
            future[i][j]=stage_1[i][j];
        }
    }
}
void player::setPresent(){
    //set present through future
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            present[i][j]=future[i][j];
        }
    }
}
//need to be brake into 4 cases to trigger w,a,s,d
void player::setFuture_w(){
    int x=0, y=0;
    //find 'C' position
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==1||present[i][j]==6){
                x=i;
                y=j;
            }
        }
    }
    future[x][y]-=1;
    future[x-1][y]+=1;
    //if the next is box
    if(present[x-1][y]==7||present[x-1][y]==12){
        future[x-1][y]-=7;
        future[x-2][y]+=7;
    }
    //if the next is fruit
    else if (present[x-1][y]==9) {
        eat=true;
        future[x-1][y]-=9;
        distroyTarget();
    }
}
void player::setFuture_a(){
    int x=0, y=0;      
    //find 'C' position
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==1||present[i][j]==6){
                x=i;
                y=j;
            }
        }
    }
    future[x][y]-=1;
    future[x][y-1]+=1;
    if(present[x][y-1]==7||present[x][y-1]==12){
        future[x][y-1]-=7;
        future[x][y-2]+=7;
    }
    //if the next is fruit
    else if (present[x][y-1]==9) {
        eat=true;
        future[x][y-1]-=9;
        distroyTarget();
    }
}
void player::setFuture_s(){
    int x=0, y=0;
    //find 'C' position
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==1||present[i][j]==6){
                x=i;
                y=j;
            }
        }
    }
    future[x][y]-=1;
    future[x+1][y]+=1;
    if(present[x+1][y]==7||present[x+1][y]==12){
        future[x+1][y]-=7;
        future[x+2][y]+=7;
    }
    //if the next is fruit
    else if (present[x+1][y]==9) {
        eat=true;
        future[x+1][y]-=9;
        distroyTarget();
    }
}
void player::setFuture_d(){
    int x=0, y=0;
    //find 'C' position
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==1||present[i][j]==6){
                x=i;
                y=j;
            }
        }
    }
    future[x][y]-=1;
    future[x][y+1]+=1;
    if(present[x][y+1]==7||present[x][y+1]==12){
        future[x][y+1]-=7;
        future[x][y+2]+=7;
    }
    //if the next is fruit
    else if (present[x][y+1]==9) {
        eat=true;
        future[x][y+1]-=9;
        distroyTarget();
    }
}
void player::resetFuture(){
    //set future through present
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            future[i][j]=present[i][j];
        }
    }
}
bool player::isLegal(){
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(future[i][j]==4||future[i][j]==10||
                    future[i][j]==14||future[i][j]==19||
                    future[i][j]==16)
                return false;
        }
    }
    return true;
}
bool player::isPass(){
    int count=0;
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(present[i][j]==12)
                count++;
        }
    }
    if(stage==1&&count==4){
        return true;
    }
    else if(stage==2&&count==9){
        return true;
    }
    else if (eat==true&&stage==2&&count==8) {
        return true;
    }
    else
        return false;
}
int player::getPresentContent(int x, int y){
    return present[x][y];
}
int player::getFutureContent(int x, int y){
    return future[x][y];
}
void player::setState(bool IsGameStart){
    state=IsGameStart;
}
bool player::getState(){
    return state;
}
void player::setStage(int GameStage){
    stage=GameStage;
    eat=false;
    //set present through stage_1, stage_2
    if(stage==1){
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                present[i][j]=stage_1[i][j];
                future[i][j]=stage_1[i][j];
            }
        }
    }
    else if(stage==2){
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                present[i][j]=stage_2[i][j];
                future[i][j]=stage_2[i][j];
            }
        }
    }
}
int player::getStage(){
    return stage;
}
//about fruit
void player::setEat(bool IsFruitEaten){
    eat=IsFruitEaten;
}
bool player::getEat(){
    return eat;
}
void player::distroyTarget(){
    int count=0;            //count how many boxes on the position
    int distroy=0;          //decide the distroyed one
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(getPresentContent(i,j)==12)
                count++;
        }
    }
    //srand(time(NULL));
    distroy=rand()%count+1;
    count=0;
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            if(getPresentContent(i,j)==12){
                count++;
                if(count==distroy)
                    future[i][j]=0;
            }
        }
    }
}
