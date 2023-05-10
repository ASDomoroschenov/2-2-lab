#include "bigint.h"

bigint::~bigint() = default;

bigint *bigint::operator+=(
        const bigint *other)
{
    return add(other);
}

bigint *bigint::operator+(
        const bigint *other) const
{
    return sum(other);
}

bigint *bigint::operator-=(
        const bigint *other)
{
    return subtract(other);
}

bigint *bigint::operator-(
        const bigint *other) const
{
    return subtraction(other);
}

bigint *bigint::operator*=(
        const bigint *other)
{
    return mult(other);
}

bigint *bigint::operator*(
        const bigint *other) const
{
    return multiplication(other);
}

bool bigint::operator<(
        const bigint *other) const
{
    return lower_than(other);
}

bool bigint::operator>(
        const bigint *other) const
{
    return greater_than(other);
}

bool bigint::operator<=(
        const bigint *other) const
{
    return lower_than_or_equal_to(other);
}

bool bigint::operator>=(
        const bigint *other) const
{
    return greater_than_or_equal_to(other);
}

bool bigint::operator==(
        const bigint *other) const
{
    return equals(other);
}

bool bigint::operator!=(
        const bigint *other) const
{
    return not_equals(other);
}