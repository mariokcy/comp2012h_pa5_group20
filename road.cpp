#include "road.h"

Road::Road(int r, int c, QWidget* _parent) :
    Block(r, c, _parent)
{
    this->col = c;
    this->row = r;
}

char Road::getType() const {
    return IMAGE_TYPE.front();
}

void Road::setRow(int r) {
    this->row = r;
    setGeometry(QRect(col*BLOCK_SIZE,r*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
}

void Road::setCol(int c) {
    this->col = c;
    setGeometry(QRect(c*BLOCK_SIZE,row*BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE));
}
