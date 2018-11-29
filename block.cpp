#include "block.h"
#include "gamecontrol.h"
#include <string>
#include <sstream>
#include <QPushButton>
#include <QDebug>

using std::string;

Block::Block(int r,
             int c,
             QWidget* _parent):
    QPushButton(_parent),
    row(r),
    col(c)
{
    setText(""); // Remove all word in the block
    setAutoFillBackground(true);
    setFlat(true); //Flatten block
    setGeometry(QRect(col*BLOCK_SIZE,row*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
    setStyleSheet("border: none"); // Remove border
    setVisible(true);
}

void Block::set_image() {
    string str = "";
    str.push_back(getType());
    setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
}

int Block::getRow() const {
    return row;
}

void Block::player_here(bool isHere) {
    if (isHere) {
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/player.png\");"));
    }
}
