#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <curl/curl.h>

/* curl utility functions */
namespace fmtl
{

/* 
 * callback function writes data to a std::ostream,
 * stolen from http://www.cplusplus.com/forum/unices/45878/
 */
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

std::string getUrl(std::vector<std::string> tickers)
{
	std::string urlQuery = "http://download.finance.yahoo.com/d/quotes.csv?";
	
	// parsing ticker symbols
	urlQuery += "s=";
	for (const auto& ticker : tickers) urlQuery += ticker + "+";
	urlQuery.pop_back();

	// adding info options
	urlQuery += "&f=st1nl1c1p2oghjkva2r2rdyj3j1";
	
	return urlQuery;
}

CURLcode curl_read(const std::string& url, std::ostream& os)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if (curl)
	{
		if (CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}

} // namespace fmtl
