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
	void setRow(int r){
		row = r;
	}
	void setCol(int c) {
		col = c;
	}
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
	int oriantation;
public:

	Accel(int r, int c, int o) :Block(r, c), oriantation(o) {};

	char getType()const {
		return type;
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