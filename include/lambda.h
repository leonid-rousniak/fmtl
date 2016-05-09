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


template <typename Function, typename... Args>
class Generator
{
public:
	Generator() = delete;
    Generator(const Function& f, const Args&... args) : _function(f), _args(std::make_tuple((args)...)) {}
    Generator(Function&& f, Args&&... args) : _function(f), _args(std::make_tuple(std::forward<Args>(args)...)) {}
     
    template <typename... Ts, std::size_t... Is>
    void caller(std::tuple<Ts...>& tup, compiletime::index<Is...>)
    {
        _function(std::get<Is>(tup)...);
    }
     
    template <typename... Ts>
    void caller(std::tuple<Ts...>& tup)
    {
        caller(tup, compiletime::sequence<sizeof...(Ts)>{});
    }
     
    void call() { caller(_args); }

private:
    Function _function;
    std::tuple<Args...> _args;
};

template <typename Function, typename... Args>
Generator<Function,Args...> make_generator(const Function& f, const Args&... args)
{
    return Generator<Function,Args...>(f, (args)...);
}

template <typename Function, typename... Args>
Generator<Function,Args...> make_generator(Function&& f, Args&&... args)
{
    return Generator<Function,Args...>(std::forward<Function>(f), std::forward<Args>(args)...);
}

template <typename Input, typename Function, typename T>
void for_each(Input& input, Function f, const T& param)
{
	static_assert(input.size() == param.size(), "Containers must have the same size!");
	//for (uint32_t i = 0; i < input.size(); ++i)
	//	f(input[i],	
}

inline auto color(uint32_t nb)
{
	return [=] (Window& win) { win.color(nb); };
}

} // namespace lambda

