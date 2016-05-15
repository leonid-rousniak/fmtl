#include <iterator>
#include <iostream>
#include "Screen.h"
#include "fmtl.h"

void foo2(int a) { std::cout << a << std::endl; }

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);	
	std::ostringstream oss;

	std::string csvStr;
	std::vector<std::string> tickers = {"AAPL", "GOOG", "MSFT"};
	std::string url = fmtl::getUrl(tickers);
	if (CURLE_OK == fmtl::curl_read(url, oss)) {
		csvStr = oss.str();
	}

	curl_global_cleanup();

	Screen screen;

	screen.setDataStream(fmtl::tokenize(csvStr));

	uint32_t row = 0;
	screen.apply([] (auto& win) { win.color(3); }, row);


	uint32_t ch;
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
