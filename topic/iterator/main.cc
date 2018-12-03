#include <iostream>
#include "fibonacci-iterator.hh"

int main()
{
    fibonacci_iterator<int> it;
    auto constexpr last = 20;
    for (auto i = 0; i < last; i++, ++it)
        std::cout << "fib[" << i << "] = " << *it << "\n";

    for (auto i = last - 1; i >= 0; i--, --it)
        std::cout << "fib[" << i << "] = " << *it << "\n";
}

