#include "terminate.h"

Terminate::Terminate(int r, int c, QWidget* _parent) :
    Block(r, c, _parent)
{

}

char Terminate::getType() const {
    return IMAGE_TYPE.front();
}

