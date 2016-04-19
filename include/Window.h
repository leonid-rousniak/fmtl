#pragma once 

#include <vector>
#include <ncurses.h>

class Window
{
public:
	Window(int nrow, int ncol, int y, int x);
	~Window();
	inline void color(int pairNumber) { wbkgd(_window ,COLOR_PAIR(pairNumber)); }
	inline void print(char* text) { wprintw(_window, text); }
	inline void refresh() { wrefresh(_window); }
	inline WINDOW* getPtr() { return _window; }

private:
	WINDOW* _window;
};
