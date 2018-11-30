#ifndef ACCEL_H
#define ACCEL_H

#include <QWidget>
#include "block.h"

class Accel : public Block
{
public:
    enum DIRECTION{ UP, DOWN, LEFT, RIGHT };
    Accel(int r, int c, DIRECTION dir, QWidget* _parent);
    virtual char getType() const override;
    virtual void set_image(Player player) override;
    Accel::DIRECTION getDir() const;

private:
    DIRECTION dir;
    const string IMAGE_TYPE = "a";
};

#endif // ACCEL_H
