#pragma once 

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <cstdint>

class Window
{
public:
	Window() = delete;
	Window(uint32_t nrow, uint32_t ncol, uint32_t y, uint32_t x);
	Window& operator= (const Window& other);
	Window(const Window& b);
	~Window();
	inline void color(uint32_t pairNumber) { wbkgd(_window ,COLOR_PAIR(pairNumber)); }
	inline void print(char* text) { wprintw(_window, text); }
	inline void refresh() { wrefresh(_window); }
	inline void size(uint32_t& y, uint32_t& x) const { getmaxyx(_window,y,x); }
	inline void beg(uint32_t& y, uint32_t& x) const { getbegyx(_window,y,x); }
	void move(uint32_t y, uint32_t x); 
	inline WINDOW* getPtr() { return _window; }

private:
	WINDOW* _window;
	uint32_t _nrow;
	uint32_t _ncol;	
	uint32_t _y;
	uint32_t _x;
};
