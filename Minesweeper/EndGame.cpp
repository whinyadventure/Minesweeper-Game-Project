#include <stdio.h>
#include "headers/endGame.h"
#include "headers/highScores.h"
#include "headers/variables.h"


void createInfoDisplay() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	info_display = al_create_display(700, 350);
	al_set_window_position(info_display, 600, 300);
}

void loserDisplay() {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, INFO_X, INFO_Y, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
	al_draw_text(menu_font, lightBlue, INFO_X - 100, INFO_Y + 90, ALLEGRO_ALIGN_CENTRE, "your score:");
	
	char buff[5];
	snprintf(buff, sizeof(buff), "%d", al_get_timer_count(timer));
	al_draw_text(nbr_font, lightBlue, INFO_X - 10, INFO_Y + 90, NULL, buff);
}

void winnerDisplay() {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, INFO_X, INFO_Y, ALLEGRO_ALIGN_CENTRE, "YOU WON");
	al_draw_text(menu_font, lightBlue, INFO_X - 90, INFO_Y + 90, ALLEGRO_ALIGN_CENTRE, "your score:");

	char buff[5];
	snprintf(buff, sizeof(buff), "%d", al_get_timer_count(timer));
	al_draw_text(nbr_font, lightBlue, INFO_X, INFO_Y + 90, NULL, buff);

	al_draw_text(menu_font, lightBlue, INFO_X - 80, INFO_Y + 140, ALLEGRO_ALIGN_CENTRE, "nickname:");
	al_draw_filled_rectangle(INFO_X, INFO_Y + 140, INFO_X + 180, INFO_Y + 180, infoColor);
	al_draw_ustr(menu_font, lightBlue, INFO_X + 10, INFO_Y + 140, ALLEGRO_ALIGN_LEFT, nickname);
}

void warning_nick() {
	al_draw_text(menu_font, lightBlue, INFO_X, INFO_Y + 200, ALLEGRO_ALIGN_CENTRE, "Nickname is too long!");
}

void endGameLoop(bool if_lost) {
	createInfoDisplay();

	nickname = al_ustr_new("");
	char nick[10];
	for (int i = 0; i < 10; i++) nick[i] = '\0';
	int p = (char)al_ustr_size(nickname);

	if (if_lost)
		loserDisplay();

	al_register_event_source(event_queue, al_get_display_event_source(info_display));

	while (true) {
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;

		if (!if_lost) {
			winnerDisplay();
			if (events.type == ALLEGRO_EVENT_KEY_CHAR) {
				if (events.keyboard.unichar >= 32)
					p += al_ustr_append_chr(nickname, events.keyboard.unichar);
				else if (events.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
					if (al_ustr_prev(nickname, &p))
						al_ustr_truncate(nickname, p);
				}
			}
			else if (events.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				if (nickname->slen <= 10) {
					al_ustr_to_buffer(nickname, nick, sizeof(nick));
					break;
				}
				else
					warning_nick();
			}
		}
		al_flip_display();
	}

	if (!if_lost) {
		int diff_lvl = getDiffLvl();
		LoadedData *ptr = loadData(diff_lvl);
		sortScores(ptr, nick, al_get_timer_count(timer));
		saveData(ptr);
	}

	al_ustr_free(nickname);
	al_destroy_display(info_display);
}

