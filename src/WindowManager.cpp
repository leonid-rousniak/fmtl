#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();

	// Check if terminal supports color
	if( has_colors() == false )
	{	
		endwin();
		std::cout << "Your terminal does not support color" << std::endl;
		exit(1);
	}

	start_color();
	init_pair(1,COLOR_YELLOW,COLOR_BLUE);
	init_pair(2,COLOR_BLUE,COLOR_RED);
	init_pair(3,COLOR_BLUE,COLOR_WHITE);
}

WindowManager::~WindowManager()
{
 	endwin();
}

void WindowManager::setup(int nTickers)
{
	std::cout << "Setup!" << std::endl;
	_wTickers.reserve(nTickers);
	_wPrices.reserve(nTickers);

	//Total screen size is 24x80
	for (int i=0; i < nTickers; ++i)
	{
		_wTickers[i] = Window(2*i,0,1);
		_wPrices[i] = Window(2*i,12,2);
		std::cout << "hi" << std::endl;
	}

	_main = Window(0,28,3);
}
