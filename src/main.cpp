#include <iterator>
#include <iostream>
#include "CurlWrap.h"
#include "fmtl.h"
#include "Window.h"
#include "Screen.h"


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

	Screen screen;
	Window window(12,40,13,0);	
	window.color(1);
	window.print((char *) "Hello world");
	window.refresh();
	wgetch(window.getPtr());

 	// Clear ncurses data structures
	return 0;
}
