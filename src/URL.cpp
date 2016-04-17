#include "URL.h"

URL::URL(Tickers tickers, bool l1, bool c6, bool k2)
	: _tickers(tickers)
{
	_info["l1"] = l1;
	_info["c6"] = c6;
	_info["k2"] = k2;
}


std::string URL::get()
{
	std::string urlQuery = _prefix;
	
	// parsing ticker symbols
	urlQuery += "s=";
	for (const auto& s : _tickers) urlQuery += s;

	// parsing info options
	urlQuery += "&f=";
	for (const auto& option : _info) 
	{
		if (option.second)
			urlQuery += option.first;
	}

	return urlQuery;
}
