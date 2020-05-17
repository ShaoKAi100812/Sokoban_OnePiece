#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void decideLabel(QLabel *label, int content);
    void up_case();
    void left_case();
    void down_case();
    void right_case();
    void pass_case();
    void hideAllObject();
    void closeWindow();
    void subMenu();
    void start();
    void stage_1_case();
    void stage_2_case();
    void back2Menu();
    void testItem();        //for restart
    void ifEatMoment(); //reload pic at eat moment

signals:
    void signal_w();
    void signal_a();
    void signal_s();
    void signal_d();
    void signal_pass();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;
    player g1;
    QLabel *(background[7][9]);
    QLabel *(present[7][9]);
    QPushButton *(subButton[3]);
    QLabel *cong;
    int stepNum=0;
    QLabel *step;
    QLabel *countStep;
    QPushButton *menuButton;
    QPushButton *testButton;             //for restart
    int findEatMoment=0;

};

#endif // MAINWINDOW_H
