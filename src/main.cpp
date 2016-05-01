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

	for (uint32_t i = 0; i < 5; ++i)
		screen.addWindow(Window(2,25,5*i,0));

	screen.forEach([] (Window& win) { win.color(2); });
	screen.forEach([] (Window& win) { win.print(0,0,"Hello Leonid"); });
	screen.forEach([] (Window& win) { win.print(1,0,"Second line"); });
	screen.apply(0, [] (Window& win) { win.color(3); });

	uint32_t row = 0;

	while((ch = getch()) != KEY_BACKSPACE) {	
		switch(ch)
		{	
			case KEY_UP:
				if (row == 0)
					break;

				screen.apply(row, [] (Window& win) { win.color(2); });
				--row;
				screen.apply(row, [] (Window& win) { win.color(3); });
				break;

			case KEY_DOWN:
				if (row >= screen.size()-1) 
					break;

				screen.apply(row, [] (Window& win) { win.color(2); });
				++row;
				screen.apply(row, [] (Window& win) { win.color(3); });
				break;	
		}
	}

	return 0;
}
