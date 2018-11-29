#include "accel.h"

Accel::Accel(int r, int c,DIRECTION _dir, QWidget* _parent) :
    Block(r, c, _parent),
    dir(_dir)
{

}

char Accel::getType() const {
    return IMAGE_TYPE.front();
}

Accel::DIRECTION Accel::getDir() const {
    return dir;
}

void Accel::set_image() {
    string str = "";
    str.push_back(getType());
    setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
}
