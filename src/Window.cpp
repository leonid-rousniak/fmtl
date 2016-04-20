#include "Window.h"

Window::Window(int y, int x, int category)
{
	switch(category)
	{
		case 1: _window = newwin(2,12,y,x);
		case 2: _window = newwin(2,16,y,x);
		case 3: _window = newwin(24,52,y,x); 
	}
	std::cout << "Constructor is used!" << std::endl;
}

Window::Window(const Window& other)
{
	int nrow, ncol, y, x; 
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
		int nrow, ncol, y, x; 
		other.size(nrow,ncol);
		other.beg(y,x);

        // allocate new memory and copy the elements
        WINDOW* new_window = newwin(nrow,ncol,y,x);
		overlay(other._window, new_window);

        // deallocate old memory
		delwin(_window);

        // assign the new memory to the object
        _window = new_window;
		_focused = other._focused;
    }
	std::cout << "assignment constructor" << std::endl;
    // by convention, always return *this
    return *this;
}

Window::~Window()
{
	delwin(_window);
}
