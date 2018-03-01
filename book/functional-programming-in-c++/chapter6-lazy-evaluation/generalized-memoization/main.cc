// ml:std = gnu++17
// ml:run = time -p $bin
#include <iostream>
#include <map>
#include <tuple>

template <class Result, class... Args>
auto make_memorized(Result (*f)(Args...))
{
    std::map<std::tuple<Args...>, Result> cache;

    return [f, cache](Args... args) mutable {
        auto const args_tuple = std::make_tuple(args...);
        auto const cached = cache.find(args_tuple);

        if (cached == cache.end()) {
            auto result = f(args...);
            cache[args_tuple] = result;
            return result;
        } else {
            return cached->second;
        }
    };
}

int fib(int n)
{
    return n <= 1
        ? n
        : fib(n - 1) + fib(n - 2);
}

int main()
{
    auto mem = make_memorized(fib);
    std::cout << mem(42) << "\n";
    std::cout << mem(42) << "\n";
}

