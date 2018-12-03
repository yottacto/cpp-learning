#include <iostream>
#include <type_traits>
#include <string>
#include <utility>

struct user
{
    user(std::string name, int age)
        : name(name), age(age) {}
    auto get_name() const { return name; }
    auto get_age() const { return age; }

private:
    std::string name;
    unsigned age{0};
};

template <size_t I>
auto get(user const& u)
{
    if constexpr (I == 0)
        return u.get_name();
    else if constexpr (I == 1)
        return u.get_age();
}

namespace std
{
    template <> struct tuple_size<user> : std::integral_constant<std::size_t, 2> {};

    template <std::size_t N>
    struct tuple_element<N, user> { using type = decltype(get<N>(std::declval<user>())); };
}

int main()
{
    user j{"jack", 11};
    auto [name, age] = j;
    std::cout << name << ": " << age << " years old.\n";
}

