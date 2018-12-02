#ifndef BLOCK_H
#define BLOCK_H

#include <QPushButton>
#include <QDebug>
#include "player.h"

using std::string;

class GameControl;
// Base class of different block type
// is Abstract Base Class
class Block : public QPushButton
{
    Q_OBJECT

public:
    Block(int r, int c, QWidget* _parent = nullptr);
    int getRow() const;
    int getCol() const;
    virtual void setRow(int r) = 0;
    virtual void setCol(int c)= 0;
    virtual char getType() const =0; // virtual function

    virtual void set_image(Player player);
    bool player_isHere(Player player);

protected:
    int row;
    int col;

    static const int BLOCK_SIZE = 50; // Size of block is 20px
};

#endif // BLOCK_H
