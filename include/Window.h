#pragma once 

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <cstdint>
#include <tuple>

class Window
{
public:
	using vec2d = std::pair<uint32_t, uint32_t>;

	Window() = delete;
	Window(uint32_t nrow, uint32_t ncol, uint32_t y, uint32_t x);
	Window(const Window& b);
	Window(Window&& b) noexcept;
	Window& operator= (const Window& other);
	Window& operator= (Window&& other) noexcept;
	~Window() noexcept;

	inline void color(uint32_t pairNumber) { wbkgd(_window ,COLOR_PAIR(pairNumber)); wrefresh(_window); }
	inline void print(uint32_t y, uint32_t x, const char* text) { mvwprintw(_window, y, x, text); wrefresh(_window); }
	inline vec2d size() const { return _size; }
	inline vec2d pos() const { return _pos; }
	void move(uint32_t y, uint32_t x); 

private:
	WINDOW* _window;
	vec2d _size;
	vec2d _pos;
};
