#include "gamewindow.h"
#include "block.h"
#include "ui_gamewindow.h"
#include <QPushButton>

#include <iostream>
#include "qdebug.h"
#include <string>
#include <sstream>
using std::cout;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    paint_map();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::paint_map() {
    qDebug() << "hi";
    for (std::vector<std::vector<int>>::iterator row = map.begin(); row != map.end(); ++row) {
        std::vector<int> col_list = *row;
        for (std::vector<int>::iterator block = col_list.begin(); block != col_list.end(); ++block) {
            if (*block == 0) {
                // debug
                qDebug()<< "w ";
            } else {
                qDebug() << "r ";
            }
            Block* me = new Block(this, nullptr, row-map.begin(),block - col_list.begin(),*block, 0);
        }
        qDebug() << '\n';
    }
}
