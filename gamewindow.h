#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "gamecontrol.h"
#include "accel.h"

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
    void load_map();
    void update_map();
//    void rotate();
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    GameControl* game;
    static const int BLOCK_SIZE = 50; // 20px*20px
    void closeEvent(QCloseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event) override;
    void paint_player();
signals:
    void KeyPress(int key);
    void gameWindow_closed();
};

#endif // GAMEWINDOW_H
