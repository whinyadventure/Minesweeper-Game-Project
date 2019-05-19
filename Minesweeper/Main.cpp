#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/variables.h"
#include "headers/mainMenu.h"

using namespace std;

int main() {
	srand(time(NULL));
	bool check;

	check = initializations();
	if (!check)
		return -1;

	check = createMainDisplay();
	if (!check)
		return -1;

	menuLoop();
		
	al_destroy_font(title_font);
	al_destroy_font(menu_font);
	al_destroy_font(info_font);
	al_destroy_font(nbr_font);
	al_destroy_display(main_display);
	al_destroy_bitmap(image);
	al_destroy_bitmap(square);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}
