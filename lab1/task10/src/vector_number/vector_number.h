#ifndef VECTOR_NUMBER_H
#define VECTOR_NUMBER_H

#include <iostream>
#include <vector>
#include <sstream>
#include "long_number.h"

using vector_type = std::vector<unsigned int>;

class vector_number final : public long_number<vector_type>
{

private:

    unsigned long long _base;

private:

    friend std::ostream &operator<<(
            std::ostream&,
            const vector_type&);

    static bool validate_value(
            const vector_type&);

    static size_t make_equal_length(
            vector_type&,
            vector_type&);

    static vector_type naiv_mult(
            vector_type,
            vector_type,
            unsigned long long);

    static vector_type karatsuba(
            vector_type,
            vector_type,
            unsigned long long);

    static vector_type burnickel_ziegler_division(
            vector_type dividend,
            vector_type divider,
            unsigned long long base);

    static std::pair<vector_type, vector_type> div_three_halves_by_two(
            vector_type first_dividend,
            vector_type second_dividend,
            vector_type third_dividend,
            vector_type first_divider,
            vector_type second_divider,
            unsigned long long base);

    static vector_type div_two_digits_by_one(
            vector_type dividend,
            vector_type divider,
            unsigned long long base);

public:

    explicit vector_number(
            const vector_type &initial_value,
            unsigned long long base);

    long_number<vector_type> *add(
            const long_number<vector_type>*) override;

    long_number<vector_type> *sum(
            const long_number<vector_type>*) const override;

    long_number<vector_type> *subtract(
            const long_number<vector_type>*) override;

    long_number<vector_type> *subtraction(
            const long_number<vector_type>*) const override;

    long_number<vector_type> *multiply(
            const long_number<vector_type>*) override;

    long_number<vector_type> *multiplication(
            const long_number<vector_type>*) const override;

    long_number<vector_type> *divide(
            const long_number<vector_type>*) override;

    long_number<vector_type> *division(
            const long_number<vector_type>*) const override;

    long_number<vector_type> *div(
            const unsigned long&) override;

    long_number<vector_type> *division(
            const unsigned long&) const override;

    long_number<vector_type> *mod(
            const unsigned long&) override;

    long_number<vector_type> *module(
            const unsigned long&) override;

    long_number<vector_type> *pow(
            unsigned long) override;

    bool lower_than(
            const long_number<vector_type>*) const override;

    bool greater_than(
            const long_number<vector_type>*) const override;

    bool lower_than_or_equal_to(
            const long_number<vector_type>*) const override;

    bool greater_than_or_equal_to(
            const long_number<vector_type>*) const override;

    bool equals(
            const long_number<vector_type>*) const override;

    bool not_equals(
            const long_number<vector_type>*) const override;

    ~vector_number() override = default;
};

#endif // VECTOR_NUMBER_H