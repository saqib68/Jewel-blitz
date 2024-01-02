#include <iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include <cstdlib>
#include"help.h"

using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 120
#define KEY_ENTER 13
void bigboldfont()
{
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 450;
	fontex.dwFontSize.X = 30;
	fontex.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}
//function for diamond
void Diamond(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	myEllipse(x1, y1 - 10, x2, y1 + 10, R, G, B);
	int x = 1;
	for (int i = 1; i <= 22; i++)
	{

		myLine(x1 + x, y1 + x, x2 - x, y2 + x, R, G, B);
		x++;
	}
}
//function for triangle
void triangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{

	int x = 1;
	for (int i = 1; x <= 23; i++)
	{
		myLine(x1 - x, x + y1, x + x2, x + y1, R, G, B);
		x++;
	}


}
bool checkifanypairs4(int arr[8][8]) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i][j + 3])
				return true;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++) {
			if (arr[j][i] == arr[j + 1][i] && arr[j][i] == arr[j + 2][i] && arr[j + 3][i] == arr[j][i])
				return true;
		}
	}
	return false;
}
bool checkifanypairs(int arr[8][8]) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2]) {

				return true;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		//cout << i;
		;		for (int j = 0; j < 6; j++) {
			if (arr[j][i] == arr[j + 1][i] && arr[j][i] == arr[j + 2][i]) {
				//cout << "CC";
				return true;
			}
		}
	}
	return false;
}
bool checkSPECIAL4row(int arr[8][8]) {
	int arr1[8][8];
	int r = 99, c = 99, chk = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			arr[i][j] = arr1[i][j];
			if (arr1[i][j] > 5) {
				r = i;
				c = i;
				chk = 1;
			}
		}
	}
	if (chk == 1) {
		arr1[r][c] = arr1[r][c] - 5;
		if (checkifanypairs(arr1) == true) {
			//cout << "KK";
			return 1;
		}
	}
	return 0;
}
void swapping(int& a, int& b, char chk, int arr[8][8], int& x, int& y)
{
	switch (chk) {

	case KEY_DOWN:
		swap(arr[a][b], arr[a + 1][b]);
		if (checkifanypairs(arr) == 0 && checkSPECIAL4row(arr) == 0) {

			swap(arr[a][b], arr[a + 1][b]);
			break;
		}
		a = a + 1;
		y = y + 60;
		break;
	case KEY_UP:
		swap(arr[a][b], arr[a - 1][b]);
		if (checkifanypairs(arr) == 0 && checkSPECIAL4row(arr) == 0) {
			swap(arr[a][b], arr[a - 1][b]);
			break;
		}
		a = a - 1;
		y = y - 60;
		break;
	case KEY_RIGHT:
		swap(arr[a][b + 1], arr[a][b]);
		if (checkifanypairs(arr) == 0 && checkSPECIAL4row(arr) == 0) {

			swap(arr[a][b + 1], arr[a][b]);
			break;
		}
		b = b + 1;
		x = x + 60;
		break;
	case KEY_LEFT:
		swap(arr[a][b - 1], arr[a][b]);
		if (checkifanypairs(arr) == 0 && checkSPECIAL4row(arr) == 0) {
			swap(arr[a][b - 1], arr[a][b]);
			break;
		}
		b = b - 1;
		x = x - 60;
		break;
	default:
		char k = _getch();
		swapping(a, b, k, arr, x, y);
		break;

	}
}
int checkboardofrow(int arr[8][8], int row, int& chk) {
	int arr1[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] > 5)
				arr1[i][j] = arr[i][j] - 5;
			else
				arr1[i][j] = arr[i][j];
		}
	}
	int col = 99;
	chk = 0;
	for (int i = 0; i < 6; i++) {
		if (arr1[row][i] == arr1[row][i + 1] && arr1[row][i + 2] == arr1[row][i]) {
			chk = 1;
			col = i;
			//cout << "yup"<<" row "<<row <<" col"<< i;
			return col;
		}
	}
	return col;
}
int checkboardofcol(int arr[8][8], int col, int& chk) {
	int row = 99;
	chk = 0;
	for (int i = 7; i > 1; i--) {

		if (arr[i][col] == arr[i - 1][col] && arr[i][col] == arr[i - 2][col]) {
			chk = 1;
			row = i;
			//cout << "yup" << " row " << row << " col" << i;
			return row;
		}
	}
}
void operationfalldown3(int arr[][8], int row, int col) {
	for (int i = row; i > 0; i--)
	{
		swap(arr[i][col], arr[i - 1][col]);
		swap(arr[i][col + 1], arr[i - 1][col + 1]);
		swap(arr[i][col + 2], arr[i - 1][col + 2]);

	}
	{
		srand(time(0));
		arr[0][col] = rand() % (5 - 1 + 1) + 1;
		arr[0][col + 1] = rand() % (5 - 1 + 1) + 1;
		arr[0][col + 2] = rand() % (5 - 1 + 1) + 1;
	}
}
void operationfalldowncol3(int arr[][8], int row, int col) {
	if (row == 3) {
		swap(arr[row][col], arr[row - 3][col]);
	}

	if (row == 4) {
		swap(arr[row][col], arr[row - 3][col]);
		swap(arr[row - 1][col], arr[row - 4][col]);
	}
	if (row == 5)
	{
		swap(arr[row][col], arr[row - 3][col]);
		swap(arr[row - 1][col], arr[row - 4][col]);
		swap(arr[row - 2][col], arr[row - 5][col]);
	}
	if (row == 6)
	{
		swap(arr[row][col], arr[row - 3][col]);
		swap(arr[row - 1][col], arr[row - 4][col]);
		swap(arr[row - 2][col], arr[row - 5][col]);
		swap(arr[0][col], arr[3][col]);
	}
	if (row == 7) {
		swap(arr[row][col], arr[row - 3][col]);
		swap(arr[row - 1][col], arr[row - 4][col]);
		swap(arr[row - 2][col], arr[row - 5][col]);
		swap(arr[0][col], arr[3][col]);
		swap(arr[1][col], arr[4][col]);
	}
	{
		srand(time(0));
		arr[0][col] = rand() % (5 - 1 + 1) + 1;
		arr[1][col] = rand() % (5 - 1 + 1) + 1;
		arr[2][col] = rand() % (5 - 1 + 1) + 1;
	}
}
//void display(int gameboard[][8], int& selectionx, int& selectiony) {
//	//background
//	myRectangle(0, 0, 2000, 800, 155, 155, 0);
//
//	//frame
//	int x = 10, y = 10;
//	myRectangle(450, 50, 940, 540, 255, 255, 255);
//
//	for (int i = 0; i < 8; i++)
//	{
//		int x = 10;
//		for (int j = 0; j < 8; j++)
//		{
//			myRectangle(x + 450, y + 50, x + 500, y + 100, 0, 0, 0);
//			x = x + 60;
//		}
//		y = y + 60;
//	}
//	//shapes in game
//	int z = 10, k = 10;
//
//
//	for (int i = 0; i < 8; i++)
//	{
//		int z = 10;
//		for (int j = 0; j < 8; j++)
//		{
//			if (gameboard[i][j] == 5)
//
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 0, 255, 0);
//
//			else if (gameboard[i][j] == 4)
//				myEllipse(z + 460, k + 60, z + 490, k + 90, 255, 255, 0);
//			else if (gameboard[i][j] == 3)
//			{
//				triangle(z + 474, k + 63, z + 473, k + 63, 185, 65, 255);
//			}
//			else if (gameboard[i][j] == 2)
//			{
//				Diamond(z + 452, k + 65, z + 496, k + 65, 135, 206, 235);
//			}
//			else if (gameboard[i][j] == 1)
//			{
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 210, 210, 235);
//				myEllipse(z + 457, k + 58, z + 493, k + 92, 210, 210, 235);
//
//			}
//
//			z = z + 60;
//		}
//
//		k = k + 60;
//
//	}
//	///curser
//	{
//		myLine(selectionx, selectiony, selectionx + 60, selectiony, 0, 0, 0);
//		myLine(selectionx, selectiony, selectionx, selectiony + 60, 0, 0, 0);
//		myLine(selectionx, selectiony + 60, selectionx + 60, selectiony + 60, 0, 0, 0);
//		myLine(selectionx + 60, selectiony, selectionx + 60, selectiony + 60, 0, 0, 0);
//	}
//}
//void display(int gameboard[][8], int& selectionx, int& selectiony) {
//	//background
//	myRectangle(0, 0, 2000, 800, 155, 155, 0);
//
//	//frame
//	int x = 10, y = 10;
//	myRectangle(450, 50, 940, 540, 255, 255, 255);
//
//	for (int i = 0; i < 8; i++)
//	{
//		int x = 10;
//		for (int j = 0; j < 8; j++)
//		{
//			myRectangle(x + 450, y + 50, x + 500, y + 100, 0, 0, 0);
//			x = x + 60;
//		}
//		y = y + 60;
//	}
//	//shapes in game
//	int z = 10, k = 10;
//
//
//	for (int i = 0; i < 8; i++)
//	{
//		int z = 10;
//		for (int j = 0; j < 8; j++)
//		{
//			if (gameboard[i][j] == 5)
//			{
//
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 255, 0, 0);
//			}
//
//			else if (gameboard[i][j] == 4)
//				myEllipse(z + 460, k + 60, z + 490, k + 90, 0, 255, 0);
//			else if (gameboard[i][j] == 3)
//			{
//				triangle(z + 474, k + 63, z + 473, k + 63, 185, 65, 255);
//			}
//			else if (gameboard[i][j] == 2)
//			{
//				Diamond(z + 452, k + 65, z + 496, k + 65, 135, 206, 235);
//			}
//			else if (gameboard[i][j] == 1)
//			{
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 210, 210, 235);
//				myEllipse(z + 457, k + 58, z + 493, k + 92, 210, 210, 235);
//
//			}
//			else if (gameboard[i][j] == 6)
//			{
//				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
//
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 255, 0, 0);
//			}
//			else if (gameboard[i][j] == 7)
//			{
//				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
//				myEllipse(z + 460, k + 60, z + 490, k + 90, 0, 255, 0);
//
//
//			}
//			else if (gameboard[i][j] == 8)
//			{
//				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
//				triangle(z + 474, k + 63, z + 473, k + 63, 185, 65, 255);
//
//			}
//			else if (gameboard[i][j] == 9)
//			{
//				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
//				Diamond(z + 452, k + 65, z + 496, k + 65, 135, 206, 235);
//
//			}
//			else if (gameboard[i][j] == 10)
//			{
//				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
//				myRectangle(z + 460, k + 60, z + 490, k + 90, 210, 210, 235);
//				myEllipse(z + 457, k + 58, z + 493, k + 92, 210, 210, 235);
//
//			}
//
//
//
//			z = z + 60;
//		}
//
//		k = k + 60;
//
//	}
//	///curser
//	{
//		myLine(selectionx, selectiony, selectionx + 60, selectiony, 0, 0, 0);
//		myLine(selectionx, selectiony, selectionx, selectiony + 60, 0, 0, 0);
//		myLine(selectionx, selectiony + 60, selectionx + 60, selectiony + 60, 0, 0, 0);
//		myLine(selectionx + 60, selectiony, selectionx + 60, selectiony + 60, 0, 0, 0);
//	}
//}
void display(int gameboard[][8], int& selectionx, int& selectiony) {
	//background
	myRectangle(0, 0, 2000, 800, 155, 155, 0);

	//frame
	int x = 10, y = 10;
	myRectangle(450, 50, 940, 540, 255, 255, 255);

	for (int i = 0; i < 8; i++)
	{
		int x = 10;
		for (int j = 0; j < 8; j++)
		{
			myRectangle(x + 450, y + 50, x + 500, y + 100, 0, 0, 0);
			x = x + 60;
		}
		y = y + 60;
	}
	//shapes in game
	int z = 10, k = 10;


	for (int i = 0; i < 8; i++)
	{
		int z = 10;
		for (int j = 0; j < 8; j++)
		{
			if (gameboard[i][j] == 1)
			{

				myRectangle(z + 460, k + 60, z + 490, k + 90, 255, 0, 0);
			}

			else if (gameboard[i][j] == 2)
				myEllipse(z + 460, k + 60, z + 490, k + 90, 0, 255, 0);
			else if (gameboard[i][j] == 3)
			{
				triangle(z + 474, k + 63, z + 473, k + 63, 185, 65, 255);
			}
			else if (gameboard[i][j] == 4)
			{
				Diamond(z + 452, k + 65, z + 496, k + 65, 135, 206, 235);
			}
			else if (gameboard[i][j] == 5)
			{
				myRectangle(z + 460, k + 60, z + 490, k + 90, 210, 210, 235);
				myEllipse(z + 457, k + 58, z + 493, k + 92, 210, 210, 235);

			}
			else if (gameboard[i][j] == 6)
			{
				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);

				myRectangle(z + 460, k + 60, z + 490, k + 90, 255, 0, 0);
			}
			else if (gameboard[i][j] == 7)
			{
				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
				myEllipse(z + 460, k + 60, z + 490, k + 90, 0, 255, 0);


			}
			else if (gameboard[i][j] == 8)
			{
				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
				triangle(z + 474, k + 63, z + 473, k + 63, 185, 65, 255);

			}
			else if (gameboard[i][j] == 9)
			{
				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
				Diamond(z + 452, k + 65, z + 496, k + 65, 135, 206, 235);

			}
			else if (gameboard[i][j] == 10)
			{
				myRectangle(z + 450, k + 50, z + 500, k + 100, 255, 255, 0);
				myRectangle(z + 460, k + 60, z + 490, k + 90, 210, 210, 235);
				myEllipse(z + 457, k + 58, z + 493, k + 92, 210, 210, 235);

			}



			z = z + 60;
		}

		k = k + 60;

	}
	///curser
	{
		myLine(selectionx, selectiony, selectionx + 60, selectiony, 0, 0, 0);
		myLine(selectionx, selectiony, selectionx, selectiony + 60, 0, 0, 0);
		myLine(selectionx, selectiony + 60, selectionx + 60, selectiony + 60, 0, 0, 0);
		myLine(selectionx + 60, selectiony, selectionx + 60, selectiony + 60, 0, 0, 0);
	}
}
int random() {

	return rand() % (5 - 1 + 1) + 1;
}
void COLoperationof3(int board[8][8]) {
	int row = 0, chk = 0;
	for (int i = 0; i < 8; i++) {
		chk = 0;
		row = 0;
		row = checkboardofcol(board, i, chk);
		if (chk == 1)
			operationfalldowncol3(board, row, i);
	}
}
void ROWoperationof3(int board[8][8]) {
	int col = 0, chk = 0;
	for (int i = 0; i < 8; i++) {
		chk = 0;
		col = 0;
		col = checkboardofrow(board, i, chk);
		if (chk == 1)
			operationfalldown3(board, i, col);
	}
}
int checkboard4ofrow(int arr[8][8], int row, int& chk) {
	int col = 99;
	chk = 0;
	for (int i = 0; i < 5; i++) {
		if (arr[row][i] == arr[row][i + 1] && arr[row][i + 2] == arr[row][i] && arr[row][i + 3] == arr[row][i]) {
			chk = 1;
			col = i;
			//cout << "yup"<<" row "<<row <<" col"<< i;
			return col;
		}
	}
	return col;
}
int checkboard4ofcol(int arr[8][8], int col, int& chk) {
	int row = 99;
	chk = 0;
	for (int i = 7; i > 2; i--) {

		if (arr[i][col] == arr[i - 1][col] && arr[i][col] == arr[i - 2][col] && arr[i][col] == arr[i - 3][col]) {
			chk = 1;
			row = i;
			//cout << "yup" << " row " << row << " col" << i;
			return row;
		}
	}
}
void operationfalldown4(int arr[8][8], int row, int col) {
	operationfalldown3(arr, row, col);
	//cout << row << col;


	arr[row][col + 3] = arr[row][col + 3] + 5;

}
void operationfalldowncol4(int arr[8][8], int row, int col) {
	operationfalldowncol3(arr, row, col);
	//cout << row << col;


	arr[row + 3][col] = arr[row + 3][col] + 5;

}
void ROWoperationof4(int board[8][8]) {
	int col = 0, chk = 0;
	for (int i = 0; i < 8; i++) {
		chk = 0;
		col = 0;
		col = checkboard4ofrow(board, i, chk);

		if (chk == 1)
			operationfalldown4(board, i, col);
	}
}
void COLoperationof4(int board[8][8]) {
	int row = 0, chk = 0;
	for (int i = 0; i < 8; i++) {
		chk = 0;
		row = 0;
		row = checkboard4ofcol(board, i, chk);
		if (chk == 1)
			operationfalldowncol4(board, row, i);
	}
}
//bool checkSPECIAL4row(int arr[8][8]) {
//	int arr1[8][8];
//	int r=99, c=99,chk=0;
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//			arr[i][j] = arr1[i][j];
//			if (arr1[i][j] > 5) {
//				r = i;
//				c = i;
//				chk = 1;
//			}
//		}
//	}
//	if (chk == 1) {
//		arr1[r][c] = arr1[r][c] - 5;
//		if (checkifanypairs(arr1) == true)
//			return 1;
//	}
//	return 0;
//}
int main() {
	time_t st, end;
	st = time(NULL);
	end = time(NULL) + 60;
	int board[8][8], c = 0;
	int selectionx = 455;
	int selectiony = 55;
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = rand() % 5 + 1;
		}
	}

	int a = 0, b = 0;
	char chk, chk1;

	while (checkifanypairs(board) == 1) {
		ROWoperationof3(board);
		COLoperationof3(board);
	}
	ROWoperationof3(board);
	COLoperationof3(board);
	bigboldfont();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);//brown
	cout << "\n\n\n\n\n\n\n                                  BEJEWELED BLITZ!        ";
	SetConsoleTextAttribute(h, 4);//red
	cout << "\n\n\n\n\n\n\n                               PRESS ANY KEY TO START!                 ";
	int p = _getch();
	system("cls");
	display(board, selectionx, selectiony);
	//st < end
	for (; st < end;) {
		switch (_getch()) {
			//movement
		case KEY_DOWN:
			//system("CLS");
			if (selectiony != 475) {
				a = a + 1;
				selectiony += 60;
				display(board, selectionx, selectiony);
			}

			break;
		case KEY_UP:
			//system("CLS");
			if (selectiony != 55)
			{
				a = a - 1;
				selectiony -= 60;
				display(board, selectionx, selectiony);

			}
			break;

		case KEY_RIGHT:
			// system("CLS"); /
			if (b != 7) {
				b = b + 1;
				selectionx += 60;
				display(board, selectionx, selectiony);
			}
			break;
		case KEY_LEFT:
			// system("CLS"); /
			if (b != 0) {
				selectionx -= 60;
				display(board, selectionx, selectiony);
				b = b - 1;
			}

			break;
		case KEY_ENTER:

			// system("CLS"); /

			display(board, selectionx, selectiony);
			chk = _getch();
			swapping(a, b, chk, board, selectionx, selectiony);
			//system("cls");
			bool chkk = checkifanypairs(board);
			//cout << checkifanypairs4(board);
			//p = _getch();
			display(board, selectionx, selectiony);
			break;


		}
		while (checkifanypairs4(board) == 1) {
			ROWoperationof4(board);
			COLoperationof4(board);
			c = c + 2;
		}

		while (checkifanypairs(board) == 1) {
			COLoperationof3(board);
			ROWoperationof3(board);
			c++;
		}

		display(board, selectionx, selectiony);
		st = time(NULL);
	}
	system("cls");
	cout << " \n\n\n\n\n\n\n                  THANK YOU! YOUR SCORE WAS " << c;
	cout << " \n\n                  PRESS ANY KEY TO EXIT \n\n\n\n\n\n\n\n";
	_getch();
}

