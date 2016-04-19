#include <iterator>
#include <iostream>
#include "CurlWrap.h"
#include "fmtl.h"
#include "Window.h"

void ncursesInit()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();

	// Check if terminal supports color
	if( has_colors() == false )
	{	
		endwin();
		std::cout << "Your terminal does not support color" << std::endl;
		exit(1);
	}

	start_color();
	init_pair(1,COLOR_YELLOW,COLOR_BLUE);
	init_pair(2,COLOR_BLUE,COLOR_RED);
	init_pair(3,COLOR_BLUE,COLOR_WHITE); 
}

int main(int argc, char* argv[])
{
	try 
	{
	
	std::vector<char*> tickers(argv+1, argv + argc);
	
	// Get the query for Yahoo API
	std::string url = fmtl::getUrl(tickers);	

	CurlWrap curl;
	curl.perform(url.c_str());
	
	} // try  

	catch (const std::runtime_error& e) // catch runtime exceptions
	{
		std::cerr << e.what();
	}

	ncursesInit(); 

	Window window(12,40,13,0);	
	window.color(1);
	window.print((char *) "Hello world");
	window.refresh();
	wgetch(window.getPtr());

 	// Clear ncurses data structures
 	endwin();
	return 0;
}
