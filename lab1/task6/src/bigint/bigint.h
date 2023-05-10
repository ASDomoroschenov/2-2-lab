#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>

class bigint
{
public:
    virtual void *get_representation() const = 0;

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

    friend std::ostream& operator<<(
            std::ostream&,
            const bigint*);
};

#endif // BIGINT_H