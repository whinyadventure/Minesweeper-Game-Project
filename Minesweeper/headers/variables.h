#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#define screen_width 1200
#define screen_height 880
#define MINESWEEPER_X screen_width / 2
#define MINESWEEPER_Y screen_height / 4
#define SQUARE_SIZE 30

extern ALLEGRO_DISPLAY *main_display, *info_display;
extern ALLEGRO_BITMAP *image, *square;
extern ALLEGRO_MOUSE_STATE state;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT *title_font, *menu_font, *info_font, *nbr_font;
extern ALLEGRO_USTR *input_X, *input_Y, *input_mines, *nickname;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_COLOR darkBlue, lightBlue, infoColor;
extern ALLEGRO_EVENT events;