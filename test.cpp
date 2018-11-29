#include <iostream>
#include "Source.cpp"
using namespace std;

enum{W,R,T,A,B};
const int MAX_COL = 4;
const int MAX_ROW = 4;

char block[4][4] = {
{ R,W,W,R },
{ A,W,W,R },
{ T,W,W,R },
{ B,R,R,R }
};
int main()
{
	Block* board[MAX_ROW][MAX_COL];
	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
			switch (block[r][c])
			{
			case W:
				board[r][c] = new Wall{ r,c };
				break;
			case R:
				board[r][c] = new Road{ r,c };
				break;
			case A:
				board[r][c] = new Accel{ r,c,1 };
				break;
			case B:
				board[r][c] = new Accel{ r,c,2 };
				break;
			case T:
				board[r][c] = new Terminate{ r,c };
				break;
			default:
				break;
			}
			
		}
	}
	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
				cout << board[r][c]->getType();
		}
		cout << endl;
	}

	int player[3] = { 0,0,0 };
	do {
		char dir;
		if (player[2] == 0) {
			cout << "enter dir:" << endl; cout << "up: w" << endl; cout << "down: s" << endl;	cout << "left: a" << endl;	cout << "right: d" << endl;
			cin >> dir;
			switch (dir)
			{
			case 'w':
				if (player[0] > 0 && block[player[0] - 1][player[1]] != W) {
					player[0] = player[0] - 1;

				}
				break;
			case 's':
				if (player[0] < MAX_ROW - 1 && block[player[0] + 1][player[1]] != W) {
					player[0] = player[0] + 1;
				}
				break;
			case 'a':
				if (player[1] > 0 && block[player[0]][player[1] - 1] != W) {
					player[1] = player[1] - 1;
				}
				break;
			case 'd':
				if (player[1] < MAX_COL - 1 && block[player[0]][player[1] + 1] != W) {
					player[1] = player[1] + 1;
				}
				break;
			}
		}
		if (board[player[0]][player[1]]->getType() == 'A') {
			Accel* temp=dynamic_cast<Accel*> (board[player[0]][player[1]]);
			player[2]=temp->getType();
			
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
		}
		else {
			if (player[2] == 1) {
				if (player[0] = MAX_ROW - 1 || block[player[0] + 1][player[1]] == W|| block[player[0]][player[1]] == T) {
					player[2] = 0;
				}
				else {
					player[0] = player[0] + 1;
				}
			}
			if (player[2] == 2) {
				if (player[0] = MAX_ROW - 1 || block[player[0] + 1][player[1]] == W || block[player[0]][player[1]] == T) {
					player[2] = 0;
				}
				else {
					player[0] = player[0] + 1;
				}
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
		}
	} while (player[0] != 0 || player[1] != 3);
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


