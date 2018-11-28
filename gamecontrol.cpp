#include "gamecontrol.h"
#include "gamewindow.h"
#include <iostream>
#include <QDebug>
using std::cout;
using std::cin;

GameControl::GameControl() :
    game_window(new GameWindow(this, nullptr))
{
    game_window->paint_map();
    game_window->show();
}

GameControl::~GameControl() {

}

void GameControl::move(int key) {
    switch (key)
    {
    case Qt::Key_W:
        if (player[0] > 0 && (map[player[0] - 1])[player[1]] == 1) {
            player[0] = player[0] - 1;
        }
        break;
    case Qt::Key_S:
        if (player[0] < MAX_ROW - 1 && map[player[0] + 1][player[1]] == 1) {
            player[0] = player[0] + 1;
        }
        break;
    case Qt::Key_A:
        if (player[1] > 0 && map[player[0]][player[1] - 1] == 1) {
            player[1] = player[1] - 1;
        }
        break;
    case Qt::Key_D:
        if (player[1] < MAX_COL - 1 && map[player[0]][player[1] + 1] == 1) {
            player[1] = player[1] + 1;
        }
        break;
    }

    qDebug("%d||||||%d",player[0], player[1]);
}
