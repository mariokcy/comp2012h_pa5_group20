#include "direction.h"

class Player {

private:
    int row = 0;
    int col = 0;

    static const int GOAL_X = 19;
    static const int GOAL_Y = 19;
    bool Accel = false;
    DIRECTION dir = DOWN;

public:
    // player start at (0,0)
    // Player() = default;
     // player start at (r,c)
    // if no parameter, default start at (0,0)
    Player(int r = 0, int c = 0, DIRECTION dir = DOWN);

    //getter
    int getRow() const;
    int getCol() const;
    DIRECTION getDir() const;
    bool isAccel() const;

    //setter
    void setDir(DIRECTION input);
    void setAccel(bool on);
    void setRow(int r);
    void setCol(int c);
};
