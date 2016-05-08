#include "Screen.h"
#include <iostream>

Screen::Screen()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();

	// Check if terminal supports color
	if( has_colors() == false )
	{	
		endwin();
		std::cout << "Your terminal does not support color" << std::endl;
		exit(1);
	}

	start_color();
	init_pair(1,COLOR_BLUE,COLOR_YELLOW);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_BLUE,COLOR_WHITE);
}

Screen::~Screen()
{
 	endwin();
}


