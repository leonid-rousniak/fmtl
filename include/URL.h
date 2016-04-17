#pragma once

#include <string>

class URL
{
public:
	URL() : _prefix("http://download.finance.yahoo.com/d/quotes.csv?") {}
	URL(std::string prefix) : _prefix(prefix) {}
	
private:
	std::string _prefix;
};
