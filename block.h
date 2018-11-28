#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <QPushButton>
#include <QDebug>

using std::string;

class gameControl;

class Block : public QPushButton
{
    Q_OBJECT

public:
    Block(QWidget* _parent = nullptr,
          gameControl* _game = nullptr,
          int _y = 0,
          int _x = 0,
          int _type = 0,
          int _orientation = 0);
private:
    gameControl* game;
    int x;
    int y;
    int orientation;
    int type;

    static const int BLOCK_SIZE = 20; // Size of block is 20px

    // Method
    void set_image();
};

#endif // BLOCK_H
