#include "road.h"

Road::Road(int r, int c, QWidget* _parent) :
    Block(r, c, _parent)
{

}

char Road::getType() const {
    return IMAGE_TYPE.front();
}

