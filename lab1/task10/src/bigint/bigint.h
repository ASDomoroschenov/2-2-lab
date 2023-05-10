#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>

class bigint
{

public:

    virtual bigint *add(
            const bigint*) = 0;

    bigint *operator+=(
            const bigint*);

    virtual bigint *sum(
            const bigint*) const = 0;

    bigint *operator+(
            const bigint*) const;

    virtual bigint *subtract(
            const bigint*) = 0;

    bigint *operator-=(
            const bigint*);

    virtual bigint *subtraction(
            const bigint*) const = 0;

    bigint *operator-(
            const bigint*) const;

    virtual bigint *multiply(
            const bigint*) = 0;

    bigint *operator*=(
            const bigint*);

    virtual bigint *multiplication(
            const bigint*) const = 0;

    bigint *operator*(
            const bigint*) const;

    virtual bigint *divide(
            const bigint*) = 0;

    bigint *operator/=(
            const bigint*);

    virtual bigint *division(
            const bigint*) const = 0;

    bigint *operator/(
            const bigint*);

    virtual bool lower_than(
            const bigint*) const = 0;

    bool operator<(
            const bigint*) const;

    virtual bool greater_than(
            const bigint*) const = 0;

    bool operator>(
            const bigint*) const;

    virtual bool lower_than_or_equal_to(
            const bigint*) const = 0;

    bool operator<=(
            const bigint*) const;

    virtual bool greater_than_or_equal_to(
            const bigint*) const = 0;

    bool operator>=(
            const bigint*) const;

    virtual bool equals(
            const bigint*) const = 0;

    bool operator==(
            const bigint*) const;

    virtual bool not_equals(
            const bigint*) const = 0;

    bool operator!=(
            const bigint*) const;

    virtual ~bigint();

    virtual void output() const = 0;

    friend std::ostream& operator<<(
            std::ostream &stream,
            const bigint *target_output);

};

class bigint_multiplication
{

public:

    virtual bigint *multiply(
            const bigint *left_multiplier,
            const bigint *right_multiplier) const = 0;

};

#endif // BIGINT_H