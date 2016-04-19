#pragma once

#include <vector>
#include <string>

// Generic free functions
namespace fmtl
{

std::string getUrl(std::vector<char*> tickers)
{
	std::string urlQuery = "http://download.finance.yahoo.com/d/quotes.csv?";
	
	// parsing ticker symbols
	urlQuery += "s=";
	for (const auto& s : tickers) urlQuery += std::string(s) + "+";
	urlQuery.pop_back();

	// adding info options
	urlQuery += "&f=sl1c1p2oghjkva2r2rdyj3j1";
	
	return urlQuery;
}

} // namespace fmtl
