#include "headers/variables.h"
#include "headers/newGame.h"
#include "headers/board.h"
#include "headers/gameplay.h"

void setNewGameDisplay() {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y, ALLEGRO_ALIGN_CENTRE, "MINESWEEPER");
	al_draw_text(info_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 60, ALLEGRO_ALIGN_CENTRE, "Choose difficulty level");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 110, ALLEGRO_ALIGN_CENTRE, "easy");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 165, ALLEGRO_ALIGN_CENTRE, "medium");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 220, ALLEGRO_ALIGN_CENTRE, "hard");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 275, ALLEGRO_ALIGN_CENTRE, "custom");
	al_draw_text(menu_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 340, ALLEGRO_ALIGN_CENTRE, "back");
}

void setCustomDisplay(int cursor) {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y, ALLEGRO_ALIGN_CENTRE, "MINESWEEPER");
	al_draw_text(info_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 60, ALLEGRO_ALIGN_CENTRE, "Specify the dimentions");
	al_draw_text(info_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 85, ALLEGRO_ALIGN_CENTRE, "max 30 x 24");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X - 110, MINESWEEPER_Y + 140, ALLEGRO_ALIGN_CENTRE, "X = ");
	al_draw_filled_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 140, MINESWEEPER_X + 180, MINESWEEPER_Y + 180, infoColor);
	al_draw_ustr(nbr_font, lightBlue, MINESWEEPER_X - 65, MINESWEEPER_Y + 140, ALLEGRO_ALIGN_LEFT, input_X);
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X - 110, MINESWEEPER_Y + 200, ALLEGRO_ALIGN_CENTRE, "Y = ");
	al_draw_filled_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 200, MINESWEEPER_X + 180, MINESWEEPER_Y + 240, infoColor);
	al_draw_ustr(nbr_font, lightBlue, MINESWEEPER_X - 65, MINESWEEPER_Y + 200, ALLEGRO_ALIGN_LEFT, input_Y);
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X - 140, MINESWEEPER_Y + 260, ALLEGRO_ALIGN_CENTRE, "mines =  ");
	al_draw_filled_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 260, MINESWEEPER_X + 180, MINESWEEPER_Y + 300, infoColor);
	al_draw_ustr(nbr_font, lightBlue, MINESWEEPER_X - 65, MINESWEEPER_Y + 260, ALLEGRO_ALIGN_LEFT, input_mines);

	if (cursor == 0)
		al_draw_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 140, MINESWEEPER_X + 180, MINESWEEPER_Y + 180, lightBlue, 1);
	else if(cursor == 1)
		al_draw_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 200, MINESWEEPER_X + 180, MINESWEEPER_Y + 240, lightBlue, 1);
	else if(cursor == 2)
		al_draw_rectangle(MINESWEEPER_X - 75, MINESWEEPER_Y + 260, MINESWEEPER_X + 180, MINESWEEPER_Y + 300, lightBlue, 1);
}

void warning(bool smaller) {
	if(smaller)
		al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 320, ALLEGRO_ALIGN_CENTRE, "Choose smaller number !");
	else
		al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 320, ALLEGRO_ALIGN_CENTRE, "Choose greater number !");
}

void newGameLoop() {
	int mouse_x, mouse_y;

	while (true) {
		setNewGameDisplay();
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 104) && (mouse_y <= MINESWEEPER_Y + 154))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 104, MINESWEEPER_X + 125, MINESWEEPER_Y + 154, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 159) && (mouse_y <= MINESWEEPER_Y + 209))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 159, MINESWEEPER_X + 125, MINESWEEPER_Y + 209, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 214) && (mouse_y <= MINESWEEPER_Y + 264))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 214, MINESWEEPER_X + 125, MINESWEEPER_Y + 264, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 269) && (mouse_y <= MINESWEEPER_Y + 319))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 269, MINESWEEPER_X + 125, MINESWEEPER_Y + 319, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 334) && (mouse_y <= MINESWEEPER_Y + 384))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 334, MINESWEEPER_X + 125, MINESWEEPER_Y + 384, infoColor, 1);
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 104) && (mouse_y <= MINESWEEPER_Y + 154)) {
				fill_boardData(8, 8, 10);
				gameplayLoop();
				break;
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 159) && (mouse_y <= MINESWEEPER_Y + 209)) {
				fill_boardData(16, 16, 40);
				gameplayLoop();
				break;
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 214) && (mouse_y <= MINESWEEPER_Y + 264)) {
				fill_boardData(16, 30, 99);
				gameplayLoop();
				break;
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 269) && (mouse_y <= MINESWEEPER_Y + 319)) {
				customLoop();
				break;
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 334) && (mouse_y <= MINESWEEPER_Y + 384))
				break;
		}
		al_flip_display();
	}
}

void customLoop() {
	ALLEGRO_USTR **ptr;
	ptr = &input_X;
	int number, digit, p;

	setCustomDisplay(3);

	for (int i = 0; i < 3; i++) {
		number = NULL;
		*ptr = al_ustr_new("");
		p = (int)al_ustr_size(*ptr);

		while (true) {
			al_register_event_source(event_queue, al_get_keyboard_event_source());
			al_wait_for_event(event_queue, &events);
			setCustomDisplay(i);

			if (events.type == ALLEGRO_EVENT_KEY_CHAR) {
				if (events.keyboard.unichar >= '0' && events.keyboard.unichar <= '9') {
					p += al_ustr_append_chr(*ptr, events.keyboard.unichar);
					digit = events.keyboard.unichar - '0';
					number = number * 10 + digit;
				}
				else if (events.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
					if (al_ustr_prev(*ptr, &p))
						al_ustr_truncate(*ptr, p);
					number = number / 10;
				}
				else if (events.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (i == 0) {
						if (number < 10 || number > 30) {
							if (number < 10)
								warning(0);
							else
								warning(1);
							al_flip_display();
							continue;
						}
						new_board.columns = number;
						ptr = &input_Y;
						*ptr = al_ustr_new("");
						p = (int)al_ustr_size(*ptr);
					}
					else if (i == 1) {
						if (number < 10 || number > 24) {
							if (number < 10)
								warning(0);
							else
								warning(1);
							al_flip_display();
							continue;
						}
						new_board.rows = number;
						ptr = &input_mines;
						*ptr = al_ustr_new("");
						p = (int)al_ustr_size(*ptr);
					}
					else if (i == 2) {
						if (number < 10 || number > ((new_board.columns - 1) * (new_board.rows - 1))) {
							if (number < 10)
								warning(0);
							else if (number > ((new_board.columns - 1) * (new_board.rows - 1)))
								warning(1);
							al_flip_display();
							continue;
						}
						new_board.mines = number;
					}
					break;
				}
			}
			al_flip_display();
		}
	}

	input_X = NULL;
	input_Y = NULL;
	input_mines = NULL;

	gameplayLoop();
}