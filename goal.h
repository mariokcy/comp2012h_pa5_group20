#ifndef GOAL_H
#define GOAL_H

#include <QWidget>
#include "block.h"

class Block;

class Goal : public Block
{
public:
    Goal(int r, int c, QWidget* _parent);
    virtual char getType() const override;
    virtual void setRow(int r) override;
    virtual void setCol(int c) override;

private:
    const string IMAGE_TYPE = "g";

};

#endif // GOAL_H
