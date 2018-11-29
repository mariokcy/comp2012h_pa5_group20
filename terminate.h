#ifndef TERMINATE_H
#define TERMINATE_H

#include <QWidget>
#include "block.h"

class Terminate : public Block
{
private:
    const string IMAGE_TYPE = "t";

public:
    Terminate(int r, int c, QWidget* _parent = nullptr);
    virtual char getType() const override;
    virtual void set_image() override;
};

#endif // TERMINATE_H
