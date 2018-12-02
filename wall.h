#ifndef WALL_H
#define WALL_H

#include <QWidget>
#include "block.h"

class Wall : public Block
{
public:
    Wall(int r, int c, QWidget* _parent = nullptr);
    virtual char getType() const override;
    virtual void setRow(int r) override;
    virtual void setCol(int c) override;

private:
    const string IMAGE_TYPE = "w";
};

#endif // WALL_H
