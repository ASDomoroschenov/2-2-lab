#ifndef LONG_NUMBER_H
#define LONG_NUMBER_H

#include <iostream>

template<typename tvalue>
class long_number
{

protected:

    tvalue _number;

public:

    //begin region get_representation

    tvalue get_number() const;

    //end region get_representation


    //begin region addition

    virtual long_number<tvalue> *add(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator+=(
            const long_number<tvalue>*);

    //end region addition


    //begin region sum

    virtual long_number<tvalue> *sum(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator+(
            const long_number<tvalue>*) const;

    //end region sum


    //begin regin subtract

    virtual long_number<tvalue> *subtract(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator-=(
            const long_number<tvalue>*);

    //end region subtract


    //begin region subtraction

    virtual long_number<tvalue> *subtraction(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator-(
            const long_number<tvalue>*) const;

    //end region subtraction


    //begin region multiply

    virtual long_number<tvalue> *multiply(
            const long_number<tvalue>*) = 0;

    long_number<tvalue> *operator*=(
            const long_number<tvalue>*);

    //end region multiply


    //begin region multiplication

    virtual long_number<tvalue> *multiplication(
            const long_number<tvalue>*) const = 0;

    long_number<tvalue> *operator*(
            const long_number<tvalue>*) const;

    //end region multiplication


    //begin region div

    virtual long_number<tvalue> *div(
            const unsigned long&) = 0;

    long_number<tvalue> *operator/=(
            const unsigned long&);

    //end region div


    //begin region division

    virtual long_number<tvalue> *division(
            const unsigned long&) = 0;

    long_number<tvalue> *operator/(
            const unsigned long&);

    //end region division


    //begin region mod

    virtual long_number<tvalue> *mod(
            const unsigned long&) = 0;

    long_number<tvalue> *operator%=(
            const unsigned long&);

    //end region mod


    //begin region module

    virtual long_number<tvalue> *module(
            const unsigned long&) = 0;

    long_number<tvalue> *operator%(
            const unsigned long&);

    //end region module


    //begin region pow

    virtual long_number<tvalue> *pow(
            unsigned long) = 0;

    long_number<tvalue> *operator^(
            unsigned long);

    //end region pow


    //begin region comparison

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

    //end region comparison


    //begin region destructor

    virtual ~long_number() = default;

    //end region destructor

};


//begin region get_representation

template<typename tvalue>
tvalue long_number<tvalue>::get_number() const
{
    return _number;
}

//end region get_representation


//begin region addition

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator+=(
        const long_number<tvalue> *other)
{
    return add(other);
}

//end region addition


//begin region sum

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator+(
        const long_number<tvalue> *other) const
{
    return sum(other);
}

//end region sum


//begin region subtract

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator-=(
        const long_number<tvalue> *other)
{
    return subtract(other);
}

//end region subtract


//begin region subtraction

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator-(
        const long_number<tvalue> *other) const
{
    return subtraction(other);
}

//end region subtraction


//begin region multiply

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator*=(
        const long_number<tvalue> *other)
{
    return multiply(other);
}

//end region multiply


//begin region multiplication

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator*(
        const long_number<tvalue> *other) const
{
    return multiplication(other);
}

//end region multiplication


//begin region div

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator/=(
        const unsigned long &target)
{
    return div(target);
}

//end region div


//begin region division

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator/(
        const unsigned long &target)
{
    return division(target);
}

//end region division


//begin region mod

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator%=(
        const unsigned long &target)
{
    return mod(target);
}

//end region mod


//begin region module

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator%(
        const unsigned long &target)
{
    return module(target);
}

//end region module


//begin region pow

template<typename tvalue>
long_number<tvalue> *long_number<tvalue>::operator^(
        unsigned long step)
{
    return pow(step);
}

//end region pow


//begin region comparison

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

//end region comparison

#endif // LONG_NUMBER_H