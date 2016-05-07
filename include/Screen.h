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
	void addWindow(Window&& window);
	inline size_t size() { return _windows.size(); }

	template <typename... Fs>
	void forEach(Fs... fs)
	{
		std::for_each(begin(_windows), end(_windows), lambdaList(fs...));
		refresh();
	}

	template <typename... Fs>
	void apply(uint32_t row, Fs... fs)
	{
		if (row >= 0 and row < size()) {
			lambdaList(fs...)(_windows[row]);
			refresh();
		}
	}

private:
	std::vector<Window> _windows;
	Window _central;
};
