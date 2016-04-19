#pragma once 

#include <vector>
#include <ncurses.h>

class Window
{
public:
	Window(int nrow, int ncol, int y, int x);
	~Window();

private:
	WINDOW* _window;
};
