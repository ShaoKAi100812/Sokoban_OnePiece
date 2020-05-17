#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class player : public QObject
{
    Q_OBJECT

public:
    player();
    void setPresent();
    void setFuture_w();
    void setFuture_a();
    void setFuture_s();
    void setFuture_d();
    void resetFuture();
    bool isLegal();
    bool isPass();
    int getPresentContent(int x, int y);
    int getFutureContent(int x, int y);
    void setState(bool IsGameStart);
    bool getState();
    void setStage(int GameStage);
    int getStage();
    void setEat(bool IsFruitEaten);
    bool getEat();
    void distroyTarget();

private:
    int stage_1[7][9]={ { 3, 3, 3, 3, -1, 3, 3, 3, 3},
                       { 3, 0, 0, 3, 3, 3, 0, 0, 3},
                       { 3, 0, 7, 0, 12, 0, 7, 0, 3},
                       { 3, 0, 0, 0, 6, 0, 0, 0, 3},
                       { 3, 3, 3, 0, 5, 7, 3, 3, 3},
                       { -1, -1, 3, 0, 5, 0, 3, -1, -1},
                       { -1, -1, 3, 3, 3, 3, 3, -1, -1} };
    //add a fruit (9) in stage 2
    int stage_2[7][9]={ { 3, 3, 3, 3, 3, 3, 3, -1, -1},
                       { 3, 0, 0, 5, 7, 0, 3, 3, 3},
                       { 3, 0, 5, 7, 5, 7, 0, 9, 3},
                       { 3, 12, 7, 5, 7, 5, 1, 0, 3},
                       { 3, 0, 5, 7, 5, 7, 0, 3, 3},
                       { 3, 0, 0, 5, 7, 0, 0, 3, -1},
                       { 3, 3, 3, 3, 3, 3, 3, 3, -1} };
    int present[7][9];
    int future[7][9];
    bool state;         //judge if the game starts
    int stage;          //judge which stage it is
    bool eat;          //judge if the fruit has been eat

};

#endif // PLAYER_H
