#include "Screen.h"
#include "ascii.h"

Screen::Screen() : _dataTable(std::make_unique<fmtl::Table>())
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

	_centralWindow = Window(25,55,0,25);
	_centralWindow.color(3);
}

Screen::~Screen()
{
 	endwin();
}

void Screen::setDataStream(const fmtl::Table& table)
{
	*_dataTable = table;
	refreshCentral(0);
	
	// Add all the windows on the left side
	for (uint32_t i = 0; i < table.size(); ++i) {
		addWindow(Window(2,25,2*i,0));
		_windows[i].print(0, 0, getInfo(i,"ticker").c_str());
		_windows[i].print(1, 0, (getInfo(i,"time") + std::string(" EDT")).c_str()); 
	}
}

void Screen::refreshCentral(uint32_t index)
{
	_centralWindow.clear();
	_centralWindow.print(0,0,ascii::generator(getInfo(index,"ticker")).c_str());
	_centralWindow.print(5,0,ascii::generator(getInfo(index,"lastTrade")).c_str());
	_centralWindow.print(10,0,getInfo(index,"name").c_str());
	_centralWindow.print(11,0,"avg volume:");
	_centralWindow.print(11,15,getInfo(index,"avgVolume").c_str());
}
