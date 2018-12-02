#include "wall.h"

Wall::Wall(int r, int c, QWidget* _parent) :
    Block(r,c, _parent)
{
    this->col = c;
    this->row = r;
}

char Wall::getType() const {
    return IMAGE_TYPE.front();
}

void Wall::setRow(int r) {
    this->row = r;
    setGeometry(QRect(col*BLOCK_SIZE,r*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
}

void Wall::setCol(int c) {
    this->col = c;
    setGeometry(QRect(c*BLOCK_SIZE,row*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));

}
