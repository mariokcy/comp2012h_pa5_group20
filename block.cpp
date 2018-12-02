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

void Block::set_image(Player player) {
    if(player_isHere(player)){
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/player.png\");"));
    }
    else {
        string str = "";
        str.push_back(getType());
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
    }


}

int Block::getRow() const {
    return row;
}

bool Block::player_isHere(Player player) {
    return player.getRow()==row && player.getCol() == col;

}

int Block::getCol() const {
    return col;
}
