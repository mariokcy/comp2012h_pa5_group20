#include "player.h"

Player::Player(int r, int c, DIRECTION dir) {
    this->dir = dir;
    row = r;
    col = c;

}

//getter
int Player::getRow()const {
    return row;
}
int Player::getCol()const {
    return col;
}
DIRECTION Player::getDir()const {
    return dir;
}
bool Player::isAccel()const {
    return Accel;
}
//setter
void Player::setDir(DIRECTION input) {
    this->dir = input;
}
void Player::setAccel(bool on) {
    Accel = on;
}
void Player::setRow(int r) {
    row = r;
}
void Player::setCol(int c) {
    col = c;
}
bool Player::isEnd() {
    return (col == 3 && row == 0);
}
