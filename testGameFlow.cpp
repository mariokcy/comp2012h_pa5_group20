#include <iostream>
#include "test_Block_and_Player.cpp"
#include "Player.cpp"
#include "Direction.cpp"
using namespace std;
//wall road terminate up down left right
enum{W,R,T,A,B,C,D};
const int MAX_COL = 4;
const int MAX_ROW = 4;

char block[4][4] = {
{ R,W,W,R },
{ B,W,W,R },
{ T,W,W,R },
{ D,R,R,R }
};


void loadMap(Block* (*board)[MAX_ROW][MAX_COL]) {
	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
			switch (block[r][c])
			{
			case W:
				(*board)[r][c] = new Wall{ r,c };
				break;
			case R:
				(*board)[r][c] = new Road{ r,c };
				break;
			case T:
				(*board)[r][c] = new Terminate{ r,c };
				break;
			case A:
				(*board)[r][c] = new Accel{ r,c,DIRCTION::UP };
				break;
			case B:
				(*board)[r][c] = new Accel{ r,c,DIRCTION::DOWN };
				break;
			case C:
				(*board)[r][c] = new Accel{ r,c,DIRCTION::LEFT };
				break;
			case D:
				(*board)[r][c] = new Accel{ r,c,DIRCTION::RIGHT };
				break;
			default:
				break;
			}

		}
	}
}

void printMap(Block* (*board)[MAX_ROW][MAX_COL], Player player) {
	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
			if (player.getRow() == r && player.getCol() == c) {
				cout << '*';
			}
			else {
				switch ((*board)[r][c]->getType()) {
				case 'W': cout << 'X'; break;
				case 'R': cout << ' '; break;
				case 'T': cout << '@'; break;
				case 'A':
					Accel* temp = dynamic_cast<Accel*> ((*board)[r][c]);
					DIRCTION dir = temp->getDir();
					switch (dir) {
					case UP: cout << '^'; break;
					case DOWN: cout << 'v'; break;
					case LEFT: cout << '<'; break;
					case RIGHT: cout << '>'; break;
					}
					break;

				}
			}
		}
		cout << endl;
	}
}
int main()
{
	Player* player = new Player();
	Block* board[MAX_ROW][MAX_COL];
	
	loadMap(&board);

	printMap(&board, *player);

	do {
		char input;
		DIRCTION dir;
		if (!player->isAccel()) {
			cout << "enter dir (w: up/ s: down/ a: left/ d: right): " << endl;
			cin >> input;
			 dir = input == 'w' ? UP :
				input == 's' ? DOWN :
				input == 'a' ? LEFT : RIGHT;
			
		}

		else if (player->isAccel()) {
			dir = player->getDir();

		}
			   
	int r = player->getRow(); int c = player->getCol();
		switch (dir)
		{
			
		case UP:
			if (r > 0 && block[r - 1][c] != W) {
				player->setRow(r - 1);
				player->setDir(DIRCTION::UP);
			}
			else 
				player->setAccel(false);

			break;

		case DOWN:
			if (r < MAX_ROW - 1 && block[r + 1][c] != W) {
				player->setRow(r + 1);
				player->setDir(DIRCTION::DOWN);
			}
			else
				player->setAccel(false);

			break;
		case LEFT:
			if (c > 0 && block[r][c - 1] != W) {
				player->setCol(c - 1);
				player->setDir(DIRCTION::LEFT);
			}
			else
				player->setAccel(false);

			break;

		case RIGHT:
			if (c < MAX_COL - 1 && block[r][c + 1] != W) {
				player->setCol(c + 1);
				player->setDir(DIRCTION::RIGHT);
			}
			else
				player->setAccel(false);

			break;
		}





		//update dir and accel
		if (board[player->getRow()][player->getCol()]->getType() == 'A') {
			Accel* temp = dynamic_cast<Accel*> (board[player->getRow()][player->getCol()]);
			player->setDir(temp->getDir());
			player->setAccel(true);
		}else if (board[player->getRow()][player->getCol()]->getType() == 'T') {
			player->setAccel(false);
		}
		r = player->getRow(); c = player->getCol();
		switch (player->getDir())
		{
			
		case UP:
			if (r <= 0 || block[r - 1][c] == W) {
				player->setAccel(false);
			}
			break;

		case DOWN:
			if (r >= MAX_ROW - 1 || block[r + 1][c] == W) {
				player->setAccel(false);
			}
			break;
		case LEFT:
			if (c <= 0 || block[r][c - 1] == W) {
				player->setAccel(false);
			}
			break;

		case RIGHT:
			if (c >= MAX_COL - 1 || block[r][c + 1] == W) {
				player->setAccel(false);
			}
			break;
		}


		printMap(&board, *player);
	} while (!player->isEnd());
}
	
	//Block* a = new Road{ 0, 0 };
	/*int player[2] = { 0,0 };
	do {
		char dir;
		cout << "enter dir:" << endl;cout << "up: w" << endl;cout << "down: s" << endl;	cout << "left: a" << endl;	cout << "right: d" << endl;
		cin >> dir;
		switch (dir)
		{
		case 'w':
			if (player[0] > 0 && block[player[0] - 1][player[1]] == A) {
				player[0] = player[0] - 1;
			}
			break;
		case 's':
			if (player[0] < MAX_ROW - 1 && block[player[0] + 1][player[1]] == A) {
				player[0] = player[0] + 1;
			}
			break;
		case 'a':
			if (player[1] > 0 && block[player[0]][player[1] - 1] == A) {
				player[1] = player[1] - 1;
			}
			break;
		case 'd':
			if (player[1] < MAX_COL - 1 && block[player[0]][player[1] + 1] == A) {
				player[1] = player[1] + 1;
			}
			break;
		}
		for (int r = 0; r < MAX_ROW; r++) {
			for (int c = 0; c < MAX_COL; c++) {
				if (player[0] == r && player[1] == c)
					cout << '*';
				else
				{
					cout << block[r][c];
				}
			}
			cout << endl;
		}

	} while (player[0] != 0 || player[1] != 3);
	*/


