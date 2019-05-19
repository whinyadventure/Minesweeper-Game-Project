#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "headers/board.h"
#include "headers/variables.h"
#include "headers/newGame.h"
#include "headers/highScores.h"

void setHighScores() {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y, ALLEGRO_ALIGN_CENTRE, "MINESWEEPER");
	al_draw_text(info_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 60, ALLEGRO_ALIGN_CENTRE, "High scores");
	al_draw_text(menu_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 450, ALLEGRO_ALIGN_CENTRE, "back");
	al_draw_text(menu_font, lightBlue, 200, MINESWEEPER_Y + 120, ALLEGRO_ALIGN_CENTRE, "easy");
	al_draw_text(menu_font, lightBlue, 450 , MINESWEEPER_Y + 120, ALLEGRO_ALIGN_CENTRE, "medium");
	al_draw_text(menu_font, lightBlue, 700, MINESWEEPER_Y + 120, ALLEGRO_ALIGN_CENTRE, "hard");
	al_draw_text(menu_font, lightBlue, 950 , MINESWEEPER_Y + 120, ALLEGRO_ALIGN_CENTRE, "custom");

	for (int i = 200; i <= 950; i += 250) {
		al_draw_text(info_font, infoColor, i - 90, MINESWEEPER_Y + 150, ALLEGRO_ALIGN_LEFT, "nickname");
		al_draw_text(info_font, infoColor, i + 90, MINESWEEPER_Y + 150, ALLEGRO_ALIGN_CENTRE, "time");
	}

	printScores(200, MINESWEEPER_Y + 180);
}

void printScores(int x, int y) {
	LoadedData *ptr = NULL;
	for (int i = 1; i < 5; i++) {
		ptr = loadData(i);
		for (int j = 0; j < 5; j++) {
			char buff[5], nbr[5];
			snprintf(buff, sizeof(buff), "%d", ptr[j].time);
			snprintf(nbr, sizeof(nbr), "%d.", j+1);
			if (ptr[j].time != NULL) {
				al_draw_text(nbr_font, lightBlue, x - 90, y, ALLEGRO_ALIGN_RIGHT, nbr);
				al_draw_text(menu_font, lightBlue, x - 80, y, ALLEGRO_ALIGN_LEFT, ptr[j].nickname);
				al_draw_text(nbr_font, lightBlue, x + 90, y, ALLEGRO_ALIGN_CENTRE, buff);
			}
			y += 40;
		}
		y = MINESWEEPER_Y + 180;
		x += 250;
	}
}

void highScoresLoop() {
	int mouse_x, mouse_y;

	while (true) {

		al_wait_for_event(event_queue, &events);
		setHighScores();

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 444) && (mouse_y <= MINESWEEPER_Y + 494))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 444, MINESWEEPER_X + 125, MINESWEEPER_Y + 494, infoColor, 1);
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 444) && (mouse_y <= MINESWEEPER_Y + 494))
				break;
		}

		al_flip_display();
	}
}

LoadedData* loadData(int diff_lvl) {
	FILE *file;
	LoadedData *scoresArr = (LoadedData*)malloc(6 * sizeof(LoadedData));
	nullTheStructArr(scoresArr);
	int tmp;

	if (diff_lvl == 1)
		file = fopen("easy.txt", "a+");
	else if (diff_lvl == 2)
		file = fopen("medium.txt", "a+");
	else if (diff_lvl == 3)
		file = fopen("hard.txt", "a+");
	else
		file = fopen("custom.txt", "a+");

	if (file) {
		if (!isEmpty(file)) {
			for (int i = 0; i < 5; i++) {
				if (fscanf(file, "%d\n", &tmp) > NULL) {
					scoresArr[i].time = tmp;
					fscanf(file, "%s\n", &scoresArr[i].nickname);
				}
			}
		}
	}
	fclose(file);

	return scoresArr;
}

void sortScores(LoadedData *scoreArr, char nickname[], int score) {
	int i = 0;
	while (scoreArr[i].time != NULL && scoreArr[i].time <= score)
		i++;
	
	int j = 5;
	while (j >= i) {
		scoreArr[j] = scoreArr[j - 1];
		j--;
	}

	for (int k = 0; k < 10; k++)
		scoreArr[i].nickname[k] = nickname[k];
	scoreArr[i].time = score;
}

void saveData(LoadedData *scoresArr) {
	FILE *file;

	int diff_lvl = getDiffLvl();

	if (diff_lvl == 1)
		file = fopen("easy.txt", "w");
	else if (diff_lvl == 2)
		file = fopen("medium.txt", "w");
	else if (diff_lvl == 3)
		file = fopen("hard.txt", "w");
	else
		file = fopen("custom.txt", "w");

	if (file) {
		for (int i = 0; i < 5; i++) {
			if (scoresArr[i].time != NULL) {
				fprintf(file, "%d\n", scoresArr[i].time);
				fprintf(file, "%s\n", scoresArr[i].nickname);
			}
		}
	}
	fclose(file);
}

void nullTheStructArr(LoadedData *scoresArr) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++)
			scoresArr[i].nickname[j] = '\0';
		scoresArr[i].time = NULL;
	}
}

bool isEmpty(FILE *file) {
	size_t length = ftell(file);
	fseek(file, NULL, SEEK_END);

	if (ftell(file) == NULL)
		return true;

	fseek(file, length, SEEK_SET);
	return false;
}

int getDiffLvl() {
	int diff_lvl;

	if (new_board.rows == 8 && new_board.columns == 8)
		diff_lvl = 1;
	else if (new_board.rows == 16 && new_board.columns == 16)
		diff_lvl = 2;
	else if (new_board.rows == 16 && new_board.columns == 30)
		diff_lvl = 3;
	else
		diff_lvl = 4;

	return diff_lvl;
}




