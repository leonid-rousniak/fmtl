#pragma once
 
#include <curl/curl.h>
#include <stdexcept> 
#include <string>

class CurlWrap
{
public:
	CurlWrap();
	~CurlWrap();
	void perform(const char* url);

private:
	CURL* _curl;
};
