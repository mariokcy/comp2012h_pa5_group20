
#include "gamecontrol.h"
#include "gamewindow.h"
#include <iostream>
#include <QDebug>
#include "accel.h"
#include <algorithm>
#include <QMessageBox>
#include "record.h"
#include <QFile>
#include "search_algorithm.h"

using std::cout;
using std::cin;

GameControl::GameControl() :
    player(new Player(PLAYER_X,PLAYER_Y)),
    game_window(new GameWindow(this, nullptr))
{
    readfile(map);
    game_window->load_map();
    game_window->show();
}

GameControl::~GameControl() {
    delete player;
    player = nullptr;
    for (int i = 0; i < board.size(); ++i) {
        for( int j = 0; j < board.size(); ++j) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
    delete game_window;
    game_window = nullptr;
}

void GameControl::move(int key) {
    if (gameEnd) return;
    DIRECTION dir = UP; // Default : UP
    if (player->isAccel()) {
        dir = player->getDir();
    } else {
        std::vector<Qt::Key> key_list = {Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D};
        for (std::vector<Qt::Key>::iterator i = key_list.begin(); i != key_list.end(); ++i) {
            if (key == *i) {
                dir = static_cast<DIRECTION>(i-key_list.begin());
            }
        }
        if (key == Qt::Key_R) {
            rotate();
            return;
        }
        if (key==Qt::Key_C) {

        }
    }
    // Walk to the desire position
    std::vector<int> temp = Search_algorithm::checkEndPoint(&board,player->getRow(),player->getCol(),dir);
    player->setRow(temp[0]);
    player->setCol(temp[1]);
    game_window->update_map();
    qDebug("%d||||||%d",player->getRow(), player->getCol());
    step++;
    if(player->getRow()==goal_x && player->getCol()==goal_y) {
        QMessageBox::information(nullptr, "Congraulations!You arrived the end point.", QString::fromStdString("You have use " + std::to_string(step) + "steps!"));
        gameEnd = true;
    }
}

//update map by rotate 90 degree and also change all related to direction such as accelerater, player
void GameControl::rotate() {
    qDebug() << "rotate";
    std::vector<std::vector<int>> new_map;

    //rotate the map and store in new_map
    for (int oldCol = 0; oldCol< map.size(); ++oldCol) {
        std::vector<int> new_row;

        for (int oldRow = map.size()-1; oldRow>=0; --oldRow) {
            int update=0;
            switch(map[oldRow][oldCol]){
            //rotate accelerater
            case UP+3: update=RIGHT+3; break;
            case DOWN+3: update=LEFT+3; break;
            case LEFT+3: update=UP+3; break;
            case RIGHT+3: update=DOWN+3; break;
            default:update=map[oldRow][oldCol];break;
            }

            new_row.push_back(update);
        }
        new_map.push_back(new_row);
    }
    //deep copy the new_map to original map
    for (int i=0; i< map.size();++i){
        for (int j=0; j< map.size();++j){
            map[i][j]=new_map[i][j];
        }
    }
    //rotate player
    int r = player->getRow();
    int c = player->getCol();
    player->setRow(c);
    player->setCol(MAX_COL-1-r);
    switch(player->getDir()){
    case UP:
        player->setDir(LEFT);
        break;
    case LEFT:
        player->setDir(DOWN);
        break;
    case DOWN:
        player->setDir(RIGHT);
        break;
    case RIGHT:
        player->setDir(UP);
        break;
    }
    int x = goal_x;
    goal_x = MAX_COL - goal_y;
    goal_y = x;

    //reload and update the map
    game_window->load_map();
    game_window->update_map();
}

void GameControl::readfile(std::vector<std::vector<int>> &map) {
    QFile file(QString::fromStdString(":/map.txt")) ;
    if(!(file.open(QIODevice::ReadOnly))) {
        qDebug() << "Cannot find map file!";
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    int counter = 0;
    map.clear();
    while(line != QString("}") && counter <= 999) {
        counter++;
        if (line == "{") {
            line = in.readLine();
            continue;
        };
        line.remove("{");
        line.remove("}");
        std::vector<int> row_vector = {};
        for (int i = 0; i < line.count(QRegExp("[0-9]")); ++i) {
            QString element = line.section(QChar(','),i,i);
            row_vector.push_back(element.toInt());
        }
        map.push_back(row_vector);
        line = in.readLine();
    }
    if (counter>= 999) qDebug("Error: infinite loop in readfile while loop!");
    file.close();
}

