#include <iterator>
#include <iostream>
#include "fmtl.h"
#include "Screen.h"


/* lambdaList is a facilty to use void lambdas sequentially            * 
 * It is useful when used in conjunction with window-specific function */
template <typename... Fs>
auto lambdaList(Fs... fs) { 
    using swallow = int [];
    return [=](auto&... args) {
        (void)swallow{0,
			(void(fs(args...)), 0)...};
    };
}

int main(int argc, char* argv[])
{
	/*
	curl_global_init(CURL_GLOBAL_ALL);	
	std::ostringstream oss;

	std::string csvStr;
	std::vector<std::string> tickers = {"AAPL", "GOOG"};
	std::string url = fmtl::getUrl(tickers);
	if (CURLE_OK == fmtl::curl_read(url, oss)) {
		csvStr = oss.str();
	}

	std::cout << csvStr << std::endl;

	curl_global_cleanup();
	*/
	
	uint32_t ch;
	Screen screen;

	for (uint32_t i = 0; i < 5; ++i)
		screen.addWindow(Window(2,25,5*i,0));

	screen.forEach(lambdaList(fmtl::colorBG, fmtl::printLeonid));
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

			case 'a':
				screen.forEach([] (Window& win) { win.print(1,0,"Updated!"); });
		}
	}
	
	return 0;
}
