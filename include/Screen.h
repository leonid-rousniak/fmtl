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
	void setup(int nTickers);
	inline void forEachW1(auto lambda) { std::for_each(begin(_wTickers), end(_wTickers), lambda); }

private:
	Window _main;
	std::vector<Window> _wTickers;
	std::vector<Window> _wPrices;
};
