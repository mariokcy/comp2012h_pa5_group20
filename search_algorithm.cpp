

#include "search_algorithm.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "accel.h"

Search_algorithm::Search_algorithm(GameControl* game) :
    game(game)
{    
}



// Function to check if it is possible to go to position (row, col)
// from current position. The function returns false if (row, col)
// is not a valid position or has value 0 or it is already visited
bool Search_algorithm::isValid(std::vector<std::vector<Block*>> *board, bool visited[MAX_ROW][MAX_COL], int row, int col)
{
    return (row >= 0) && (row < MAX_ROW) && (col >= 0) && (col < MAX_COL)
        && !((*board)[row][col]->getType()=='W') && !visited[row][col];
}

std::vector<int> Search_algorithm::checkEndPoint(std::vector<std::vector<Block*>> *board, int curRow, int curCol, DIRECTION dir)
{
    Player temp{ curRow,curCol,dir };
    do {

        if (temp.isAccel()) {
            dir = temp.getDir();

        }

        int r = temp.getRow(); int c = temp.getCol();
        switch (dir) {
        case UP:
            if (r > 0 && (*board)[r - 1][c]->getType() != 'w') {
                temp.setRow(r - 1);
                temp.setDir(UP);
            }
            else
                temp.setAccel(false);

            break;

        case DOWN:
            if (r < MAX_ROW - 1 && (*board)[r + 1][c]->getType() != 'w') {
                temp.setRow(r + 1);
                temp.setDir(DOWN);
            }
            else
                temp.setAccel(false);

            break;
        case LEFT:
            if (c > 0 && (*board)[r][c - 1]->getType() != 'w') {
                temp.setCol(c - 1);
                temp.setDir(LEFT);
            }
            else
                temp.setAccel(false);

            break;

        case RIGHT:
            if (c < MAX_COL - 1 && (*board)[r][c + 1]->getType() != 'w') {
                temp.setCol(c + 1);
                temp.setDir(DIRECTION::RIGHT);
            }
            else
                temp.setAccel(false);

            break;
        }

        //update dir and accel
        if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'a') {
            Accel* tempAccel = dynamic_cast<Accel*> ((*board)[temp.getRow()][temp.getCol()]);
            temp.setDir(tempAccel->getDir());
            temp.setAccel(true);
        }
        else if ((*board)[temp.getRow()][temp.getCol()]->getType() == 't') {
            temp.setAccel(false);
        }

        //set Accel false if have wall
        r = temp.getRow(); c = temp.getCol();
        switch (temp.getDir()) {
        case UP:
            if (r <= 0 || (*board)[r - 1][c]->getType() == 'w') {
                temp.setAccel(false);
            }
            break;

        case DOWN:
            if (r >= MAX_ROW - 1 || (*board)[r + 1][c]->getType() == 'w') {
                temp.setAccel(false);
            }
            break;
        case LEFT:
            if (c <= 0 || (*board)[r][c - 1]->getType() == 'w') {
                temp.setAccel(false);
            }
            break;
        case RIGHT:
            if (c >= MAX_COL - 1 || (*board)[r][c + 1]->getType() == 'w') {
                temp.setAccel(false);
            }
            break;
        }
        //end when player need input
    } while (temp.isAccel());

    std::vector<int> end;
    end.push_back(temp.getRow());
    end.push_back(temp.getCol());
    return end;
};

std::vector<int> Search_algorithm::checkEndPoint(std::vector<std::vector<Block*>> *board, int curRow, int curCol)
{
    if ((*board)[curRow][curCol]->getType() == 'a') {
        Accel* tempAccel = dynamic_cast<Accel*> ((*board)[curRow][curCol]);
        Player temp{ curRow,curCol,tempAccel->getDir() };
        temp.setAccel(true);

        do {
            int r = temp.getRow(); int c = temp.getCol();
            switch (temp.getDir())
            {
            case UP:
                if (r > 0 && (*board)[r - 1][c]->getType() != 'w') {
                    temp.setRow(r - 1);
                    temp.setDir(UP);
                }
                else
                    temp.setAccel(false);
                break;

            case DOWN:
                if (r < MAX_ROW - 1 && (*board)[r + 1][c]->getType() != 'w') {
                    temp.setRow(r + 1);
                    temp.setDir(DOWN);
                }
                else
                    temp.setAccel(false);

                break;
            case LEFT:
                if (c > 0 && (*board)[r][c - 1]->getType() != 'w') {
                    temp.setCol(c - 1);
                    temp.setDir(LEFT);
                }
                else
                    temp.setAccel(false);

                break;

            case RIGHT:
                if (c < MAX_COL - 1 && (*board)[r][c + 1]->getType() != 'w') {
                    temp.setCol(c + 1);
                    temp.setDir(DIRECTION::RIGHT);
                }
                else
                    temp.setAccel(false);

                break;
            }

            //update dir and accel
            if ((*board)[temp.getRow()][temp.getCol()]->getType() == 'a') {
                Accel* tempAccel = dynamic_cast<Accel*> ((*board)[temp.getRow()][temp.getCol()]);
                temp.setDir(tempAccel->getDir());
                temp.setAccel(true);
            }
            else if ((*board)[temp.getRow()][temp.getCol()]->getType() == 't') {
                temp.setAccel(false);
            }

            //set Accel false if have wall
            r = temp.getRow(); c = temp.getCol();
            switch (temp.getDir())
            {

            case UP:
                if (r <= 0 || (*board)[r - 1][c]->getType() == 'w') {
                    temp.setAccel(false);
                }
                break;

            case DOWN:
                if (r >= MAX_ROW - 1 || (*board)[r + 1][c]->getType() == 'w') {
                    temp.setAccel(false);
                }
                break;
            case LEFT:
                if (c <= 0 || (*board)[r][c - 1]->getType() == 'w') {
                    temp.setAccel(false);
                }
                break;

            case RIGHT:
                if (c >= MAX_COL - 1 || (*board)[r][c + 1]->getType() == 'w') {
                    temp.setAccel(false);
                }
                break;
            }

            //end when player need input
        } while (temp.isAccel());

        std::vector<int> end;
        end.push_back(temp.getRow());
        end.push_back(temp.getCol());
        return end;
    } else {
        std::vector<int> end;
        end.push_back(curRow);
        end.push_back(curCol);
        return end;
    }
}


//choice{originalRow, originalCol, movedRow, movedCol, terminateRow, terminateCol, distanceFromStart}
//stp: store moved coordinate
bool Search_algorithm::findStp(std::vector<std::vector<int>> choice,int n, int endRow, int endCol ,std::stack<std::vector<int>> &stp, std::vector<std::vector<Block*>>* board)
{
    if (n == 0) {
        return true;
    }
    for (int i = choice.size() - 1; i >= 0; i--) {
        std::vector<int> end = checkEndPoint(board, choice[i][2], choice[i][3]);
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
void Search_algorithm::BFS(std::vector<std::vector<Block*>> *board, int i, int j, int x, int y)
{
    //store the possible route for find stp
    std::vector<std::vector<int>> choice;
    choice.push_back(std::vector<int>{ i, j, i, j, i, j, 0 });


    // construct a matrix to keep track of visited cells
    bool visited[MAX_ROW][MAX_COL];

    // initially all cells are unvisited
    memset(visited, false, sizeof visited);

    // create an empty queue
    std::queue<Node> q;

    // mark source cell as visited and enqueue the source node
    visited[i][j] = true;
    q.push({ i, j, 0 });

    // stores length of longest path from source to destination
    int min_dist = INT_MAX;

    // run till queue is not empty
    while (!q.empty()) {
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
            std::vector<int> endPoint = checkEndPoint(board, i, j, (DIRECTION)k);
            if (isValid(board, visited, i + row[k], j + col[k]) && isValid(board, visited, endPoint[0], endPoint[1]))
            {
                // mark next cell as visited and enqueue it
                visited[i + row[k]][j + col[k]] = true;
                visited[endPoint[0]][endPoint[1]] = true;
                q.push({ endPoint[0], endPoint[1], dist + 1 });

                choice.push_back(std::vector<int>{ i, j, i + row[k], j + col[k], endPoint[0], endPoint[1], dist + 1 });
            }
        }
    }

    if (min_dist != INT_MAX)
        qDebug() << "The shortest path from source to destination "
                    "has length " << min_dist << endl;
    else
        qDebug() << "Destination can't be reached from given source" << endl;

    std::stack<std::vector<int>> stp;
    bool a = findStp(choice, min_dist, x, y, stp, board);
    for (int i = 0; i < min_dist; i++) {

        qDebug() << stp.top()[2] << ',' << stp.top()[3] << endl;
        stp.pop();
    }

}
