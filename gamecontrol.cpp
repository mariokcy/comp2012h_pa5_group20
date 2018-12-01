#include "gamecontrol.h"
#include "gamewindow.h"
#include <iostream>
#include <QDebug>
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

}

void GameControl::move(int key) {
    Accel::DIRECTION dir = Accel::UP; // Default : UP
    if (player->isAccel()) {
        dir = player->getDir();
    } else {
        std::vector<Qt::Key> key_list = {Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D};
        for (std::vector<Qt::Key>::iterator i = key_list.begin(); i != key_list.end(); ++i) {
            if (key == *i) {
                dir = static_cast<Accel::DIRECTION>(i-key_list.begin());
            }
        }
        if (key == Qt::Key_R) {
            game_window->rotate(0);
        }

    }
    // Walk to the desire position
    int r = player->getRow(); int c = player->getCol();
    switch (dir)
    {
    case Accel::UP:// map[r-1][c].PASSABLE != false
        if (r > 0 && board[r - 1][c]->getType() != 'w') {
            player->setRow(r - 1);
            player->setDir(Accel::UP);
        }
        else
            player->setAccel(false);

        break;

    case Accel::DOWN:
        if (r < MAX_ROW - 1 &&
                board[r + 1][c]->getType() != 'w') {
            player->setRow(r + 1);
            player->setDir(Accel::DOWN);
        }
        else
            player->setAccel(false);

        break;
    case Accel::LEFT:
        if (c > 0 &&
                board[r][c - 1]->getType() != 'w') {
            player->setCol(c - 1);
            player->setDir(Accel::LEFT);
        }
        else
            player->setAccel(false);
        break;

    case Accel::RIGHT:
        if (c < MAX_COL - 1 && board[r][c + 1]->getType() != 'w') {
            player->setCol(c + 1);
            player->setDir(Accel::RIGHT);
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

        case Accel::UP:
            if (r <= 0 || !(board[r - 1][c]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case Accel::DOWN:
            if (r >= MAX_ROW - 1 || !(board[r + 1][c]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;
        case Accel::LEFT:
            if (c <= 0 || !(board[r][c - 1]->getType() != 'w')) {
                player->setAccel(false);
            } else {
                move(key);
            }
            break;

        case Accel::RIGHT:
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
