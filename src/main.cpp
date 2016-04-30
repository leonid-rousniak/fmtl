#include <iterator>
#include <iostream>
#include "CurlWrap.h"
#include "fmtl.h"
#include "Screen.h"


int main(int argc, char* argv[])
{
	/*try 
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
	}*/
	uint32_t ch;
	Screen screen;
	std::vector<Window> windows;
	windows.reserve(2);
	windows[0] = Window(5,5,5,5);
	windows[0].color(2);
	windows[0].refresh();
	windows[1] = Window(5,5,10,10);
	windows[1].color(2);
	windows[1].refresh();

	while((ch = getch()) != KEY_BACKSPACE) {	


	}

	return 0;
}
