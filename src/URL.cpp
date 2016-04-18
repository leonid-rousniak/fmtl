#include "URL.h"
#include <iostream>

URL::URL(Tickers tickers, bool l1, bool c1, bool p2)
	: _tickers(tickers)
{
	_info["l1"] = l1;
	_info["c1"] = c1;
	_info["p2"] = p2;
}


std::string URL::get()
{
	std::string urlQuery = _prefix;
	
	// parsing ticker symbols
	urlQuery += "s=";
	for (const auto& s : _tickers) urlQuery += s + "+";
	urlQuery.pop_back();

	// parsing info options
	urlQuery += "&f=";
	for (const auto& option : _info) 
	{
		if (option.second)
			urlQuery += option.first;
	}
	
	return urlQuery;
}
