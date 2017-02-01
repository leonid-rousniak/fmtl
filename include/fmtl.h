#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <curl/curl.h>
#include "Window.h"

/* utility functions for the program*/
namespace fmtl {

/* 
 * callback function writes data to a std::ostream,
 * stolen from http://www.cplusplus.com/forum/unices/45878/
 */
inline static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if (userp) {
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

inline std::string getUrl(std::vector<std::string> tickers)
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

inline CURLcode curl_read(const std::string& url, std::ostream& os)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if (curl) {
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

inline std::string retrieveData(std::vector<std::string> tickers)
{
	curl_global_init(CURL_GLOBAL_ALL);	
	std::stringstream ss;

	std::string csvStr;
	std::string url = getUrl(tickers);
	if (CURLE_OK == curl_read(url, ss)) {
		csvStr = ss.str();
	}

	curl_global_cleanup();
	return csvStr;
}

inline std::vector<std::string> retrieveNews()
{
	curl_global_init(CURL_GLOBAL_ALL);	
	std::stringstream ss;

	const auto handle = curl_read("http://finance.yahoo.com/rss/topfinstories", ss);
	if (handle != CURLE_OK)
		ss << "Error in getting the news feed";

	curl_global_cleanup();

	std::vector<std::string> newsFeed;
	std::string line;
	while (std::getline(ss, line)) {
		if (line.find("title") != std::string::npos) {
			auto start = line.find(">");
			auto finish = line.substr(start+1).find("<");
			line = line.substr(start+1,finish);
			newsFeed.push_back(line);
		}
	}
	newsFeed.erase(begin(newsFeed),begin(newsFeed)+2);
	return newsFeed;
}

inline void newsFeed()
{
	const std::vector<std::string> newsFeed = fmtl::retrieveNews(); 
	Window newsBar(1,80,22,0);
	newsBar.color(4);
	while (1) {
		for (const auto& feed : newsFeed) {
			newsBar.clear();
			newsBar.print(0,0,feed.c_str());
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	}
}

using YahooRow = std::unordered_map<std::string, std::string>;
using Table = std::vector<YahooRow>;

inline Table tokenize(std::string str)
{
	const std::vector<std::string> fields = {
		"ticker",
		"time",
		"name",
		"lastTrade",
		"change",
		"changePct",
		"open",
		"low",
		"high",
		"low52",
		"high52",
		"volume",
		"avgVolume",
		"peRatioRT",
		"peRatio",
		"dividend",
		"yield",
		"marketCapRT",
		"marketCap"
	};		

	str.erase(std::remove(begin(str), end(str), '\"'), end(str));
	std::stringstream ss(str);
	std::string row;
	Table table;

	while (std::getline(ss, row, '\n')) {
		std::stringstream rowSs(row);
		std::string item;
		YahooRow yahooRow;
		uint32_t index = 0;

		while (std::getline(rowSs, item, ',')) {
			yahooRow[fields[index]] = item;	
			++index;
		}
		table.push_back(yahooRow);
	}

	return table;
}

} // namespace fmtl
