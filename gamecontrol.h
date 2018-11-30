#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QString>
#include <vector>
#include "block.h"
#include "player.h"

class GameWindow;
// Control the game Flow
class GameControl : public QObject
{
    Q_OBJECT

public:
    GameControl();
    ~GameControl();
    enum {W, R, T, A, B, C, D}; // W: Wall, R: Road, T: Stop A,B,C,D: wsad Accelerator
    std::vector<std::vector<int>> map = {{1,0,0,1,0,0,0,0},{4,0,0,1,0,0,0,0},{2,0,0,1,0,0,0,0},{6,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    std::vector<std::vector<Block*>> board = {};
    Player* player;

private:
    GameWindow* game_window;
    static const int MAX_COL = 8;
    static const int MAX_ROW = 8;

public slots:
    void move(int key);
};

#endif // GAMECONTROL_H
