#ifndef VECTOR_NUMBER_H
#define VECTOR_NUMBER_H

#define BASE 10//(static_cast<unsigned long>(1) << (sizeof(int) << 3))

#include <iostream>
#include <vector>
#include <sstream>
#include "long_number.h"

using vector_type = std::vector<unsigned int>;

class vector_number final : public long_number<vector_type>
{
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
            vector_type);

    static vector_type karatsuba(
            vector_type,
            vector_type);
public:
    explicit vector_number(
            vector_type);

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

    long_number<vector_type> *div(
            const unsigned long&) override;

    long_number<vector_type> *division(
            const unsigned long&) override;

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