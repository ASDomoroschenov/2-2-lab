#ifndef LONG_NUMBER_H
#define LONG_NUMBER_H

#include <iostream>

template<typename tvalue>
class long_number
{
protected:
    tvalue _number;
public:
    tvalue get_number() const;

    virtual long_number<tvalue> *add(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator+=(
            const long_number<tvalue>*);

    virtual long_number<tvalue> *sum(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator+(
            const long_number<tvalue>*) const;

    virtual long_number<tvalue> *subtract(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator-=(
            const long_number<tvalue>*);

    virtual long_number<tvalue> *subtraction(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator-(
            const long_number<tvalue>*) const;

    virtual long_number<tvalue> *multiply(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator*=(
            const long_number<tvalue>*);

    virtual long_number<tvalue> *multiplication(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator*(
            const long_number<tvalue>*) const;

    virtual long_number<tvalue> *div(
            const unsigned long&) = 0;

    long_number<tvalue> *operator/=(
            const unsigned long&);

    virtual long_number<tvalue> *division(
            const unsigned long&) = 0;

    long_number<tvalue> *operator/(
            const unsigned long&);

    virtual long_number<tvalue> *mod(
            const unsigned long&) = 0;

    long_number<tvalue> *operator%=(
            const unsigned long&);

    virtual long_number<tvalue> *module(
            const unsigned long&) = 0;

    long_number<tvalue> *operator%(
            const unsigned long&);

    virtual long_number<tvalue> *pow(
            unsigned long) = 0;

    long_number<tvalue> *operator^(
            unsigned long);

    virtual bool lower_than(
            const long_number<tvalue>*) const = 0;

    bool operator<(
            const long_number<tvalue>*) const;

    virtual bool greater_than(
            const long_number<tvalue>*) const = 0;

    bool operator>(
            const long_number<tvalue>*) const;

    virtual bool lower_than_or_equal_to(
            const long_number<tvalue>*) const = 0;

    bool operator<=(
            const long_number<tvalue>*) const;

    virtual bool greater_than_or_equal_to(
            const long_number<tvalue>*) const = 0;

    bool operator>=(
            const long_number<tvalue>*) const;

    virtual bool equals(
            const long_number<tvalue>*) const = 0;

    bool operator==(
            const long_number<tvalue>*) const;

    virtual bool not_equals(
            const long_number<tvalue>*) const = 0;

    bool operator!=(
            const long_number<tvalue>*) const;

    virtual ~long_number() = default;
};

template<typename tvalue>
tvalue long_number<tvalue>::get_number() const
{
    return _number;
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator+=(
        const long_number<tvalue> *other)
{
    return add(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator+(
        const long_number<tvalue> *other) const
{
    return sum(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator-=(
        const long_number<tvalue> *other)
{
    return subtract(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator-(
        const long_number<tvalue> *other) const
{
    return subtraction(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator*=(
        const long_number<tvalue> *other)
{
    return multiply(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator*(
        const long_number<tvalue> *other) const
{
    return multiplication(other);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator/=(
        const unsigned long &target)
{
    return div(target);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator/(
        const unsigned long &target)
{
    return division(target);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator%=(
        const unsigned long &target)
{
    return mod(target);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator%(
        const unsigned long &target)
{
    return module(target);
}

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator^(
        unsigned long step)
{
    return pow(step);
}

template<typename tvalue>
bool long_number<tvalue>::operator<(
        const long_number<tvalue> *other) const
{
    return lower_than(other);
}

template<typename tvalue>
bool long_number<tvalue>::operator>(
        const long_number<tvalue> *other) const
{
    return greater_than(other);
}

template<typename tvalue>
bool long_number<tvalue>::operator<=(
        const long_number<tvalue> *other) const
{
    return lower_than_or_equal_to(other);
}

template<typename tvalue>
bool long_number<tvalue>::operator>=(
        const long_number<tvalue> *other) const
{
    return greater_than_or_equal_to(other);
}

template<typename tvalue>
bool long_number<tvalue>::operator==(
        const long_number<tvalue> *other) const
{
    return equals(other);
}

template<typename tvalue>
bool long_number<tvalue>::operator!=(
        const long_number<tvalue> *other) const
{
    return not_equals(other);
}

#endif // LONG_NUMBER_H