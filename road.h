#ifndef ROAD_H
#define ROAD_H

#include <QWidget>
#include "block.h"

// Normal road block, allow passage, no special feature
class Road : public Block
{
public:
    Road(int r, int c, QWidget* _parent);
    virtual char getType() const override;
    virtual void setRow(int r) override;
    virtual void setCol(int c) override;

private:
    const string IMAGE_TYPE = "r";

};

#endif // ROAD_H
