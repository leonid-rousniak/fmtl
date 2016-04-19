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
	if( has_colors() == false )
	{	
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
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

	Window window(5,5,0,0);	
 	// Clear ncurses data structures
 	endwin();
	return 0;
}
