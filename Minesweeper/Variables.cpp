#include "headers/variables.h"

ALLEGRO_DISPLAY *main_display, *info_display;
ALLEGRO_BITMAP *image, *square;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_FONT *title_font, *menu_font, *info_font, *nbr_font;
ALLEGRO_USTR *input_X, *input_Y, *input_mines, *nickname;
ALLEGRO_TIMER *timer;
ALLEGRO_COLOR darkBlue, lightBlue, infoColor;
ALLEGRO_EVENT events;