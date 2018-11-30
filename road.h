#ifndef ROAD_H
#define ROAD_H

#include <QWidget>
#include "block.h"

class Road : public Block
{
private:
    const string IMAGE_TYPE = "r";

public:
    Road(int r, int c, QWidget* _parent);
    virtual char getType() const override;

};

#endif // ROAD_H
