#include "wall.h"

Wall::Wall(int r, int c, QWidget* _parent) :
    Block(r,c, _parent)
{

}

char Wall::getType() const {
    return IMAGE_TYPE.front();
}
