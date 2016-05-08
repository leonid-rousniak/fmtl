#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "Window.h"

namespace central 
{

using YahooRow = std::unordered_map<std::string, std::string>;

std::vector<YahooRow> tokenize(const std::string& str);

void update(Window& centralWin, YahooRow& yahooRow);

} // namespace central
