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
	Window win1(5,5,5,5);
	win1.color(2);
	win1.refresh();

	while((ch = getch()) != KEY_BACKSPACE)
	{	switch(ch)
		{	case KEY_LEFT:
				win1.move(0,-1);
				win1.refresh();
				break;
			case KEY_RIGHT:
				win1.move(0,1);
				win1.refresh();
				break;
			case KEY_UP:
				win1.move(-1,0);
				win1.refresh();
				break;
			case KEY_DOWN:
				win1.move(1,0);
				win1.refresh();
				break;	
		}
	}

	return 0;
}
