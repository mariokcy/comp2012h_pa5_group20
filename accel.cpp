#include "accel.h"

Accel::Accel(int r, int c,DIRECTION _dir, QWidget* _parent) :
    Block(r, c, _parent),
    dir(_dir)
{
    this->col = c;
    this->row = r;
}

char Accel::getType() const {
    return IMAGE_TYPE.front();
}

DIRECTION Accel::getDir() const {
    return dir;
}

void Accel::set_image(Player player) {
    if(player_isHere(player)){
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/player.png\");"));
    }
    else {
        string str = "";
        str.push_back(getType());
        setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + "_" + std::to_string(dir) + ".png\");"));
    }
}
void Accel::setRow(int r) {
    this->row = r;
    setGeometry(QRect(col*BLOCK_SIZE,r*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
}

void Accel::setCol(int c) {
    this->col = c;
    setGeometry(QRect(c*BLOCK_SIZE,row*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
}
