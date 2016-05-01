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


std::string curlQuery(std::string url)
{
	curl_global_init(CURL_GLOBAL_ALL);
	curlHandle = curl_easy_init();
	if (!curlHandle)
		throw std::runtime_error("Was not able to init curl");

	curl_easy_setopt(curlHandle, CURLOPT_URL, url);

	std::string data;
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION,
			[&data] (char* buf, size_t size, size_t nmemb, void* up) 
			{
				for (uint32_t i = 0; i < size*nmemb; ++i)
					data.push_back(buf[i]);

				return size*nmemb; //tell curl how many bytes we handled
			});

	CURLcode res = curl_easy_perform(curlHandle);

	if( res != CURLE_OK)
		throw std::runtime_error("curl_easy_perform() failed: invalid url\n");

}	

} // namespace fmtl
