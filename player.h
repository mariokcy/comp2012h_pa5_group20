#include "accel.h"

class Player {

private:
    int row = 0;
    int col = 0;

    bool Accel = false;
    Accel::DIRECTION dir = Accel::DOWN;

public:
    Player() = default;
    Player(int r, int c, Accel::DIRECTION dir = Accel::DOWN);
    //getter
    int getRow() const;
    int getCol() const;
    Accel::DIRECTION getDir() const;
    bool isAccel();
    //setter
    void setDir(Accel::DIRECTION input);
    void setAccel(bool on);
    void setRow(int r);
    void setCol(int c);
    bool isEnd();
};
