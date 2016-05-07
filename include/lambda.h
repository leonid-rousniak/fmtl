#pragma once

/* lambdaList is a facilty to use void lambdas sequentially */
template <typename... Fs>
auto lambdaList(Fs... fs) { 
    using swallow = int [];
    return [=](auto&... args) {
		(void)swallow{0,
			(void(fs(args...)), 0)...};
	};
}

