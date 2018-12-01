#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <QPushButton>
#include <QDebug>

using std::string;

class GameControl;
// Normal road block, allow passage, no special feature
class Block : public QPushButton
{
    Q_OBJECT

public:
    Block(int r, int c, QWidget* _parent = nullptr);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    virtual char getType() const =0; // virtual function
    virtual void set_image();
    static const int BLOCK_SIZE = 50; // Size of block is 20px

private:
    int row ;
    int col;

};

#endif // BLOCK_H
