#pragma once
#include <functional>

template <
    class Integer,
    class Plus = std::plus<Integer>,
    class Minus = std::minus<Integer>
>
struct fibonacci_iterator
{
    explicit fibonacci_iterator(
        Integer zero = Integer{0},
        Integer one = Integer{1},
        Plus p = Plus{},
        Minus m = Minus{}
    );

    Integer const& operator* () const;
    Integer const* operator->() const;

    fibonacci_iterator&      operator++();
    const fibonacci_iterator operator++(int);

    fibonacci_iterator&      operator--();
    const fibonacci_iterator operator--(int);

private:
    Integer curr;
    Integer next;

    Plus plus;
    Minus minus;
};

template <class Integer, class Plus, class Minus>
bool operator==(
    fibonacci_iterator<Integer, Plus, Minus>& lhs,
    fibonacci_iterator<Integer, Plus, Minus>& rhs
);


template <class Integer, class Plus, class Minus>
bool operator!=(
    fibonacci_iterator<Integer, Plus, Minus>& lhs,
    fibonacci_iterator<Integer, Plus, Minus>& rhs
);

// implementation

template <class Integer, class Plus, class Minus>
fibonacci_iterator<Integer, Plus, Minus>::fibonacci_iterator(
    Integer zero, Integer one, Plus plus, Minus minus
) : curr{zero}, next{one}, plus{plus}, minus{minus}
{
}

template <class Integer, class Plus, class Minus>
Integer const& fibonacci_iterator<Integer, Plus, Minus>::operator*() const
{
    return curr;
}

template <class Integer, class Plus, class Minus>
Integer const* fibonacci_iterator<Integer, Plus, Minus>::operator->() const
{
    return &**this;
}

template <class Integer, class Plus, class Minus>
fibonacci_iterator<Integer, Plus, Minus>&
fibonacci_iterator<Integer, Plus, Minus>::operator++()
{
    Integer new_next = plus(curr, next);
    curr = next;
    next = new_next;
    return *this;
}

template <class Integer, class Plus, class Minus>
fibonacci_iterator<Integer, Plus, Minus> const
fibonacci_iterator<Integer, Plus, Minus>::operator++(int)
{
    fibonacci_iterator result = *this;
    ++ *this;
    return result;
}

template <class Integer, class Plus, class Minus>
fibonacci_iterator<Integer, Plus, Minus>&
fibonacci_iterator<Integer, Plus, Minus>::operator--()
{
    Integer prev = minus(next, curr);
    next = curr;
    curr = prev;
    return *this;
}

template <class Integer, class Plus, class Minus>
fibonacci_iterator<Integer, Plus, Minus> const
fibonacci_iterator<Integer, Plus, Minus>::operator--(int)
{
    fibonacci_iterator result = *this;
    -- *this;
    return result;
}

template <class Integer, class Plus, class Minus>
bool operator==(
    fibonacci_iterator<Integer, Plus, Minus> const& lhs,
    fibonacci_iterator<Integer, Plus, Minus> const& rhs
)
{
    return lhs.curr == rhs.curr && lhs.next == rhs.next;
}

template <class Integer, class Plus, class Minus>
bool operator!=(
    fibonacci_iterator<Integer, Plus, Minus> const& lhs,
    fibonacci_iterator<Integer, Plus, Minus> const& rhs
)
{
    return !(lhs == rhs);
}

