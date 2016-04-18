#include "CurlWrap.h"
#include "URL.h"
#include <tclap/CmdLine.h>

int main(int argc, char* argv[])
{
	try 
	{
	
	// Parse command-line arguments with tclap
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	TCLAP::MultiArg<std::string> tickerArg("t","tickers","Symbols corresponding to the tickers", false, "string");
	cmd.add(tickerArg);
	TCLAP::SwitchArg l1Switch("l","last","last trade.", cmd, false);
	TCLAP::SwitchArg c1Switch("c","change","change real time", cmd, false);
	TCLAP::SwitchArg p2Switch("p","percent","percent change real time", cmd, false);

	cmd.parse(argc, argv);
	std::vector<std::string> tickers = tickerArg.getValue();
	
	// Get the query for Yahoo API
	URL url(tickers, l1Switch.getValue(), c1Switch.getValue(), p2Switch.getValue());		

	CurlWrap curl;
	curl.perform(url.get());
	
	} // try  


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
