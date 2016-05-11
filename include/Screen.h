#pragma once

#include <ncurses.h>
#include <vector>
#include <algorithm>
#include "Window.h"
#include "lambda.h"

class Screen 
{
public:
	Screen();
	~Screen();
	inline void addWindow(Window&& window) { _windows.push_back(window); }
	inline size_t size() { return _windows.size(); }

	template <typename... Fs>
	void forEach(Fs... fs)
	{
		std::for_each(begin(_windows), end(_windows), lambda::Chain(fs...));
		refresh();
	}

	template <typename... Fs>
	void apply(uint32_t row, Fs... fs)
	{
		if (row >= 0 and row < size()) {
			lambda::Chain(fs...)(_windows[row]);
			refresh();
		}
	}

private:
	std::vector<Window> _windows;
};
