#include <iterator>
#include <iostream>
#include "Screen.h"
#include "fmtl.h"


int main(int argc, char* argv[])
{

	std::vector<std::string> tickers = {"F", "AAPL", "GOOG", "MSFT"};
	Screen screen;

	screen.setDataStream(fmtl::tokenize(fmtl::retrieveData(tickers)));

	uint32_t row = 0;
	screen.apply([] (auto& win) { win.color(3); }, row);


	int ch;
	while((ch = getch()) != KEY_BACKSPACE) {	
		switch(ch)
		{	
			case KEY_UP:
				if (row == 0)
					break;

				screen.apply([] (Window& win) { win.color(2); }, row);
				--row;
				screen.apply([] (Window& win) { win.color(3); }, row);
				screen.refreshCentral(row);
				break;

			case KEY_DOWN:
				if (row >= screen.size()-1) 
					break;

				screen.apply([] (Window& win) { win.color(2); }, row);
				++row;
				screen.apply([] (Window& win) { win.color(3); }, row);
				screen.refreshCentral(row);
				break;	
			
			case 'r':
				//screen.update(fmtl::tokenize(fmtl::retrieveData(tickers)));
				break;

			case 'i':
				screen.insert(row);
				break;

			case 'a':
				screen.forEach([] (Window& win) {
					win.clear();
					win.color(2);
					win.print(1,0,"Updated!"); 
				});
				screen.apply([] (Window& win) { win.color(3); }, row);
				break;
		}
	}
	
	return 0;
}
