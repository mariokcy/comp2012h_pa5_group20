#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QString>
#include <vector>
#include "block.h"

class GameWindow;
// Control the game Flow
class GameControl : public QObject
{
    Q_OBJECT

public:
    GameControl();
    ~GameControl();
    std::vector<std::vector<int>> map = {{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}};
    std::vector<Block*> map_block ={};

private:
    int player[2] = {0,0};
    GameWindow* game_window;
    static const int MAX_COL = 4;
    static const int MAX_ROW = 4;

public slots:
    void move(int key);
};

#endif // GAMECONTROL_H
