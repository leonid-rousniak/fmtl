#pragma once 

#include <vector>
#include <ncurses.h>
#include <iostream>

// Category 1 is for ticker and date, 2 is for last trade and % change,
// 3 is for the main window
class Window
{
public:
	Window() { std::cout << "default constructor" << std::endl; }
	Window(int y, int x, int category);
	Window& operator= (const Window& other);
	Window(const Window& b);
	~Window();
	inline void color(int pairNumber) { wbkgd(_window ,COLOR_PAIR(pairNumber)); }
	inline void print(char* text) { wprintw(_window, text); }
	inline void refresh() { wrefresh(_window); }
	inline void size(int& y, int& x) const { getmaxyx(_window,y,x); }
	inline void beg(int& y, int& x) const { getbegyx(_window,y,x); }
	inline WINDOW* getPtr() { return _window; }

private:
	WINDOW* _window;
	bool _focused = false;
};
