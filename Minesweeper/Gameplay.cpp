#include <stdio.h>
#include <time.h>
#include "headers/variables.h"
#include "headers/board.h"
#include "headers/gameplay.h"
#include "headers/endGame.h"

void setGameplayDisplay(int &x, int &y) {	
	al_clear_to_color(darkBlue);

	image = al_load_bitmap("images/smile.png");
	al_draw_bitmap(image, ((screen_width / 2) - 15), 85, NULL);

	image = al_load_bitmap("images/clock.png");
	al_draw_bitmap(image, x, 85, NULL);
	al_draw_filled_rectangle(x + 36, 86, x + 94, 114, infoColor);
	al_draw_rectangle(x + 35, 85, x + 95, 115, lightBlue, 1);

	image = al_load_bitmap("images/mines.png");
	al_draw_bitmap(image, x + (SQUARE_SIZE * (new_board.columns - 3) - 5), 85, NULL);
	al_draw_filled_rectangle(x + (SQUARE_SIZE * (new_board.columns - 2) + 1), 86, x + (SQUARE_SIZE * (new_board.columns)) - 1, 114, infoColor);
	al_draw_rectangle(x + (SQUARE_SIZE * (new_board.columns - 2)), 85, x + (SQUARE_SIZE * (new_board.columns)), 115, lightBlue, 1);

	int tmp_x = x;
	int tmp_y = y;
	square = al_load_bitmap("images/uncovered.png");
	for (int i = 0; i < new_board.rows; i++) {
		for (int j = 0; j < new_board.columns; j++) {
			al_draw_bitmap(square, tmp_x, tmp_y, NULL);
			tmp_x += SQUARE_SIZE;
		}
		tmp_x = x;
		tmp_y += SQUARE_SIZE;
	}

	al_flip_display();
}

void showMineCounter(int &x, int mine_counter) {
	char buff[5];
	snprintf(buff, sizeof(buff), "%d", mine_counter);
	al_draw_filled_rectangle(x + (SQUARE_SIZE * (new_board.columns - 2) + 1), 86, x + (SQUARE_SIZE * (new_board.columns)) - 1, 114, infoColor);
	al_draw_text(nbr_font, lightBlue, x + (SQUARE_SIZE * (new_board.columns - 2) + 5), 80, ALLEGRO_ALIGN_LEFT, buff);
}

void showTime(int &x) {
	char buff[5];
	snprintf(buff, sizeof(buff), "%d", al_get_timer_count(timer));
	al_draw_filled_rectangle(x + 36, 86, x + 94, 114, infoColor);
	al_draw_text(nbr_font, lightBlue, x + 40, 80, ALLEGRO_ALIGN_LEFT, buff);
}

void gameplayLoop() {
	int pos_x = (screen_width / 2) - ((SQUARE_SIZE * new_board.columns) / 2);
	int pos_y = 120;

	int mouse_x, mouse_y;
	int tmp_x = NULL; 
	int tmp_y = NULL;
	int mine_counter = new_board.mines;
	bool check, startTimer = false;
	bool if_lost = false;

	Matrix **matrix = createMatrix();
	generateBoard(matrix);

	Position *flagArr = (Position*)malloc(new_board.rows * new_board.columns * sizeof(Position));
	nullFlagArr(flagArr);

	setGameplayDisplay(pos_x, pos_y);

	timer = al_create_timer(1.0);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	while (true) {
		al_wait_for_event(event_queue, &events);
		al_get_mouse_state(&state);

		showTime(pos_x);
		showMineCounter(pos_x, mine_counter);

		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if (mouse_x >= pos_x && mouse_x <= (pos_x + (SQUARE_SIZE * new_board.columns)) && (mouse_y >= pos_y && mouse_y <= (pos_y + (SQUARE_SIZE * new_board.rows)))) {
				if (state.buttons & 1){
					check = leftButtonDown(matrix, flagArr, mouse_x, mouse_y, pos_x, pos_y);

					if (!check) {
						tmp_x = mouse_x;
						tmp_y = mouse_y;
					}
				}
				else if (state.buttons & 2) {
					if (!startTimer) {
						al_start_timer(timer);
						startTimer = true;
					}

					markSpot(matrix, flagArr, mouse_x, mouse_y, pos_x, pos_y, mine_counter);
				}
			}
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if (mouse_x == tmp_x && mouse_y == tmp_y) {
				if (!startTimer) {
					al_start_timer(timer);
					startTimer = true;
				}

				if (leftButtomUp(flagArr, matrix, mouse_x, mouse_y, pos_x, pos_y)) {
					if_lost = true;
					break;
				}
			}
		}

		if (checkIfGameWin(matrix, flagArr, pos_x, pos_y)) {
			al_stop_timer(timer);

			image = al_load_bitmap("images/smile3.png");
			al_draw_filled_rectangle((screen_width / 2) - 15, 85, (screen_width / 2) + 15, 115, darkBlue);
			al_draw_bitmap(image, ((screen_width / 2) - 15), 85, NULL);
			al_flip_display();
			break;
		}

		al_flip_display();
	}
	
	// free memory of dynamic structures
	for (int i = 0; i < new_board.rows; i++){
		Matrix* ptr = matrix[i];
		free(ptr);
	}

	free(flagArr);
	endGameLoop(if_lost);
}

int computeColumn(int mouse_x, int &pos_x) {
	return (mouse_x - pos_x) / SQUARE_SIZE;
}

int computeRow(int mouse_y, int &pos_y) {
	return (mouse_y - pos_y) / SQUARE_SIZE;
}

int computeX(int columnNbr, int &pos_x) {
	return pos_x + (SQUARE_SIZE * columnNbr);
}

int computeY(int rowNbr, int &pos_y) {
	return pos_y + (SQUARE_SIZE * rowNbr);
}

void nullFlagArr(Position *flagArr) {
	for (int i = 0; i < (new_board.rows * new_board.columns); i++) {
		flagArr[i].x = NULL;
		flagArr[i].y = NULL;
	}
}

bool isInFlagArr(Position *flagArr, int &x, int &y) {
	bool check = false;

	for (int i = 0; i < (new_board.rows * new_board.columns); i++) {
		if (flagArr[i].x == x && flagArr[i].y == y) {
			check = true;
			break;
		}
	}
	return check;
}

bool leftButtonDown(Matrix **matrix, Position *flagArr, int mouse_x, int mouse_y, int &pos_x, int &pos_y) {
	int column = computeColumn(mouse_x, pos_x);
	int row = computeRow(mouse_y, pos_y);
	int x = computeX(column, pos_x);
	int y = computeY(row, pos_y);
	bool check = isInFlagArr(flagArr, x, y);

	if (!check) {
		if (!matrix[row][column].state) {
			image = al_load_bitmap("images/smile2.png");
			al_draw_filled_rectangle((screen_width / 2) - 15, 85, (screen_width / 2) + 15, 115, darkBlue);
			al_draw_bitmap(image, ((screen_width / 2) - 15), 85, NULL);
		}
	}
	return check;
}

void markSpot(Matrix **matrix, Position *flag_Arr, int mouse_x, int mouse_y, int &pos_x, int &pos_y, int &mine_counter) {
	int column = computeColumn(mouse_x, pos_x);
	int row = computeRow(mouse_y, pos_y);
	int x = computeX(column, pos_x);
	int y = computeY(row, pos_y);
	int i = 0;

	if (!matrix[row][column].state) {
		bool check = isInFlagArr(flag_Arr, x, y);

		if(check){
			while (!(flag_Arr[i].x == x && flag_Arr[i].y == y))
				i++;

			flag_Arr[i].x = NULL; flag_Arr[i].y = NULL;
			mine_counter++;
	
			square = al_load_bitmap("images/uncovered.png");
			al_draw_bitmap(square, x, y, NULL);
		}
		else {
			while (flag_Arr[i].x != NULL)
				i++;
			flag_Arr[i].x = x; 
			flag_Arr[i].y = y;
			mine_counter--;

			square = al_load_bitmap("images/flag.png");
			al_draw_bitmap(square, x, y, NULL);
		}
	}
}

void gameOver(Position *flag_Arr, Matrix **matrix, int tmp_x, int tmp_y, int &pos_x, int &pos_y) {
	image = al_load_bitmap("images/smile1.png");
	al_draw_filled_rectangle((screen_width / 2) - 15, 85, (screen_width / 2) + 15, 115, darkBlue);
	al_draw_bitmap(image, ((screen_width / 2) - 15), 85, NULL);

	int row, column, x, y;
	
	for (int i = 0; i < new_board.rows; i++) {
		for (int j = 0; j < new_board.columns; j++) {
			x = computeX(j, pos_x);
			y = computeY(i, pos_y);
			if (matrix[i][j].number == 9 && !isInFlagArr(flag_Arr, x, y)) {
				square = al_load_bitmap("images/bomb1.png");
				al_draw_bitmap(square, x, y, NULL);
			}
		}
	}

	for (int k = 0; k < (new_board.rows * new_board.columns); k++) {
		if (flag_Arr[k].x != NULL) {
			row = computeRow(flag_Arr[k].y, pos_y);
			column = computeColumn(flag_Arr[k].x, pos_x);

			if (matrix[row][column].number != 9) {
				square = al_load_bitmap("images/bomb_x.png");
				al_draw_bitmap(square, flag_Arr[k].x, flag_Arr[k].y, NULL);
			}
		}
	}

	square = al_load_bitmap("images/bomb2.png");
	al_draw_bitmap(square, computeX(tmp_x, pos_x), computeY(tmp_y, pos_y), NULL);
	al_flip_display();
}

bool checkIfGameWin(Matrix **matrix, Position *flag_Arr, int &pos_x, int &pos_y) {
	int i, j, x, y;
	int counter_square = NULL;
	int counter_flags = NULL;

	for (i = 0; i < new_board.rows; i++) {
		for (j = 0; j < new_board.columns; j++) {
			if (matrix[i][j].state)
				counter_square++;
		}
	}

	for (i = 0; i < new_board.rows; i++) {
		for (j = 0; j < new_board.columns; j++) {
			x = computeX(j, pos_x);
			y = computeY(i, pos_y);
			if (matrix[i][j].number == 9 && isInFlagArr(flag_Arr, x, y))
				counter_flags++;
		}
	}
	
	if (counter_square == ((new_board.rows * new_board.columns) - new_board.mines) && counter_flags == new_board.mines)
		return true;
	else
		return false;
}

bool leftButtomUp(Position *flag_Arr, Matrix **matrix, int mouse_x, int mouse_y, int &pos_x, int &pos_y) {
	int tmp_column = computeColumn(mouse_x, pos_x);
	int tmp_row = computeRow(mouse_y, pos_y);

	if (matrix[tmp_row][tmp_column].number == 9) {
		al_stop_timer(timer);
		gameOver(flag_Arr, matrix, tmp_column, tmp_row, pos_x, pos_y);
		return true;
	}
	else {
		image = al_load_bitmap("images/smile.png");
		al_draw_filled_rectangle((screen_width / 2) - 15, 85, (screen_width / 2) + 15, 115, darkBlue);
		al_draw_bitmap(image, ((screen_width / 2) - 15), 85, NULL);

		recursiveUncovering(matrix, flag_Arr, tmp_column, tmp_row, pos_x, pos_y);

		return false;
	}
}

void recursiveUncovering(Matrix **matrix, Position *flag_Arr, int column, int row, int &pos_x, int &pos_y) {
	int draw_x = computeX(column, pos_x);
	int draw_y = computeY(row, pos_y);
	
	if (!matrix[row][column].state && !isInFlagArr(flag_Arr, draw_x, draw_y)) {
		matrix[row][column].state = true;
		int number = loadSquare(matrix, column, row);
		al_draw_bitmap(square, draw_x, draw_y, NULL);

		if (number == 0) {
			checkCell(matrix, flag_Arr, column - 1, row, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column - 1, row + 1, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column - 1, row - 1, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column, row + 1, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column, row - 1, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column + 1, row, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column + 1, row + 1, pos_x, pos_y);
			checkCell(matrix, flag_Arr, column + 1, row - 1, pos_x, pos_y);
		}
	}
}

void checkCell(Matrix **matrix, Position *flag_Arr, int column, int row, int &pos_x, int &pos_y) {
	if ((column >= 0 && column < new_board.columns) && (row >= 0 && row < new_board.rows))
		recursiveUncovering(matrix, flag_Arr, column, row, pos_x, pos_y);
}

int loadSquare(Matrix **matrix, int column, int row) {
	int number;
	if (matrix[row][column].number == 0) {
		square = al_load_bitmap("images/0.png");
		number = 0;
	}
	else if (matrix[row][column].number == 1) {
		square = al_load_bitmap("images/1.png");
		number = 1;
	}
	else if (matrix[row][column].number == 2) {
		square = al_load_bitmap("images/2.png");
		number = 2;
	}
	else if (matrix[row][column].number == 3) {
		square = al_load_bitmap("images/3.png");
		number = 3;
	}
	else if (matrix[row][column].number == 4) {
		square = al_load_bitmap("images/4.png");
		number = 4;
	}
	else if (matrix[row][column].number == 5) {
		square = al_load_bitmap("images/5.png");
		number = 5;
	}
	else if (matrix[row][column].number == 6) {
		square = al_load_bitmap("images/6.png");
		number = 6;
	}
	else if (matrix[row][column].number == 7) {
		square = al_load_bitmap("images/7.png");
		number = 7;
	}
	else if (matrix[row][column].number == 8) {
		square = al_load_bitmap("images/8.png");
		number = 8;
	}
	return number;
}