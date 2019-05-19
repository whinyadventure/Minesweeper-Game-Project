#include <stdio.h>
#include <stdlib.h>
#include "headers/board.h"

BoardData new_board;

void fill_boardData(int x, int y, int mines) {
		new_board.rows = x;
		new_board.columns = y;
		new_board.mines = mines;
}

Matrix** createMatrix() {
	int i, j;
	Matrix **matrix = (Matrix**)malloc(new_board.rows * sizeof(Matrix*));

	for (i = 0; i < new_board.rows; i++)
		matrix[i] = (Matrix*)malloc(new_board.columns * sizeof(Matrix));

	for (i = 0; i < new_board.rows; i++) {
		for (j = 0; j < new_board.columns; j++) {
			matrix[i][j].number = NULL;
			matrix[i][j].state = false;
		}
	}
	return matrix;
}

void generateBoard(Matrix **matrix) {
	Position *mineArr = (Position*)malloc(new_board.mines * sizeof(Position));
	int rand_row, rand_column;
	int counter = NULL;

	while (counter != new_board.mines) {
		rand_row = rand() % new_board.rows;
		rand_column = rand() % new_board.columns;

		if (matrix[rand_row][rand_column].number == NULL) {
			matrix[rand_row][rand_column].number = 9;
			mineArr[counter].x = rand_row;
			mineArr[counter].y = rand_column;
			counter++;
		}
	}

	for (int i = 0; i < new_board.mines; i++) {
		cellNumber(matrix, mineArr[i].x - 1, mineArr[i].y);
		cellNumber(matrix, mineArr[i].x - 1, mineArr[i].y - 1);
		cellNumber(matrix, mineArr[i].x - 1, mineArr[i].y + 1);
		cellNumber(matrix, mineArr[i].x, mineArr[i].y - 1);
		cellNumber(matrix, mineArr[i].x, mineArr[i].y + 1);
		cellNumber(matrix, mineArr[i].x + 1, mineArr[i].y);
		cellNumber(matrix, mineArr[i].x + 1, mineArr[i].y - 1);
		cellNumber(matrix, mineArr[i].x + 1, mineArr[i].y + 1);
	}
	free(mineArr);
}

void cellNumber(Matrix **matrix, int x, int y) {
	if ((x >= 0 && x < new_board.rows) && (y >= 0 && y < new_board.columns) && (matrix[x][y].number != 9))
		matrix[x][y].number++;
}

void printMatrix(Matrix **matrix) {
	int i, j;
	for (i = 0; i < new_board.rows; i++) {
		for (j = 0; j < new_board.columns; j++)
			printf_s("(%d,%d) ", matrix[i][j].number, matrix[i][j].state);
		printf_s("\n");
	}
	printf_s("\n");
}
