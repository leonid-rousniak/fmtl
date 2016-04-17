#pragma once
 
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <stdexcept>

class CurlWrap
{
public:
	CurlWrap();
	~CurlWrap();
	void perform(std::string url);

private:
	CURL* _curl;
};
