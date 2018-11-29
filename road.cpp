#include "road.h"

Road::Road(int r, int c, QWidget* _parent) :
    Block(r, c, _parent)
{

}

char Road::getType() const {
    return IMAGE_TYPE.front();
}

void Road::set_image() {
    string str = "";
    str.push_back(getType());
    setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
}
