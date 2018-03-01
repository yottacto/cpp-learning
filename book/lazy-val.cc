// ml:std = gnu++17
// ml:ldf += -pthread
#include <iostream>
#include <optional>
#include <functional>
#include <utility>
#include <mutex>

namespace tue
{

    template <class F>
    struct lazy_val
    {
        lazy_val(F computation) : computation{computation} {}

        operator auto const& () const
        {
            std::call_once(cache_flag, [this]() {
                cache = std::invoke(computation);
            });
            return *cache;
        }

    private:
        F computation;
        mutable std::optional<decltype(computation())> cache;
        mutable std::once_flag cache_flag;
    };

    // helper function
    template <class F>
    auto make_lazy_val(F&& computation)
    {
        return lazy_val<F>{std::forward<F>(computation)};
    }

    // macro trick
    struct _lazy_val_helper
    {
        template <class F>
        auto operator-(F&& computation) const
        {
            return lazy_val<F>{computation};
        }
    } lazy_val_helper;

    #define lazy lazy_val_helper - [=]
}

int main()
{
    auto v = tue::lazy {
        return 4;
    };
    std::cout << v << "\n";
}

