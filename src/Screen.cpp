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

	_centralWindow = Window(23,55,0,25);
	_centralWindow.color(3);

	Window::vec2d currentSize = getScreenSize();
	_commandLine = Window(1,80,currentSize.first-1,0);
	_commandLine.color(1);
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
	
Window::vec2d Screen::getScreenSize()
{
	uint32_t row, col;
	getmaxyx(stdscr,row,col);
	return std::make_pair(row,col); 
}

void Screen::insert(uint32_t index)
{
	std::string message("Insert ticker:");
	_commandLine.print(0,0,message.c_str());

	std::string ticker;
	int ch;
	while((ch = getch()) != '\n') {	
		switch(ch) {
			case KEY_BACKSPACE:
				if (not ticker.empty()) {
					ticker.pop_back();
					_commandLine.clear();
					_commandLine.print(0,0,message.c_str());
					_commandLine.print(0,14,ticker.c_str());
				}
				break;

			default:
				ticker += ch;
				_commandLine.clear();
				_commandLine.print(0,0,message.c_str());
				_commandLine.print(0,14,ticker.c_str());
				break;
		}
	}
	_commandLine.clear();
	_commandLine.refresh();
}
