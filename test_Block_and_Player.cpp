enum DIRCTION{
	UP, DOWN, LEFT, RIGHT
};



class Block{
private:
	int row;
	int col;
public:
	Block(int r, int c) {
		row = r;
		col = c;

	}
	int getRow()const {
		return row;
	}
	int getCol()const {
		return col;
	}
/*	void setRow(int r){
		row = r;
	}
	void setCol(int c) {
		col = c;
	}
	*/
	virtual char getType()const = 0;
};

class Road: public Block {
private:
	char type = 'R';
public:

	Road(int r, int c) :Block(r, c) {};

	char getType()const {
		return type;
	}
};

class Wall: public Block {
private:
	char type = 'W';
public:

	Wall(int r, int c) :Block(r, c) {};

	char getType()const {
		return type;
	}
};
class Accel : public Block {
private:
	char type = 'A';
	DIRCTION dir;
public:

	Accel(int r, int c, DIRCTION dir) :Block(r, c), dir(dir) {};

	char getType()const {
		return type;
	}
	DIRCTION getDir()const {
		return dir;
	}
};
class Terminate : public Block {
private:
	char type = 'T';
public:

	Terminate(int r, int c) :Block(r, c) {};

	char getType()const {
		return type;
	}
};


class Player {
private:
	int row = 0;
	int col = 0;

	bool Accel = false;
	DIRCTION dir = DOWN;
public:
	Player() = default;
	Player(int r, int c, DIRCTION dir) {
		this->dir = dir;
		row = r;
		col = c;

	}
	//getter
	int getRow()const {
		return row;
	}
	int getCol()const {
		return col;
	}
	DIRCTION getDir()const {
		return dir;
	}
	bool isAccel() {
		return Accel;
	}
	//setter
	void setDir(DIRCTION input) {
		this->dir = input;
	}
	void setAccel(bool on) {
		Accel = on;
	}
	void setRow(int r) {
		row = r;
	}
	void setCol(int c) {
		col = c;
	}
	bool isEnd() {
		return (col == 3 && row == 0);
	}
};