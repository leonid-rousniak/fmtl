#pragma once

#include <ncurses.h>
#include <vector>
#include <algorithm>
#include "Window.h"

class Screen 
{
public:
	Screen();
	~Screen();
	void addWindow(Window&& window);
	inline void forEach(auto lambda) { std::for_each(begin(_windows), end(_windows), lambda); }
	inline size_t size() { return _windows.size(); }

	inline void apply(uint32_t row, auto lambda) // inlined because of the lambda
	{
		if (row >= 0 and row < size()) {
			lambda(_windows[row]);
			refresh();
		}
	}

private:
	//Window _main;
	//Window _child;
	std::vector<Window> _windows;
};
