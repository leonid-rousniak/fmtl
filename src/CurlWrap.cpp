#include "CurlWrap.h"

CurlWrap::CurlWrap() 
{
	_curl = curl_easy_init();
	if( !_curl )
		throw std::runtime_error("Was not able to init curl");
}

CurlWrap::~CurlWrap()
{
	curl_easy_cleanup(_curl); 
}

void CurlWrap::perform(std::string url)
{
	curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
	CURLcode res = curl_easy_perform(_curl);

	if( res != CURLE_OK)
		throw std::runtime_error("curl_easy_perform() failed: invalid url\n");
}
