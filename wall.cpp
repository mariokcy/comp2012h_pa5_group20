#include "wall.h"

Wall::Wall(int r, int c, QWidget* _parent) :
    Block(r,c, _parent)
{

}

char Wall::getType() const {
    return IMAGE_TYPE.front();
}

void Wall::set_image() {
    string str = "";
    str.push_back(getType());
    setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
}
