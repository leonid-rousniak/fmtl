#include <iterator>
#include <iostream>
#include "CurlWrap.h"
#include "fmtl.h"
#include "WindowManager.h"


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

	WindowManager screen;
	screen.setup(5);
	screen.forEachW1([] (Window win) { win.color(2); });
	Window window(13,0,1);	
	window.color(2);
	window.refresh();
	wgetch(window.getPtr());

	return 0;
}
