#include "Screen.h"
#include "ascii.h"

Screen::Screen(const std::vector<std::string>& tickers)
	: _dataTable(std::make_unique<fmtl::Table>()),
	  _tickers(tickers)
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
	init_pair(4,COLOR_BLACK,COLOR_WHITE);

	_centralWindow = Window(22,55,0,25);
	_centralWindow.color(2);

	Window::vec2d currentSize = getScreenSize();
	_commandLine = Window(1,80,currentSize.first-1,0);
	_commandLine.color(2);
}

Screen::~Screen()
{
 	endwin();
}

void Screen::update(bool updateData)
{
	if (updateData)
		*_dataTable = fmtl::tokenize(fmtl::retrieveData(_tickers));
	refreshCentral(_activeRow);
	
	// Add all the windows on the left side
	for (uint32_t i = 0; i < _tickers.size(); ++i) {
		addWindow(Window(2,25,2*i,0));
		_windows[i].print(0, 0, getInfo(i,"ticker").c_str());
		_windows[i].print(1, 0, getInfo(i,"time").c_str()); 
		_windows[i].color(2);
	}
	_windows[_activeRow].color(4);
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

void Screen::moveUp()
{
	if (_activeRow != 0) {
		apply([] (Window& win) { win.color(2); }, _activeRow);
		--_activeRow;
		apply([] (Window& win) { win.color(4); }, _activeRow);
		refreshCentral(_activeRow);
	}
}

void Screen::moveDown()
{
	if (_activeRow < _tickers.size()-1) {
		apply([] (Window& win) { win.color(2); }, _activeRow);
		++_activeRow;
		apply([] (Window& win) { win.color(4); }, _activeRow);
		refreshCentral(_activeRow);
	}
}
	
Window::vec2d Screen::getScreenSize()
{
	uint32_t row, col;
	getmaxyx(stdscr,row,col);
	return std::make_pair(row,col); 
}

void Screen::insert()
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
	auto position = begin(_tickers) + _activeRow;
	_tickers.insert(position,ticker);
	_commandLine.clear();
	_commandLine.refresh();
	_windows.clear();
	update();
}


void Screen::remove()
{
	if (_activeRow == 0 and _tickers.size() == 1)
		return;
	auto posTick = begin(_tickers) + _activeRow;
	_tickers.erase(posTick);
	auto posTable = begin(*_dataTable) + _activeRow;
	(*_dataTable).erase(posTable);
	if (_activeRow == _tickers.size()) {
		_windows[_activeRow].color(2);
		--_activeRow;
	}
	_windows.clear();
	update(false);
}
