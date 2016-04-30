#include "Window.h"

Window::Window(uint32_t nrow, uint32_t ncol, uint32_t y, uint32_t x)
{
	_window = newwin(nrow,ncol,y,x);
	getmaxyx(_window, _nrow, _ncol);
	getbegyx(_window, _y, _x);
	std::cout << "Window is constructed!" << std::endl;
}

Window::Window(const Window& other)
{
	std::cout << "Copy constructor!" << std::endl;
	uint32_t nrow, ncol, y, x; 
	other.size(nrow,ncol);
	other.beg(y,x);

    // allocate new memory and copy the elements
    WINDOW* new_window = newwin(nrow,ncol,y,x);
	overlay(other._window, new_window);

    //Then copy the value from the passed object
	_window = new_window;
}

Window& Window::operator= (const Window& other)
{
    if (this != &other) // protect against invalid self-assignment
    {
		// get window size and beginning coordinates
		uint32_t nrow, ncol, y, x; 
		other.size(nrow,ncol);
		other.beg(y,x);

        // allocate new memory and copy the elements
        WINDOW* new_window = newwin(nrow,ncol,y,x);
		overlay(other._window, new_window);

        // deallocate old memory
		delwin(_window);

        // assign the new memory to the object
        _window = new_window;
    }
	std::cout << "assignment operator" << std::endl;

    return *this;
}

Window::~Window()
{
	delwin(_window);
	std::cout << "Window is destroyed!" << std::endl;
}


void Window::move(uint32_t y, uint32_t x) 
{ 
	mvwin(_window, _y+y, _x+x); 
	_y = _y+y;
	_x = _x+x;
}
