#ifndef BIGINT_MULTIPLICATION
#define BIGINT_MULTIPLICATION

#include "bigint.h"
#include "bigint_implementation.h"

class multiplication_naive final : public bigint::bigint_multiplication
{

public:

    bigint *multiply(
            bigint const *left_multiplier,
            bigint const *right_multiplier) const override;

    ~multiplication_naive() override = default;

};

class multiplication_karatsuba final : public bigint::bigint_multiplication
{

public:

    bigint *multiply_wrapper(
            bigint const *left_multiplier,
            bigint const *right_multiplier) const;

    bigint *multiply(
            bigint const *left_multiplier,
            bigint const *right_multiplier) const override;

    ~multiplication_karatsuba() override = default;

};

class multiplication_schonhage_strassen final : public bigint::bigint_multiplication
{

public:

    bigint *multiply(
            bigint const *left_multiplier,
            bigint const *right_multiplier) const override;

    ~multiplication_schonhage_strassen() override = default;

};

#endif // BIGINT_MULTIPLICATION