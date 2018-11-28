#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <string>
#include "block.h"
/*
 * Assumption :
 * The map is composed by a 15*15 block, information from the map is stored in a vector vector
 * i.e. std::vector<std::vector<int>> map
 * int indicate the blocks type and status
 * for every key press, use move by one block
 *
 * */

//Control Game Window Display
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    void rotate();

    ~GameWindow();

private:
    Ui::GameWindow *ui;
    static const int BLOCK_SIZE = 20; // 20px*20px


    void paint_map();
    std::vector<std::vector<int>> map = {{0,1,0,1},{0,1,1,0},{1,1,1,1},{0,0,0,0}};
    std::vector<std::vector<Block*>> map_block ={{}};
};

#endif // GAMEWINDOW_H
