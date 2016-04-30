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

	getch();
	for (uint32_t i = 0; i < 5; ++i)
		screen.addWindow(Window(5,5,5*i,5*i));

	while((ch = getch()) != KEY_BACKSPACE) {	
		screen.forEach([] (Window& win) { win.color(2); });
					
	}

	return 0;
}
