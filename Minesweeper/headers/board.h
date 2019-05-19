#pragma once

struct BoardData{
	int rows;
	int columns;
	int mines;
};

struct Position {
	int x;
	int y;
};

struct Matrix {
	int number;
	bool state;
};

extern BoardData new_board;

void fill_boardData(int, int, int);
Matrix** createMatrix();
void generateBoard(Matrix**);
void cellNumber(Matrix**, int, int);
void printMatrix(Matrix**);