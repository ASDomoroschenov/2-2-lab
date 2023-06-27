#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

class bigint
{

public:

    virtual void output() const = 0;

    //begin region addition

    virtual bigint *add(
            bigint const *summand) = 0;

    bigint *operator+=(
            bigint const *summand);

    //end region addition


    //begin region sum

    virtual bigint *sum(
            bigint const *summand) const = 0;

    bigint *operator+(
            bigint const *summand) const;

    //end region sum


    //begin region subtract

    virtual bigint *subtract(
            bigint const *subtrahend) = 0;

    bigint *operator-=(
            bigint const *subtrahend);

    //end region subtract


    //begin region subtraction

    virtual bigint *subtraction(
            bigint const *subtrahend) const = 0;

    bigint *operator-(
            bigint const *subtrahend) const;

    //end region subtraction


    //begin region shift

    virtual bigint *shift_left(
            size_t count_digits) = 0;

    bigint *operator<<=(
            size_t count_digits);

    //begin region comparison

    virtual bool lower_than(
            bigint const *other) const = 0;

    bool operator<(
            bigint const *other) const;

    virtual bool greater_than(
            bigint const *other) const = 0;

    bool operator>(
            bigint const *other) const;

    virtual bool lower_than_or_equal_to(
            bigint const *other) const = 0;

    bool operator<=(
            bigint const *other) const;

    virtual bool greater_than_or_equal_to(
            bigint const *other) const = 0;

    bool operator>=(
            bigint const *other) const;

    virtual bool equals(
            bigint const *other) const = 0;

    bool operator==(
            bigint const *other) const;

    virtual bool not_equals(
            bigint const *other) const = 0;

    bool operator!=(
            bigint const *other) const;

    //end region comparison


    //begin region multiplication

    class bigint_multiplication
    {

    public:

        virtual bigint *multiply(
                bigint const *left_multiplier,
                bigint const *right_multiplier) const = 0;

        virtual ~bigint_multiplication() = default;

    };

    //end region multiplication


    //begin region division

    class bigint_division
    {

    public:

        virtual std::pair<bigint*, bigint*> divide(
                bigint const *dividend,
                bigint const *divider,
                bigint_multiplication const *multiplication_implementation) = 0;

        virtual ~bigint_division() = default;

    };

    //end region division


    //begin region destructor

    virtual ~bigint() = default;

    //end region destructor


    //begin region output

    friend std::ostream& operator<<(
            std::ostream &stream,
            bigint const *target_output);

    //end region output

};

#endif // BIGINT_H