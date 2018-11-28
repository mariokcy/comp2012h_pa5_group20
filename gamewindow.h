#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "gamecontrol.h"
#include <vector>
/*
 * Assumption :
 * The map is composed by a 15*15 block, information from the map is stored in a vector vector
 * i.e. std::vector<std::vector<int>> map
 * int indicate the blocks type and status
 * for every key press, use move by one block
 *
 * */

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(GameControl* _game, QWidget *parent = nullptr);
    void paint_map();
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    static const int BLOCK_SIZE = 50; // 20px*20px
    virtual void keyPressEvent(QKeyEvent *event) override;
    GameControl* game;
    std::vector<std::vector<int>> map = {{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}};
    std::vector<Block*> map_block ={};
signals:
    void KeyPress(int key);
};

#endif // GAMEWINDOW_H
