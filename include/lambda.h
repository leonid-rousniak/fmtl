#pragma once

#include "Window.h"

namespace lambda 
{

/* lambdaList is a facilty to use void lambdas sequentially */
template <typename... Fs>
auto List(Fs... fs) { 
    using swallow = int [];
    return [=](auto&... args) {
		(void)swallow{0,
			(void(fs(args...)), 0)...};
	};
}

inline auto color(uint32_t nb)
{
	return [=] (Window& win) { win.color(nb); };
}

} // namespace lambda

