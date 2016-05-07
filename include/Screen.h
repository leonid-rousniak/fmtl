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
		auto composed = lambdaList(fs...);
		std::for_each(begin(_windows), end(_windows), composed); 
	}

	inline void apply(uint32_t row, auto lambda) // inlined because of the lambda
	{
		if (row >= 0 and row < size()) {
			lambda(_windows[row]);
			refresh();
		}
	}

private:
	std::vector<Window> _windows;
};
