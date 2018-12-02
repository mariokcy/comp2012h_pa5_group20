#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QString>
#include <vector>
#include "block.h"
#include <stack>

class GameWindow;
// Control the game Flow
class GameControl : public QObject
{
    Q_OBJECT

public:
    GameControl();
    ~GameControl();
    enum {W, R, T, A, B, C, D}; // W: Wall, R: Road, T: Stop A,B,C,D: wsad Accelerator
    std::vector<std::vector<int>> map = {{1,0,0,1,0,0,0,0},
                                         {4,0,0,1,0,0,0,0},
                                         {2,0,0,1,0,0,0,0},
                                         {6,1,1,1,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0}};
    std::vector<std::vector<Block*>> board = {};
    Player* player;
    GameWindow* game_window;

private:
    void rotate();
    void readfile(std::vector<std::vector<int>> &map);

    static const int MAX_COL = 20;
    static const int MAX_ROW = 20;

    static const int PLAYER_X = 0;
    static const int PLAYER_Y = 1;

public slots:
    void move(int key);
};

#endif // GAMECONTROL_H
