//#include <iostream>
//using namespace std;

//const char A = ' ';
//const char X = 'X';
//const int MAX_COL = 4;
//const int MAX_ROW = 4;

//char block[4][4] = {
//{ A,X,X,A },
//{ A,X,X,A },
//{ A,X,X,A },
//{ A,A,A,A }
//};
//int main()
//{

//	int player[2] = { 0,0 };
//	do {
//		char dir;
//        cout << "enter dir:" << endl;
//        cout << "up: w" << endl;
//        cout << "down: s" << endl;
//        cout << "left: a" << endl;
//        cout << "right: d" << endl;
//		cin >> dir;
//		switch (dir)
//		{
//		case 'w':
//			if (player[0] > 0 && block[player[0] - 1][player[1]] == A) {
//				player[0] = player[0] - 1;
//			}
//			break;
//		case 's':
//			if (player[0] < MAX_ROW - 1 && block[player[0] + 1][player[1]] == A) {
//				player[0] = player[0] + 1;
//			}
//			break;
//		case 'a':
//			if (player[1] > 0 && block[player[0]][player[1] - 1] == A) {
//				player[1] = player[1] - 1;
//			}
//			break;
//		case 'd':
//			if (player[1] < MAX_COL - 1 && block[player[0]][player[1] + 1] == A) {
//				player[1] = player[1] + 1;
//			}
//			break;
//		}
//		for (int r = 0; r < MAX_ROW; r++) {
//			for (int c = 0; c < MAX_COL; c++) {
//				if (player[0] == r && player[1] == c)
//					cout << '*';
//				else
//				{
//					cout << block[r][c];
//				}
//			}
//			cout << endl;
//		}

//	} while (player[0] != 0 || player[1] != 3);



//}
