#include <iterator>
#include <iostream>
#include "Screen.h"
#include "fmtl.h"


int main(int argc, char* argv[])
{
	std::vector<std::string> tickers = {"F", "AAPL", "GOOG", "MSFT"};
	Screen screen(tickers);
	screen.update();

	std::thread t(fmtl::newsFeed);

	int ch;
	while((ch = getch()) != KEY_BACKSPACE) {	
		switch(ch)
		{	
			case KEY_UP:
				screen.moveUp();
				break;

			case KEY_DOWN:
				screen.moveDown();
				break;	
			
			case 'r':
				screen.update();
				break;

			case 'i':
				screen.insert();
				break;

			case 'd':
				screen.remove();
				break;
		}
	}
	t.join();
	return 0;
}
