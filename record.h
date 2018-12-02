#ifndef RECORD_H
#define RECORD_H
#include "accel.h"

class record
{
public:
    record(int r, int c, DIRECTION _dir);
    int row, col;
    DIRECTION dir;

};

#endif // RECORD_H
