#include "bigint.h"

//begin region addition

bigint *bigint::operator+=(
        bigint const *summand)
{
    return add(summand);
}

//end region addition


//begin region sum

bigint *bigint::operator+(
        bigint const *summand) const
{
    return sum(summand);
}

//end region sum


//begin region subtract

bigint *bigint::operator-=(
        bigint const *subtrahend)
{
    return subtract(subtrahend);
}

//end region subtract


//begin region subtraction

bigint *bigint::operator-(
        bigint const *subtrahend) const
{
    return subtraction(subtrahend);
}

//end region subtraction


//begin region shift

bigint *bigint::operator<<=(
        size_t count_digits)
{
    return shift_left(count_digits);
}

//end region shift

//begin region comparison

bool bigint::operator<(
        bigint const *other) const
{
    return lower_than(other);
}

bool bigint::operator>(
        bigint const *other) const
{
    return greater_than(other);
}

bool bigint::operator<=(
        bigint const *other) const
{
    return lower_than_or_equal_to(other);
}

bool bigint::operator>=(
        bigint const *other) const
{
    return greater_than_or_equal_to(other);
}

bool bigint::operator==(
        bigint const *other) const
{
    return equals(other);
}

bool bigint::operator!=(
        bigint const *other) const
{
    return not_equals(other);
}

//end region comparison