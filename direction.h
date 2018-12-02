#ifndef DIRECTION_H
#define DIRECTION_H
enum DIRECTION{ UP, DOWN, LEFT, RIGHT };
// Below arrays details all 4 possible movements from a cell
const int row[4] = { -1, 1, 0, 0 };
const int col[4] = { 0, 0, -1, 1 };
#endif // DIRECTION_H
