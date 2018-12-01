#include <iostream>
#include "test_Block_and_Player.cpp"
#include "Player.cpp"
#include "Direction.cpp"
#include<vector>
#include<queue>
#include<deque>
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include<list>
#include<stack>
// M x N matrix
#define M 10
#define N 10


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
};*/


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


// queue node used in BFS
struct Node
{
	// (x, y) represents matrix cell coordinates
	// dist represent its minimum distance from the source
	int x, y, dist;
};

// Below arrays details all 4 possible movements from a cell
int row[] = { -1, 1, 0, 0 };
int col[] = { 0, 0, -1, 1 };

// Function to check if it is possible to go to position (row, col)
// from current position. The function returns false if (row, col)
// is not a valid position or has value 0 or it is already visited
bool isValid(Block* (*board)[MAX_ROW][MAX_COL], bool visited[][MAX_COL], int row, int col)
{
	return (row >= 0) && (row < MAX_ROW) && (col >= 0) && (col < MAX_COL)
		&& !((*board)[row][col]->getType()=='W') && !visited[row][col];
}

vector<int> checkEndPoint(Block* (*board)[MAX_ROW][MAX_COL], int curRow, int curCol, DIRECTION dir) {
	
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

	vector<int> end;
	end.push_back(temp.getRow());
	end.push_back(temp.getCol());
	return end;
};
vector<int> checkEndPoint(Block* (*board)[MAX_ROW][MAX_COL], int curRow, int curCol) {
	if ((*board)[curRow][curCol]->getType() == 'A') {
		Accel* tempAccel = dynamic_cast<Accel*> ((*board)[curRow][curCol]);
		Player temp{ curRow,curCol,tempAccel->getDir() };
		temp.setAccel(true);
	
		do {

			int r = temp.getRow(); int c = temp.getCol();
			switch (temp.getDir())
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
	
		vector<int> end;
		end.push_back(temp.getRow());
		end.push_back(temp.getCol());
		return end;
	}
	else
	{
		vector<int> end;
		end.push_back(curRow);
		end.push_back(curCol);
		return end;
	}
}


//choice{originalRow, originalCol, movedRow, movedCol, terminateRow, terminateCol, distanceFromStart}
//stp: store moved coordinate
bool findStp(vector<vector<int>> choice,int n, int endRow, int endCol ,stack<vector<int>> &stp, Block* (*board)[MAX_ROW][MAX_COL]) {
	if (n == 0) {
		return true;
	}
	for (int i = choice.size() - 1; i >= 0; i--) {
		vector<int> end = checkEndPoint(board, choice[i][2], choice[i][3]);
		if (end[0]== endRow && end[1] == endCol) {
			stp.push(choice[i]);
			if (findStp(choice, n - 1, choice[i][0], choice[i][1], stp, board) ){
				return true;
			}
			else {
				stp.pop();
			}
		}
		if (choice[i][6] == n - 1) {
			return false;
		}
	}
	return false;
}
	




// Find Shortest Possible Route in a matrix mat from source
// cell (i, j) to destination cell (x, y)
void BFS(Block* (*board)[MAX_ROW][MAX_COL], int i, int j, int x, int y)
{
	//store the possible route for find stp
	vector<vector<int>> choice;
	choice.push_back(vector<int>{ i, j, i, j, i, j, 0 });


	// construct a matrix to keep track of visited cells
	bool visited[MAX_ROW][MAX_COL];

	// initially all cells are unvisited
	memset(visited, false, sizeof visited);

	// create an empty queue
	queue<Node> q;

	// mark source cell as visited and enqueue the source node
	visited[i][j] = true;
	q.push({ i, j, 0 });


	
	
	// stores length of longest path from source to destination
	int min_dist = INT_MAX;

	// run till queue is not empty	
	while (!q.empty())
	{
		// pop front node from queue and process it
		Node node = q.front();
		q.pop();
		// (i, j) represents current cell and dist stores its
		// minimum distance from the source
		int i = node.x, j = node.y, dist = node.dist;
		//a.push_back(vector<int>{i, j });

				// if destination is found, update min_dist and stop
		if (i == x && j == y)
		{
			min_dist = dist;
			break;
		}

		// check for all 4 possible movements from current cell
		// and enqueue each valid movement
		for (int k = 0; k < 4; k++)
		{
			// check if it is possible to go to position
			// (i + row[k], j + col[k]) from current position

			vector<int> endPoint = checkEndPoint(board, i, j, (DIRECTION)k);
			if (isValid(board, visited, i + row[k], j + col[k]) && isValid(board, visited, endPoint[0], endPoint[1]))
			{
				// mark next cell as visited and enqueue it
				visited[i + row[k]][j + col[k]] = true;
				visited[endPoint[0]][endPoint[1]] = true;
				q.push({ endPoint[0], endPoint[1], dist + 1 });

				choice.push_back(vector<int>{ i, j, i + row[k], j + col[k], endPoint[0], endPoint[1], dist + 1 });
			}
		}
	}

		if (min_dist != INT_MAX)
			cout << "The shortest path from source to destination "
			"has length " << min_dist << endl;
		else
			cout << "Destination can't be reached from given source" << endl;



	stack<vector<int>> stp;
	findStp(choice, min_dist, x, y, stp, board);
	for (int i = 0; i < min_dist; i++) {

		cout << stp.top()[2] << ',' << stp.top()[3] << endl;
		stp.pop();
	}

}





int main()
{
	Player* player = new Player(19,19,DOWN);
	Block* board[MAX_ROW][MAX_COL];

	loadMap(&board);

	printMap(&board, *player);

	do {
		char input;
		DIRECTION dir;
		if (!player->isAccel()) {
	
			cout << "enter dir (w: up/ s: down/ a: left/ d: right): " << endl;
			cin >> input;
			if (input == 'f') {
			BFS(&board, player->getRow(), player->getCol(), 1, 1);
			continue;
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
	} while (!(player->isEnd()));

	

}
