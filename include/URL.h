#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class URL
{
public:
	using Tickers = std::vector<std::string>;

	URL(Tickers tickers, bool l1, bool c6, bool k2);
	std::string get(); 	

private:
	std::string _prefix = "http://download.finance.yahoo.com/d/quotes.csv?";
	Tickers _tickers;
	std::unordered_map<std::string, bool> _info;
};
