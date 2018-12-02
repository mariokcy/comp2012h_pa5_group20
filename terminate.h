#ifndef TERMINATE_H
#define TERMINATE_H

#include <QWidget>
#include "block.h"

class Terminate : public Block
{
public:
    Terminate(int r, int c, QWidget* _parent = nullptr);
    virtual char getType() const override;
    virtual void setRow(int r) override;
    virtual void setCol(int c) override;

private:
    const string IMAGE_TYPE = "t";
};

#endif // TERMINATE_H
