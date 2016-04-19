#include "Window.h"

Window::Window(int nrow, int ncol, int y, int x)
{
	_window = newwin(nrow,ncol,y,x);
}

Window::~Window()
{
	delwin(_window);
}
