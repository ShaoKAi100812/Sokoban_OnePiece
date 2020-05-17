#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QApplication>
using namespace std;

//Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signal_w()), this, SLOT(up_case()));
    connect(this, SIGNAL(signal_a()), this, SLOT(left_case()));
    connect(this, SIGNAL(signal_s()), this, SLOT(down_case()));
    connect(this, SIGNAL(signal_d()), this, SLOT(right_case()));
    connect(this, SIGNAL(signal_pass()), this, SLOT(pass_case()));
    connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(subMenu()));
    connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(closeWindow()));

    QPixmap bg(":/pic/background.png");
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            //build up background, invisible
            background[i][j]=new QLabel(this);
            background[i][j]->setGeometry(45+90*j,45+90*i,90,90);
            background[i][j]->setPixmap(bg);
            background[i][j]->setScaledContents(true);
            background[i][j]->setVisible(false);
            //build up original map, invisible
            present[i][j]=new QLabel(this);
            present[i][j]->setGeometry(45+90*j,45+90*i,90,90);
            decideLabel(present[i][j], g1.getPresentContent(i,j));
            present[i][j]->setScaledContents(true);
            present[i][j]->setVisible(false);
        }
    }
    //setup pass label, invisible
    cong=new QLabel(this);
    QPixmap pass(":/pic/pass.jpg");
    cong->setGeometry(50,50,800,620);
    cong->setPixmap(pass);
    cong->setScaledContents(true);
    cong->setVisible(false);
    //setup subButton, invisible
    for(int i=0;i<3;i++){
        subButton[i]=new QPushButton(this);
        subButton[i]->setGeometry(150,160*(i+1),600,120);
        subButton[i]->setVisible(false);
        subButton[i]->setStyleSheet("font: bold; font-family: Purisa, Bold; font-size: 40px;");
    }
    subButton[0]->setText("Level 1");
    subButton[1]->setText("Level 2");
    subButton[2]->setText("Back");
    connect(subButton[0], SIGNAL(clicked()), this, SLOT(stage_1_case()));
    connect(subButton[1], SIGNAL(clicked()), this, SLOT(stage_2_case()));
    connect(subButton[2], SIGNAL(clicked()), this, SLOT(back2Menu()));
    //setup stepLabel, invisible
    step=new QLabel(this);
    step->setGeometry(100,675,100,45);
    step->setText("Step :");
    step->setStyleSheet("font: bold; font-family: Purisa, Bold; font-size: 20px;");
    step->setVisible(false);
    countStep=new QLabel(this);
    countStep->setGeometry(180,675,100,45);
    countStep->setStyleSheet("font: bold; font-family: Purisa, Bold; font-size: 24px;");
    countStep->setNum(0);
    countStep->setVisible(false);
    //setup menuButton, invisible
    menuButton=new QPushButton(this);
    menuButton->setGeometry(600,675,100,45);
    menuButton->setText("Menu");
    menuButton->setStyleSheet("font: bold; font-family: Purisa, Bold; font-size: 24px;");
    menuButton->setVisible(false);
    connect(menuButton, SIGNAL(clicked()), this, SLOT(back2Menu()));
    //setup testButton, invisible
    testButton=new QPushButton(this);
    testButton->setGeometry(400,675,100,45);
    testButton->setText("Retart");
    testButton->setStyleSheet("font: bold; font-family: Purisa, Bold; font-size: 24px;");
    testButton->setVisible(false);
    connect(testButton, SIGNAL(clicked()), this, SLOT(testItem()));
}

//Distructor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(g1.getState()){
        if(e->key() == Qt::Key_W){
            emit signal_w();
        }
        else if(e->key() == Qt::Key_A){
            emit signal_a();
        }
        else if(e->key() == Qt::Key_S){
            emit signal_s();
        }
        else if(e->key() == Qt::Key_D){
            emit signal_d();
        }
    }
}

void MainWindow::decideLabel(QLabel *label, int content){
    QPixmap bg(":/pic/background.png");
    QPixmap treasure_closed(":/pic/treasure_closed.png");
    QPixmap p(":/pic/player.png");
    QPixmap tree(":/pic/tree.png");
    QPixmap treasure_open(":/pic/treasure_open.png");
    QPixmap position(":/pic/position.png");
    QPixmap together(":/pic/together.png");
    QPixmap fruit(":/pic/fruit.png");
    switch (content){
    case -1: case 0:
        label->setPixmap(bg);
        break;
    case 1:
        label->setPixmap(p);
        break;
    case 3:
        label->setPixmap(tree);
        break;
    case 5:
        label->setPixmap(position);
        break;
    case 7:
        label->setPixmap(treasure_closed);
        break;
    case 9:
        label->setPixmap(fruit);
        break;
    case 6:
        label->setPixmap(together);
        break;
    case 12:
        label->setPixmap(treasure_open);
        break;
    default:
        exit(1);
    }
}

void MainWindow::up_case(){
    g1.setFuture_w();
    if(g1.isLegal()){
        stepNum++;
        countStep->setNum(stepNum);
        g1.setPresent();
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                if(g1.getPresentContent(i,j)==1 ||
                        g1.getPresentContent(i,j)==6){
                    decideLabel(present[i-1][j],g1.getPresentContent(i-1,j));
                    decideLabel(present[i][j],g1.getPresentContent(i,j));
                    decideLabel(present[i+1][j],g1.getPresentContent(i+1,j));
                }
            }
        }
        ifEatMoment();
        if(g1.isPass())
            emit signal_pass();
    }
    else
        g1.resetFuture();
}

void MainWindow::left_case(){
    g1.setFuture_a();
    if(g1.isLegal()){
        stepNum++;
        countStep->setNum(stepNum);
        g1.setPresent();
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                if(g1.getPresentContent(i,j)==1 ||
                        g1.getPresentContent(i,j)==6){
                    decideLabel(present[i][j-1],g1.getPresentContent(i,j-1));
                    decideLabel(present[i][j],g1.getPresentContent(i,j));
                    decideLabel(present[i][j+1],g1.getPresentContent(i,j+1));
                }
            }
        }
        ifEatMoment();
        if(g1.isPass())
            emit signal_pass();
    }
    else
        g1.resetFuture();
}

void MainWindow::down_case(){
    g1.setFuture_s();
    if(g1.isLegal()){
        stepNum++;
        countStep->setNum(stepNum);
        g1.setPresent();
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                if(g1.getPresentContent(i,j)==1 ||
                        g1.getPresentContent(i,j)==6){
                    decideLabel(present[i-1][j],g1.getPresentContent(i-1,j));
                    decideLabel(present[i][j],g1.getPresentContent(i,j));
                    decideLabel(present[i+1][j],g1.getPresentContent(i+1,j));
                }
            }
        }
        ifEatMoment();
        if(g1.isPass())
            emit signal_pass();
    }
    else
        g1.resetFuture();
}

void MainWindow::right_case(){
    g1.setFuture_d();
    if(g1.isLegal()){
        stepNum++;
        countStep->setNum(stepNum);
        g1.setPresent();
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                if(g1.getPresentContent(i,j)==1 ||
                        g1.getPresentContent(i,j)==6){
                    decideLabel(present[i][j-1],g1.getPresentContent(i,j-1));
                    decideLabel(present[i][j],g1.getPresentContent(i,j));
                    decideLabel(present[i][j+1],g1.getPresentContent(i,j+1));
                }
            }
        }
        ifEatMoment();
        if(g1.isPass())
            emit signal_pass();
    }
    else
        g1.resetFuture();
}

void MainWindow::pass_case(){
    hideAllObject();
    //initialize bellow objects
    step->setVisible(true);
    countStep->setVisible(true);
    menuButton->setVisible(true);
    testButton->setVisible(true);
    if(g1.getStage()==1){
        /* lack of wait function */
        //cong->setVisible(true);
        //cong->setVisible(false);
        stage_2_case();
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                background[i][j]->setVisible(true);
                present[i][j]->setVisible(true);
            }
        }
    }
    else if(g1.getStage()==2){
        /* lack of wait function */
        //cong->setVisible(true);
        //cong->setVisible(false);
        stage_1_case();
        g1.setState(false);
        ui->Button_1->setText("Start Game");
        back2Menu();
    }
}

void MainWindow::hideAllObject(){
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            background[i][j]->setVisible(false);
            present[i][j]->setVisible(false);
        }
    }
    cong->setVisible(false);
    ui->back->setVisible(false);
    ui->topic->setVisible(false);
    ui->Button_1->setVisible(false);
    ui->Button_2->setVisible(false);
    ui->Button_3->setVisible(false);
    for(int i=0;i<3;i++){
        subButton[i]->setVisible(false);
    }
    step->setVisible(false);
    countStep->setVisible(false);
    menuButton->setVisible(false);
    testButton->setVisible(false);
}

void MainWindow::closeWindow(){
    this->close();
}

void MainWindow::subMenu(){
    hideAllObject();
    ui->back->setVisible(true);
    for(int i=0;i<3;i++){
        subButton[i]->setVisible(true);
    }
}

void MainWindow::start(){
    hideAllObject();
    g1.setState(true);
    step->setVisible(true);
    countStep->setVisible(true);
    menuButton->setVisible(true);
    testButton->setVisible(true);
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            background[i][j]->setVisible(true);
            present[i][j]->setVisible(true);
        }
    }
}

void MainWindow::stage_1_case(){
    g1.setStage(1);
    //clean the step
    stepNum=0;
    countStep->setNum(stepNum);
    //clean the EatMoment
    findEatMoment=0;
    g1.setEat(false);
    //reload pic of map
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            decideLabel(present[i][j], g1.getPresentContent(i,j));
        }
    }
    start();
}

void MainWindow::stage_2_case(){
    g1.setStage(2);
    //clean the step
    stepNum=0;
    countStep->setNum(stepNum);
    //clean the EatMoment
    findEatMoment=0;
    g1.setEat(false);
    //reload pic of map
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            decideLabel(present[i][j], g1.getPresentContent(i,j));
        }
    }
    start();
}

void MainWindow::back2Menu(){
    hideAllObject();
    if(g1.getState()==true){
        ui->Button_1->setText("Continue");
    }
    g1.setState(false);
    ui->back->setVisible(true);
    ui->topic->setVisible(true);
    ui->Button_1->setVisible(true);
    ui->Button_2->setVisible(true);
    ui->Button_3->setVisible(true);
}

//for restartButton
void MainWindow::testItem(){
    stepNum=0;
    countStep->setNum(stepNum);
    findEatMoment=0;
    g1.setEat(false);
    g1.setStage(g1.getStage());
    for(int i=0;i<7;i++){
        for(int j=0;j<9;j++){
            decideLabel(present[i][j], g1.getPresentContent(i,j));
        }
    }
}

void MainWindow::ifEatMoment(){
    if(g1.getEat()==true)
        findEatMoment++;
    if(g1.getEat()==true&&findEatMoment==1){
        for(int i=0;i<7;i++){
            for(int j=0;j<9;j++){
                decideLabel(present[i][j],g1.getPresentContent(i,j));
            }
        }
    }
}
