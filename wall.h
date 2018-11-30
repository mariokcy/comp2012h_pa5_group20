#ifndef WALL_H
#define WALL_H

#include <QWidget>
#include "block.h"

class Wall : public Block
{
private:
    const string IMAGE_TYPE = "w";

public:
    Wall(int r, int c, QWidget* _parent = nullptr);
    virtual char getType() const override;

};

#endif // WALL_H
