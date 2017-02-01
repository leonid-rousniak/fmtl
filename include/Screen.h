#pragma once

#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>
#include "Window.h"
#include "fmtl.h"

class Screen 
{
public:
	Screen() = delete;
	Screen(const std::vector<std::string>& tickers);
	~Screen();
	void addWindow(Window&& window) { _windows.push_back(window); }
	size_t size() const { return _windows.size(); }
	void update(bool updateData = true);
	void refreshWindows();
	void refreshCentral(uint32_t index);
	void newsFeed();
	std::string getInfo(uint32_t index, std::string tag) const { return (*_dataTable)[index][tag]; }
	Window::vec2d getScreenSize() const;
	void insert();
	void remove();
	void moveUp();
	void moveDown();

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
	Window _newsBar;
	std::vector<Window> _windows;
	std::unique_ptr<fmtl::Table> _dataTable;
	std::vector<std::string> _tickers;
	uint32_t _activeRow = 0;
};
