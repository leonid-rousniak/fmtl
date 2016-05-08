#include "stream.h"
#include "ascii.h"

namespace stream
{

std::vector<YahooRow> tokenize(std::string str)
{
	std::vector<std::string> fields = {
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
	std::vector<YahooRow> table;

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


void update(Window& centralWin, YahooRow& yahooRow)
{
	centralWin.print(0,0,ascii::generator(yahooRow["ticker"]).c_str());
	centralWin.print(5,0,ascii::generator(yahooRow["lastTrade"]).c_str());
	centralWin.print(10,0,yahooRow["name"].c_str());
	centralWin.print(11,0,"avg volume:");
	centralWin.print(11,15,yahooRow["avgVolume"].c_str());
}

} // namespace stream 