#include <iostream>
#include "test_Block_and_Player.cpp"
#include "Player.cpp"
#include "Direction.cpp"
#include<vector>
#include<queue>
#include<deque>
using namespace std;
//wall road terminate up down left right
enum{W,R,T,A,B,C,D};
const int MAX_COL = 20;
const int MAX_ROW = 20;

int udlr[4][2] = { { -1,0 }, { 1,0 }, { 0,-1 }, { 0,1 } };
/*int map[4][4]={
{R,W,R,R},
{R,D,R,R},
{R,R,W,R},
{D,R,R,R}
};
*/

int map[20][20] = {
{W,R,R,R,W,R,R,R,R,R,R,T,R,R,R,R,R,R,R,C},
{W,R,R,R,W,R,R,R,R,R,R,D,R,R,R,R,R,T,B,T},
{W,R,R,R,W,W,W,R,W,W,R,W,W,W,W,W,W,W,R,R},
{W,R,R,R,W,W,W,R,W,W,R,W,W,W,W,W,W,W,R,R},
{W,R,R,R,R,R,R,R,W,R,R,W,R,R,R,R,R,W,R,R},
{W,R,R,R,R,R,R,W,W,W,R,R,R,R,R,R,R,W,R,R},
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,R,R,W,R,R},
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,R,R,W,R,R},
{R,R,R,R,B,W,R,W,R,R,R,R,R,R,R,R,R,W,R,R},
{T,R,R,W,R,W,R,W,R,R,R,R,R,R,W,W,R,W,R,R},
{R,R,W,W,R,W,R,W,R,R,R,R,R,R,W,W,R,W,R,R},
{R,T,W,W,R,W,R,W,R,R,R,R,R,R,R,W,B,W,R,R},
{R,R,W,W,R,R,R,W,R,R,R,W,R,R,R,W,R,W,T,A},
{R,R,W,W,R,W,W,W,W,W,W,W,W,W,R,R,T,R,R,R},
{R,R,W,W,R,W,W,W,W,W,W,W,W,W,R,R,R,R,R,R},
{R,R,W,W,T,D,R,R,R,R,R,R,R,T,R,R,R,R,R,R},
{R,R,W,W,D,R,R,R,R,R,R,R,R,T,R,R,R,R,R,R},
{A,A,W,W,W,W,W,W,W,W,W,W,W,W,R,R,R,R,R,R},
{R,R,W,R,R,T,R,R,R,R,R,R,R,C,R,R,R,R,R,R},
{R,T,R,R,R,R,R,R,R,R,R,R,R,C,R,R,R,R,R,R}
};



void loadMap(Block* (*board)[MAX_ROW][MAX_COL]) {
	

	
	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
			switch (map[r][c])
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
				(*board)[r][c] = new Accel{ r,c,DIRECTION::UP };
				break;
			case B:
				(*board)[r][c] = new Accel{ r,c,DIRECTION::DOWN };
				break;
			case C:
				(*board)[r][c] = new Accel{ r,c,DIRECTION::LEFT };
				break;
			case D:
				(*board)[r][c] = new Accel{ r,c,DIRECTION::RIGHT };
				break;
			default:
				break;
			}

		}
	}
}

void printMap(Block* (*board)[MAX_ROW][MAX_COL], Player player) {
	cout << "----------------------------" << endl;
	for (int r = 0; r < MAX_ROW; r++) {
		cout << '|';
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
					DIRECTION dir = temp->getDir();
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
		cout << '|';
		cout << endl;
	
	}
	cout << "--------------------------" << endl;
}
bool findPath(int curRow, int curCol, int endRow, int endCol, deque<vector<int>> &sol, Block* (*board)[MAX_ROW][MAX_COL]) {
	/*	//out of bound
		if (curRow > MAX_ROW - 1 || curRow<0 || curCol>MAX_COL - 1 || curCol < 0)return sol;
		//end
		if (curRow==endR&&curCol==endC)return sol;

		deque<vector<int>> a1,a2,a3,a4;

		a1.assign(sol.begin(), sol.end());
		a2.assign(sol.begin(), sol.end());
		a3.assign(sol.begin(), sol.end());
		a4.assign(sol.begin(), sol.end());
		for (int i = 0; i < 4; i++) {

			DIRECTION dir = i == 0 ? UP :
				i == 1 ? DOWN :
				i == 2 ? LEFT : RIGHT;
			Player temp{ curRow,curCol,dir };

			do {

				if (temp.isAccel()) {
					dir = temp.getDir();

				}

				int r = temp.getRow(); int c = temp.getCol();
				switch (dir)
				{

				case UP:
					if (r > 0 && map[r - 1][c] != W) {
						temp.setRow(r - 1);
						temp.setDir(UP);
					}
					else
						temp.setAccel(false);

					break;

				case DOWN:
					if (r < MAX_ROW - 1 && map[r + 1][c] != W) {
						temp.setRow(r + 1);
						temp.setDir(DOWN);
					}
					else
						temp.setAccel(false);

					break;
				case LEFT:
					if (c > 0 && map[r][c - 1] != W) {
						temp.setCol(c - 1);
						temp.setDir(LEFT);
					}
					else
						temp.setAccel(false);

					break;

				case RIGHT:
					if (c < MAX_COL - 1 && map[r][c + 1] != W) {
						temp.setCol(c + 1);
						temp.setDir(DIRECTION::RIGHT);
					}
					else
						temp.setAccel(false);

					break;
				}





				//update dir and accel
				if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'A') {
					Accel* tempAccel = dynamic_cast<Accel*> ((*board)[temp.getRow()][temp.getCol()]);
					temp.setDir(tempAccel->getDir());
					temp.setAccel(true);
				}
				else if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'T') {
					temp.setAccel(false);
				}

				//set Accel false if have wall
				r = temp.getRow(); c = temp.getCol();
				switch (temp.getDir())
				{

				case UP:
					if (r <= 0 || map[r - 1][c] == W) {
						temp.setAccel(false);
					}
					break;

				case DOWN:
					if (r >= MAX_ROW - 1 || map[r + 1][c] == W) {
						temp.setAccel(false);
					}
					break;
				case LEFT:
					if (c <= 0 || map[r][c - 1] == W) {
						temp.setAccel(false);
					}
					break;

				case RIGHT:
					if (c >= MAX_COL - 1 || map[r][c + 1] == W) {
						temp.setAccel(false);
					}
					break;
				}

				//end when player need input
			} while (temp.isAccel());


			deque<vector<int>>::iterator b = sol.begin();
			bool find = false;
			for (; b != sol.end(); b++) {
				if ((*b)[0] == temp.getRow() && (*b)[1] == temp.getCol()) {
					cout << (*b)[0] << ',' << (*b)[1] << endl;
					find = true;
					break;
				}
			}
			if (!find && !(curRow == temp.getRow() && curCol == temp.getCol())) {
				vector<int> new_coor;
				new_coor.push_back(temp.getRow());
				new_coor.push_back(temp.getCol());
				i == 0 ? a1.push_back(new_coor) :
					i == 1 ? a2.push_back(new_coor) :
					i == 2 ? a3.push_back(new_coor) :
					a4.push_back(new_coor);
			}



		}
		bool result[4] = { false, false, false, false };
		deque<vector<int>> possibleSolution[4];
		if (a1.size() == sol.size() + 1) {
			possibleSolution[0] = findPath(curRow - 1, curCol, endR, endC, a1, board);
			result[0] = true;
		}
		if (a2.size() == sol.size() + 1) {
			possibleSolution[1] = findPath(curRow +1, curCol, endR, endC, a2, board);
			result[1] = true;
		}
		if (a3.size() == sol.size() + 1) {
			possibleSolution[2] = findPath(curRow, curCol-1, endR, endC, a3, board);
			result[2]=true;
		}
		if (a4.size() == sol.size() + 1) {
			possibleSolution[3]= findPath(curRow , curCol+1, endR, endC, a4, board);
			result[3] = true;
		}
		int min=-1;
		if (!(result[0] || result[1] || result[2] || result[3])) return sol;
		for (int i = 0; i < 4; i++) {
			if (result[i] == false) continue;
			if (result[i] == true) {
				if (min == -1) {
					min = i;
				}
				else if(possibleSolution[min].size() > possibleSolution[i].size()){
					min = i;
				}
			}
		}
		return possibleSolution[min];
		*/

		//check end
	if (curRow == endRow && curCol == endCol) {

		return true;
	}
	vector<int> move[4];
	//update next move
	for (int i = 0; i < 4; i++) {

		DIRECTION dir = i == 0 ? UP :
			i == 1 ? DOWN :
			i == 2 ? LEFT : RIGHT;
		Player temp{ curRow,curCol,dir };

		do {

			if (temp.isAccel()) {
				dir = temp.getDir();

			}

			int r = temp.getRow(); int c = temp.getCol();
			switch (dir)
			{

			case UP:
				if (r > 0 && map[r - 1][c] != W) {
					temp.setRow(r - 1);
					temp.setDir(UP);
				}
				else
					temp.setAccel(false);

				break;

			case DOWN:
				if (r < MAX_ROW - 1 && map[r + 1][c] != W) {
					temp.setRow(r + 1);
					temp.setDir(DOWN);
				}
				else
					temp.setAccel(false);

				break;
			case LEFT:
				if (c > 0 && map[r][c - 1] != W) {
					temp.setCol(c - 1);
					temp.setDir(LEFT);
				}
				else
					temp.setAccel(false);

				break;

			case RIGHT:
				if (c < MAX_COL - 1 && map[r][c + 1] != W) {
					temp.setCol(c + 1);
					temp.setDir(DIRECTION::RIGHT);
				}
				else
					temp.setAccel(false);

				break;
			}





			//update dir and accel
			if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'A') {
				Accel* tempAccel = dynamic_cast<Accel*> ((*board)[temp.getRow()][temp.getCol()]);
				temp.setDir(tempAccel->getDir());
				temp.setAccel(true);
			}
			else if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'T') {
				temp.setAccel(false);
			}

			//set Accel false if have wall
			r = temp.getRow(); c = temp.getCol();
			switch (temp.getDir())
			{

			case UP:
				if (r <= 0 || map[r - 1][c] == W) {
					temp.setAccel(false);
				}
				break;

			case DOWN:
				if (r >= MAX_ROW - 1 || map[r + 1][c] == W) {
					temp.setAccel(false);
				}
				break;
			case LEFT:
				if (c <= 0 || map[r][c - 1] == W) {
					temp.setAccel(false);
				}
				break;

			case RIGHT:
				if (c >= MAX_COL - 1 || map[r][c + 1] == W) {
					temp.setAccel(false);
				}
				break;
			}

			//end when player need input 
		} while (temp.isAccel());
		move[i].push_back(temp.getRow());
		move[i].push_back(temp.getCol());
	}
	
	//check repeat
	for (int i = 0; i < 4; i++) {
		bool find = false;
		for (deque<vector<int>>::iterator b = sol.begin(); b != sol.end(); b++) {
	
			if ((*b)[0] == move[i][0] && (*b)[1] == move[i][1]) {
			
				find = true;
				break;
			}
		}

		if (!find) {
			vector<int> new_coor;
			sol.push_back(move[i]);
		if (findPath(move[i][0], move[i][1], endRow, endCol, sol, board)) {
			return true;
		}
		else
		{
			sol.pop_back();
		}
		}
		
	}
	return false;
}
int main()
{
	Player* player = new Player(19,19,DOWN);
	Block* board[MAX_ROW][MAX_COL];

	loadMap(&board);

	printMap(&board, *player);
	//store shortest path;
	deque<vector<int>> stp;
	do {
		char input;
		DIRECTION dir;
		if (!player->isAccel()) {
			cout << "enter dir (w: up/ s: down/ a: left/ d: right): " << endl;
			cin >> input;
			if (input == 'r') {
				vector<int>coor{ player->getRow(), player->getCol() };
				stp.push_back(coor);
				bool sol=findPath(player->getRow(), player->getCol(), 1, 1, stp, &board);
				break;
			}
			else {
				dir = input == 'w' ? UP :
					input == 's' ? DOWN :
					input == 'a' ? LEFT : RIGHT;

			}

		}

		else if (player->isAccel()) {
			dir = player->getDir();

		}

		int r = player->getRow(); int c = player->getCol();
		switch (dir)
		{

		case UP:
			if (r > 0 && map[r - 1][c] != W) {
				player->setRow(r - 1);
				player->setDir(DIRECTION::UP);
			}
			else
				player->setAccel(false);

			break;

		case DOWN:
			if (r < MAX_ROW - 1 && map[r + 1][c] != W) {
				player->setRow(r + 1);
				player->setDir(DIRECTION::DOWN);
			}
			else
				player->setAccel(false);

			break;
		case LEFT:
			if (c > 0 && map[r][c - 1] != W) {
				player->setCol(c - 1);
				player->setDir(DIRECTION::LEFT);
			}
			else
				player->setAccel(false);

			break;

		case RIGHT:
			if (c < MAX_COL - 1 && map[r][c + 1] != W) {
				player->setCol(c + 1);
				player->setDir(DIRECTION::RIGHT);
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
		}
		else if (board[player->getRow()][player->getCol()]->getType() == 'T') {
			player->setAccel(false);
		}
		r = player->getRow(); c = player->getCol();
		switch (player->getDir())
		{

		case UP:
			if (r <= 0 || map[r - 1][c] == W) {
				player->setAccel(false);
			}
			break;

		case DOWN:
			if (r >= MAX_ROW - 1 || map[r + 1][c] == W) {
				player->setAccel(false);
			}
			break;
		case LEFT:
			if (c <= 0 || map[r][c - 1] == W) {
				player->setAccel(false);
			}
			break;

		case RIGHT:
			if (c >= MAX_COL - 1 || map[r][c + 1] == W) {
				player->setAccel(false);
			}
			break;
		}


		printMap(&board, *player);
	} while (!player->isEnd());

	for (int i = 0; i < stp.size() - 1; i++) {
		player->setRow(stp[i][0]);
		player->setCol(stp[i][1]);
		printMap(&board, *player);


	}

}
