#ifndef SOKOBAN_H
#define SOKOBAN_H

class Sokoban{

public:
    Sokoban();
    void setPresent();
    void setFuture(char a);
    void resetFuture();
    void showPresent();
    bool isLegal();
    bool isPass();
    
private:
    int origin[7][9]={ { 3, 3, 3, 3, -1, 3, 3, 3, 3},{ 3, 0, 0, 3, 3, 3, 0, 0, 3},{ 3, 0, 7, 0, 12, 0, 7, 0, 3},{ 3, 0, 0, 0, 6, 0, 0, 0, 3},{ 3, 3, 3, 0, 5, 7, 3, 3, 3},{ -1, -1, 3, 0, 5, 0, 3, -1, -1},{ -1, -1, 3, 3, 3, 3, 3, -1, -1} };
    int present[7][9];
    int future[7][9];
    
};
#endif
