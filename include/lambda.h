#pragma once

#include <tuple>
#include <array>
#include "Window.h"

namespace compiletime
{
    template <std::size_t... Ts>
    struct index {};
    
    template <std::size_t N, std::size_t... Ts>
    struct sequence: sequence<N - 1, N - 1, Ts...> {};
    
    template <std::size_t... Ts>
    struct sequence<0, Ts...> : index<Ts...> {};
}

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

template <typename Input, typename Function, typename T>
void for_each(Input& input, Function f, const T& param)
{
	static_assert(input.size() == param.size(), "Containers must have the same size!");
	
}

inline auto color(uint32_t nb)
{
	return [=] (Window& win) { win.color(nb); };
}

} // namespace lambda

