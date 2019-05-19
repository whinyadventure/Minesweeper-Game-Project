#include "headers/variables.h"
#include "headers/highScores.h"
#include "headers/mainMenu.h"
#include "headers/newGame.h"
#include "headers/board.h"

bool initializations() {
	if (!al_init()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to initialize Allegro5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to initialize Allegro5's image addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_font_addon()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to initialize Allegro5's font addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_ttf_addon()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to initialize Allegro5's ttf addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to initialize Allegro5's primitives addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to install mouse!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_keyboard()) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to install keyboard!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	return true;
}

void setColors() {
	darkBlue = al_map_rgb(32, 41, 98);
	lightBlue = al_map_rgb(41, 137, 187);
	infoColor = al_map_rgb(59, 75, 148);
}

void setFonts() {
	title_font = al_load_font("fonts/Raleway-Regular.ttf", 60, NULL);
	menu_font = al_load_font("fonts/Raleway-Regular.ttf", 30, NULL);
	info_font = al_load_font("fonts/Raleway-Regular.ttf", 25, NULL);
	nbr_font = al_load_font("fonts/Lato-Light.ttf", 30, NULL);
}

void setMainDisplay() {
	al_clear_to_color(darkBlue);
	al_draw_text(title_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y, ALLEGRO_ALIGN_CENTRE, "MINESWEEPER");
	al_draw_text(info_font, infoColor, MINESWEEPER_X, MINESWEEPER_Y + 60, ALLEGRO_ALIGN_CENTRE, "Main menu");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 140, ALLEGRO_ALIGN_CENTRE, "new game");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 200, ALLEGRO_ALIGN_CENTRE, "high scores");
	al_draw_text(menu_font, lightBlue, MINESWEEPER_X, MINESWEEPER_Y + 260, ALLEGRO_ALIGN_CENTRE, "quit");
}

bool createMainDisplay() {
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	main_display = al_create_display(screen_width, screen_height);

	if (!main_display) {
		al_show_native_message_box(al_get_current_display(), "Minesweeper.exe", "Error!", "Failed to create display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	al_set_window_position(main_display, 350, 100);
	setColors();
	setFonts();
	setMainDisplay();
	
	al_flip_display();
	return true;
}

void menuLoop() {
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());

	while (true) {
		setMainDisplay();
		al_wait_for_event(event_queue, &events);
		int mouse_x, mouse_y;

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 130) && (mouse_y <= MINESWEEPER_Y + 185))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 130, MINESWEEPER_X + 125, MINESWEEPER_Y + 185, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 190) && (mouse_y <= MINESWEEPER_Y + 245))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 190, MINESWEEPER_X + 125, MINESWEEPER_Y + 245, lightBlue, 1);
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 250) && (mouse_y <= MINESWEEPER_Y + 305))
				al_draw_rectangle(MINESWEEPER_X - 130, MINESWEEPER_Y + 250, MINESWEEPER_X + 125, MINESWEEPER_Y + 305, lightBlue, 1);
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouse_x = events.mouse.x;
			mouse_y = events.mouse.y;

			if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 130) && (mouse_y <= MINESWEEPER_Y + 185)) {
				newGameLoop();
				al_set_target_backbuffer(main_display);
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 190) && (mouse_y <= MINESWEEPER_Y + 245)) {
				highScoresLoop();
			}
			else if ((mouse_x >= MINESWEEPER_X - 130) && (mouse_x <= MINESWEEPER_X + 125) && (mouse_y >= MINESWEEPER_Y + 250) && (mouse_y <= MINESWEEPER_Y + 305))
				break;
		}
		al_flip_display();
	}
}