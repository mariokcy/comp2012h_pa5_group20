#include "block.h"
#include "gamecontrol.h"
#include <string>
#include <sstream>
#include <QPushButton>
#include <QDebug>

using std::string;

Block::Block(QWidget *_parent,
             GameControl *_game,
             int _y,
             int _x,
             int _type,
             int _orientation):
    QPushButton (_parent),
    game(_game),
    x(_x),
    y(_y),
    orientation(_orientation),
    type(_type)
{
    setText(""); // Remove all word in the block
    setAutoFillBackground(true);
    setFlat(true); //Flatten block
    setGeometry(QRect(x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
    setStyleSheet("border: none"); // Remove border
    set_image();
    setVisible(true);
}

void Block::set_image() {
    if (type == 0) {
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_w.png\");"));
    } else {
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_r.png\");"));
    }
}
