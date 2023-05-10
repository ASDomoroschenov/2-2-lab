#ifndef STRING_NUMBER_H
#define STRING_NUMBER_H

#define UPPER_BOUND_INT "2147483647"
#define LOWER_BOUNT_INR ""

#include <iostream>
#include <string>
#include <sstream>
#include "long_number.h"

class string_number final : public long_number<std::string>
{
private:
    static bool validate_value(
            const std::string&);

    static size_t make_equal_length(
            std::string &,
            std::string &);

    static std::string naiv_mult(
            std::string,
            std::string);

    static std::string karatsuba(
            std::string,
            std::string);

    static std::string burnickel_ziegler_division(
            std::string dividend,
            std::string divider);

    static std::pair<std::string, std::string> div_three_halves_by_two(
            std::string first_dividend,
            std::string second_dividend,
            std::string third_dividend,
            std::string first_divider,
            std::string second_divider);

    static std::string div_two_digits_by_one(
            std::string dividend,
            std::string divider);
public:
    explicit string_number(
            std::string);

    long_number<std::string> *add(
            const long_number<std::string>*) override;

    long_number<std::string> *sum(
            const long_number<std::string>*) const override;

    long_number<std::string> *subtract(
            const long_number<std::string>*) override;

    long_number<std::string> *subtraction(
            const long_number<std::string>*) const override;

    long_number<std::string> *multiply(
            const long_number<std::string>*) override;

    long_number<std::string> *multiplication(
            const long_number<std::string>*) const override;

    long_number<std::string> *divide(
            const long_number<std::string>*) override;

    long_number<std::string> *division(
            const long_number<std::string>*) const override;

    long_number<std::string> *div(
            const unsigned long&) override;

    long_number<std::string> *division(
            const unsigned long&) const override;

    long_number<std::string> *mod(
            const unsigned long&) override;

    long_number<std::string> *module(
            const unsigned long&) override;

    long_number<std::string> *pow(
            unsigned long) override;

    bool lower_than(
            const long_number<std::string>*) const override;

    bool greater_than(
            const long_number<std::string>*) const override;

    bool lower_than_or_equal_to(
            const long_number<std::string>*) const override;

    bool greater_than_or_equal_to(
            const long_number<std::string>*) const override;

    bool equals(
            const long_number<std::string>*) const override;

    bool not_equals(
            const long_number<std::string>*) const override;

    ~string_number() override = default;
};

#endif // STRING_NUMBER_H