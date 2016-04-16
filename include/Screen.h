#pragma once

#include "termbox.h"
#include <cstdint>

class Screen
{
public:
	Screen();	

private:
	uint32_t _width;
	uint32_t _height;
	bool _cleared;
	//*Layout _layout;
	//*Markup _markup;
};
