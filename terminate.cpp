#include "terminate.h"

Terminate::Terminate(int r, int c, QWidget* _parent) :
    Block(r, c, _parent)
{

}

char Terminate::getType() const {
    return IMAGE_TYPE.front();
}

void Terminate::set_image() {
    string str = "";
    str.push_back(getType());
    setStyleSheet(QString::fromStdString("border-image: url(\":/resources/map_v2_" + str + ".png\");"));
}
