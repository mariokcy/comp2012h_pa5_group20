#include "direction.h"

class Player {

private:
    int row = 0;
    int col = 0;

    bool Accel = false;
    DIRECTION dir = DOWN;

public:
    Player() = default;
    Player(int r, int c, DIRECTION dir = DOWN);
    //getter
    int getRow() const;
    int getCol() const;
    DIRECTION getDir() const;
    bool isAccel();
    //setter
    void setDir(DIRECTION input);
    void setAccel(bool on);
    void setRow(int r);
    void setCol(int c);
    bool isEnd();
};
