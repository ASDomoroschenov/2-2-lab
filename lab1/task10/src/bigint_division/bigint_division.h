#ifndef BIGINT_DIVISION_H
#define BIGINT_DIVISION_H

#define COUNT_FOUR_HALVES 4
#define COUNT_TWO_HALVES 2
#define DIV_LIMIT 10

#include <cstdarg>
#include "bigint.h"
#include "bigint_implementation.h"

class division_burnickel_ziegler final : public bigint::bigint_division
{

private:

    static void delete_leading_zeros(
            bigint const *bigint_number,
            unsigned int *&digits,
            size_t &size_number);

    static bigint **split_number_by_length(
            bigint const *bigint_number,
            size_t count_halves,
            size_t length);

    static bigint *glue_numbers(
            size_t count_numbers,
            ...);

    static bigint *normalize(
            bigint *&dividend,
            bigint *&divider,
            bigint::bigint_multiplication const *multiplication_implementation);

public:

    std::pair<bigint*, bigint*> divide(
            bigint const *dividend,
            bigint const *divider,
            bigint::bigint_multiplication const *multiplication_implementation) override;

    std::pair<bigint*, bigint*> subtract_with_shift(
            bigint const *minuend,
            bigint const *subtrahend,
            bigint::bigint_multiplication const *multiplication_implementation);

    std::pair<bigint*, bigint*> div_two_halves_by_one(
            bigint const *dividend,
            bigint const *divider,
            bigint::bigint_multiplication const *multiplication_implementation);

    std::pair<bigint*, bigint*> div_three_halves_by_two(
            size_t length,
            bigint const *first_half_dividend,
            bigint const *second_half_dividend,
            bigint const *third_half_dividend,
            bigint const *first_half_divider,
            bigint const *second_half_divider,
            bigint::bigint_multiplication const *multiplication_implementation);
};

#endif // BIGINT_DIVISION_H