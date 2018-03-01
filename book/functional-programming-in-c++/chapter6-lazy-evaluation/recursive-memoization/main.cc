// ml:run = time -p $bin
// ml:std = gnu++14
#include <iostream>
#include <tuple>
#include <mutex>
#include <map>

namespace detail
{
    template <class Sig, class F>
    struct memorize_helper;

    template <class Result, class... Args, class F>
    struct memorize_helper<Result(Args...), F>
    {
        using function_type   = F;
        using args_tuple_type = std::tuple<Args...>;

        memorize_helper(function_type&& f)
            : f{f}
        {
        }

        memorize_helper(memorize_helper const& other)
            : f{other.f}
        {
        }

        template <class... InnerArgs>
        Result operator()(InnerArgs&&... args) const
        {
            auto args_tuple = std::make_tuple(args...);
            auto cached = cache.find(args_tuple);

            if (cached == cache.end()) {
                auto&& result = f(
                    *this,
                    std::forward<InnerArgs>(args)...
                );
                cache[args_tuple] = result;
                return result;
            } else {
                return cached->second;
            }
        }

    private:
        function_type f;
        mutable std::map<args_tuple_type, Result> cache;
        mutable std::recursive_mutex cache_mutex;
    };
}

using detail::memorize_helper;

template <class Sig, class F>
memorize_helper<Sig, F> make_memoized_r(F&& f)
{
    return {std::forward<F>(f)};
}

int main()
{
    {
        auto r = make_memoized_r<unsigned int(unsigned int)>([](auto& fib, unsigned int n) {
            std::cout << "Calculating [n = " << n << "]\n";
            return n <= 1
                ? n
                : fib(n - 1) + fib(n - 2);
        });
        std::cout << r(10) << "\n";
    }
}

