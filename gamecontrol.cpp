
#include "gamecontrol.h"
#include "gamewindow.h"
#include <iostream>
#include <QDebug>
#include <QFile>
#include <algorithm>
#include "record.h"
#include "search_algorithm.h"

using std::cout;
using std::cin;

GameControl::GameControl() :
    player(new Player(0,0)),
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
        if (key == Qt::Key_C) {
            Search_algorithm temp (this);
            temp.BFS(&board,player->getRow(),player->getCol(), 19, 19);
        }

    }
    // Walk to the desire position
    int r = player->getRow(); int c = player->getCol();
    switch (dir)
    {
    case UP:// map[r-1][c].PASSABLE != false
        if (r > 0 && board[r+row[UP]][c+col[UP]]->getType() != 'w') {
            player->setRow(r+row[UP]);
            player->setDir(UP);
        }
        else
            player->setAccel(false);

        break;

    case DOWN:
        if (r < MAX_ROW - 1 &&
                board[r+row[DOWN]][c+col[DOWN]]->getType() != 'w') {
            player->setRow(r+row[DOWN]);
            player->setDir(DOWN);
        }
        else
            player->setAccel(false);

        break;
    case LEFT:
        if (c > 0 &&
                board[r+row[LEFT]][c+col[LEFT]]->getType() != 'w') {
            player->setCol(c+col[LEFT]);
            player->setDir(LEFT);
        }
        else
            player->setAccel(false);
        break;

    case RIGHT:
        if (c < MAX_COL - 1 && board[r+row[RIGHT]][c +col[RIGHT]]->getType() != 'w') {
            player->setCol(c+col[RIGHT]);
            player->setDir(RIGHT);
        }
        else
            player->setAccel(false);
        break;
    }
    game_window->update_map();
    // Update r and c
    r = player->getRow(); c = player->getCol();

    // Position of the player is changed according to their key pressed
    //update dir and accel
    if (board[r][c]->getType() == 'a') {

        player->setDir(dynamic_cast<Accel*> (board[r][c])->getDir());
        player->setAccel(true);
    } else if (board[r][c]->getType() == 't') {
        player->setAccel(false);
    }

    if (player->isAccel()) {
        // End the accelerating situation if the condition is fulfilled
        switch (player->getDir())
        {

        case UP:
            if (r <= 0 || !(board[r+row[UP]][c+col[UP]]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case DOWN:
            if (r >= MAX_ROW - 1 || !(board[r+row[DOWN]][c+col[DOWN]]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;
        case LEFT:
            if (c <= 0 || !(board[r+row[LEFT]][c+col[LEFT]]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case RIGHT:
            if (c >= MAX_COL - 1 || !(board[r+row[RIGHT]][c+col[RIGHT]]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;
        }

    }
    game_window->update_map();
    qDebug("%d||||||%d",player->getRow(), player->getCol());

}
void GameControl::rotate() {
    qDebug() << "rotate";
    std::vector<std::vector<int>> new_map;

    for (int oldCol = 0; oldCol< map.size(); ++oldCol) {
        std::vector<int> new_row;

        for (int oldRow = map.size()-1; oldRow>=0; --oldRow) {
            int update=0;
            switch(map[oldRow][oldCol]){
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

    for (int i=0; i< map.size();++i){
        for (int j=0; j< map.size();++j){
            map[i][j]=new_map[i][j];
        }
    }
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
