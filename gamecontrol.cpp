
#include "gamecontrol.h"
#include "gamewindow.h"
#include <iostream>
#include <QDebug>
#include <algorithm>
#include "record.h"
#include "search_algorithm.h"

using std::cout;
using std::cin;

GameControl::GameControl() :
    player(new Player(0,0)),
    game_window(new GameWindow(this, nullptr))
{
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
        if (r > 0 && board[r - 1][c]->getType() != 'w') {
            player->setRow(r - 1);
            player->setDir(UP);
        }
        else
            player->setAccel(false);

        break;

    case DOWN:
        if (r < MAX_ROW - 1 &&
                board[r + 1][c]->getType() != 'w') {
            player->setRow(r + 1);
            player->setDir(DOWN);
        }
        else
            player->setAccel(false);

        break;
    case LEFT:
        if (c > 0 &&
                board[r][c - 1]->getType() != 'w') {
            player->setCol(c - 1);
            player->setDir(LEFT);
        }
        else
            player->setAccel(false);
        break;

    case RIGHT:
        if (c < MAX_COL - 1 && board[r][c + 1]->getType() != 'w') {
            player->setCol(c + 1);
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
        Accel* temp = dynamic_cast<Accel*> (board[r][c]);
        player->setDir(temp->getDir());
        player->setAccel(true);
    } else if (board[r][c]->getType() == 't') {
        player->setAccel(false);
    }

    if (player->isAccel()) {
        // End the accelerating situation if the condition is fulfilled
        switch (player->getDir())
        {

        case UP:
            if (r <= 0 || !(board[r - 1][c]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case DOWN:
            if (r >= MAX_ROW - 1 || !(board[r + 1][c]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;
        case LEFT:
            if (c <= 0 || !(board[r][c - 1]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case RIGHT:
            if (c >= MAX_COL - 1 || !(board[r][c + 1]->getType() != 'w')) {
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
//    std::vector<std::vector<Block *>> new_board = {};
//    for (int i = 0; i< MAX_ROW; ++i) {
//        std::vector<Block *> new_row = {};
//        for (int j = 0; j < MAX_COL; ++j) {
//            new_row.push_back(board[j][MAX_ROW-1-i]);
//            board[j][MAX_ROW-i-1]->setRow(i);
//            board[j][MAX_ROW-i-1]->setCol(j);
//        }
//        new_board.push_back(new_row);
//    }
//    board = {};
//    for (int i = 0; i < new_board.size(); ++i) {
//        board.push_back(new_board[MAX_ROW-i-1]);
//    }
//    qDebug("%d %d %d %d", new_board.size(), (new_board[0]).size(), board.size(), (board[0]).size());
    std::vector<std::vector<Block*>> new_board [MAX_ROW][MAX_COL];
    for (int i = 0; i< MAX_ROW; ++i) {
        for (int j = 0; j<MAX_COL; ++j) {
            int old_r = board[i][j]->getRow();
            int old_c = board[i][j]->getCol();
            board[i][j]->setRow(board.size()-old_c);
            board[i][j]->setCol(old_r);
       }
    }
    int r = player->getRow();
    int c = player->getCol();
    player->setRow(MAX_COL-1-c);
    player->setCol(r);
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
    qDebug() << "The player is now at"<< player->getRow()<< ", "<< player->getCol();
    qDebug() << "Facing " << player->getDir();
    game_window->update_map();
}
