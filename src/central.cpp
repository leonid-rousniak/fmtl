#include "central.h"
#include "ascii.h"

namespace central
{

std::vector<YahooRow> tokenize(const std::string& str)
{
	std::vector<std::string> fields = {
		"ticker",
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
	centralWin.print(10,0,"avg volume:");
	centralWin.print(10,15,yahooRow["avgVolume"].c_str());
}

} // namespace central
