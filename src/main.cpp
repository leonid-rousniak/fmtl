#include <iterator>
#include <iostream>
#include "Screen.h"
#include "fmtl.h"
#include "stream.h"

void foo(int x, float y, double z)
{
	std::cout << x + y + z << std::endl;
}

void foo2(int& a, int b) { a+=b; }

int main(int argc, char* argv[])
{
	auto generator = lambda::make_generator([] (int a, int b) { std::cout << a + b << std::endl; }, 3, 7);
	auto generator2 = lambda::make_generator(foo, 3,7,8);
	generator.yield();
	generator2.yield();

	auto data = lambda::list(2,3,"leonid");
	lambda::print(data);
	//auto data = lambda::list_leonid('f',3.5,1,3.0);
	//lambda::print(data);
	//lambda::DataList<int, const char*>(1,"lalala");	

	curl_global_init(CURL_GLOBAL_ALL);	
	std::ostringstream oss;

	std::string csvStr;
	std::vector<std::string> tickers = {"AAPL", "GOOG"};
	std::string url = fmtl::getUrl(tickers);
	if (CURLE_OK == fmtl::curl_read(url, oss)) {
		csvStr = oss.str();
	}

	curl_global_cleanup();

	std::vector<stream::YahooRow> table = stream::tokenize(csvStr);
	
	Screen screen;

	for (uint32_t i = 0; i < 2; ++i)
		screen.addWindow(Window(2,25,2*i,0));


	screen.forEach(
		[&table] (auto& win) {
			win.print(0, 0, table[0]["ticker"].c_str());
			std::string time = table[0]["time"] + " EDT";
			win.print(1, 0, time.c_str()); 
		},
		[&table] (auto& win) { win.color(2); });

	uint32_t row = 0;
	screen.apply(row, lambda::color(3)); 

	Window centralWin(25,55,0,25);
	centralWin.color(3);
	stream::update(centralWin,table[0]);

	uint32_t ch;
	while((ch = getch()) != KEY_BACKSPACE) {	
		switch(ch)
		{	
			case KEY_UP:
				if (row == 0)
					break;

				screen.apply(row, [] (Window& win) { win.color(2); });
				--row;
				screen.apply(row, [] (Window& win) { win.color(3); });
				stream::update(centralWin,table[row]);
				break;

			case KEY_DOWN:
				if (row >= screen.size()-1) 
					break;

				screen.apply(row, [] (Window& win) { win.color(2); });
				++row;
				screen.apply(row, [] (Window& win) { win.color(3); });
				stream::update(centralWin,table[row]);
				break;	

			case 'a':
				screen.forEach([] (Window& win) {
					win.clear();
					win.color(2);
					win.print(1,0,"Updated!"); 
				});
				screen.apply(row, [] (Window& win) { win.color(3); });
				break;
		}
	}
	
	return 0;
}
