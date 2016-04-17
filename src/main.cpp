#include "CurlWrap.h"
#include "URL.h"
#include <tclap/CmdLine.h>

int main(int argc, char* argv[])
{
	try 
	{
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	TCLAP::ValueArg<std::string> quoteArg("q","quote","Symbol corresponding to the quote",true,"homer","string");
	cmd.add(quoteArg);
	cmd.parse(argc, argv);
	std::string quote = quoteArg.getValue();
	
	CurlWrap curl;
	curl.perform("http://download.finance.yahoo.com/d/quotes.csv?s="+quote+"&f=l1");
	} 

	catch (const std::runtime_error& e) // catch runtime exceptions
	{
		std::cerr << e.what();
	}
	catch (TCLAP::ArgException &e)  // catch tclap exceptions 
	{ 
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
	}
	return 0;
}
