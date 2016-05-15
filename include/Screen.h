#pragma once

#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <memory>
#include "Window.h"
#include "fmtl.h"

class Screen 
{
public:
	Screen();
	~Screen();
	void addWindow(Window&& window) { _windows.push_back(window); }
	size_t size() { return _windows.size(); }
	void setDataStream(const fmtl::Table& table);
	void refreshCentral(uint32_t index);
	std::string getInfo(uint32_t index, std::string tag) { return (*_dataTable)[index][tag]; }
	void update(const fmtl::Table& table);
	Window::vec2d getScreenSize();
	void insert(uint32_t row);


	void forEach(auto f)
	{
		std::for_each(begin(_windows), end(_windows), f);
		refresh();
	}

	void apply(auto f, uint32_t row)
	{
		if (row >= 0 and row < size()) {
			f(_windows[row]);
			refresh();
		}
	}

private:
	Window _centralWindow;
	Window _commandLine;
	std::vector<Window> _windows;
	std::unique_ptr<fmtl::Table> _dataTable;
};
