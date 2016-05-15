#include "Window.h"

/* Constructor, default is deleted */
Window::Window(uint32_t nrow, uint32_t ncol, uint32_t y, uint32_t x)
	: _window(newwin(nrow, ncol, y, x)),
	  _size(std::pair<uint32_t, uint32_t> (nrow, ncol)),
	  _pos(std::pair<uint32_t, uint32_t> (y, x)) {}

/* Copy constructor */
Window::Window(const Window& other)
	: _window(newwin(other._size.first,other._size.second,other._pos.first,other._pos.second)), 
	  _size(other._size), 
	  _pos(other._pos) {}

/* Move constructor */
Window::Window (Window&& other) noexcept
	: _window(other._window),
	  _size(other._size),
	  _pos(other._pos)
{
	other._window = nullptr;
}

/* Copy assignment operator */
Window& Window::operator= (const Window& other)
{
    if (this != &other) { // protect against invalid self-assignment
		Window tmp(other);
		*this = std::move(tmp);
    }

	else 
		std::cout << "Self-assignment !!?" << std::endl;

    return *this;
}

/* Move assignment operator */
Window& Window::operator= (Window&& other) noexcept
{
	delwin(_window);
	_window = other._window;
	other._window = nullptr;
	return *this;
}

/* Destructor */
Window::~Window() noexcept
{
	wclear(_window);
	wrefresh(_window);	
	delwin(_window);
}


void Window::move(uint32_t y, uint32_t x) 
{ 
	uint32_t newy = y + _pos.first;
	uint32_t newx = x + _pos.second;
	mvwin(_window, newy, newx); 
	_pos.first = newy;
	_pos.second = newx;
	wrefresh(_window);
}
