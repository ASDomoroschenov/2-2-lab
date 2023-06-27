#include "bigint_division.h"

void division_burnickel_ziegler::delete_leading_zeros(
        bigint const *bigint_number,
        unsigned int *&digits,
        size_t &size_number)
{
    int shift = 0;

    while (shift < size_number - 1 && digits[shift] == 0)
    {
        shift++;
    }

    auto *new_digits = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(bigint_number)->allocate_with_guard(sizeof(unsigned int) * (size_number - shift)));
    memcpy(new_digits, digits + shift, sizeof(unsigned int) * (size_number - shift));
    dynamic_cast<bigint_implementation const*>(bigint_number)->deallocate_with_guard(digits);
    size_number -= shift;
    digits = new_digits;
}

bigint **division_burnickel_ziegler::split_number_by_length(
        bigint const *bigint_number,
        size_t count_halves,
        size_t length)
{
    auto [sign, digits, size_number] = bigint_implementation::get_representation_data(bigint_number);
    auto **numbers = reinterpret_cast<bigint**>(dynamic_cast<bigint_implementation const*>(bigint_number)->allocate_with_guard(sizeof(bigint*) * count_halves));
    size_t need_size = count_halves * length;

    auto *new_digits = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(bigint_number)->allocate_with_guard(sizeof(unsigned int) * need_size));

    memcpy(new_digits + (need_size - size_number),
           digits,
           sizeof(unsigned int) * size_number);

    for (int i = 0; i < need_size - size_number; i++)
    {
        new_digits[i] = 0;
    }

    dynamic_cast<bigint_implementation const*>(bigint_number)->deallocate_with_guard(digits);

    digits = new_digits;

    for (int i = 0; i < count_halves; i++)
    {
        auto *digits_number = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(bigint_number)->allocate_with_guard(sizeof(unsigned int) * length));
        memcpy(digits_number,
               digits + i * length,
               sizeof(unsigned int) * length);

        numbers[i] = new bigint_implementation(dynamic_cast<bigint_implementation const*>(bigint_number)->_memory,
                                               sign,
                                               digits_number,
                                               length);
        dynamic_cast<bigint_implementation const*>(bigint_number)->deallocate_with_guard(digits_number);
    }

    dynamic_cast<bigint_implementation const*>(bigint_number)->deallocate_with_guard(digits);

    return numbers;
}

bigint *division_burnickel_ziegler::glue_numbers(
        size_t count_numbers,
        ...)
{
    va_list arguments;
    va_start(arguments, count_numbers);

    unsigned int *digits_result = nullptr;
    size_t size_number_result = 0;

    for (int i = 0; i < count_numbers; i++)
    {
        bigint *next_number = va_arg(arguments, bigint*);
        auto [sign_next_number, digits_next_number, size_next_number] = bigint_implementation::get_representation_data(next_number);

        if (i == 0)
        {
            delete_leading_zeros(next_number,
                                 digits_next_number,
                                 size_next_number);
        }

        if (!(i == 0 && size_next_number == 1 && digits_next_number[0] == 0))
        {
            auto *new_digits_result = reinterpret_cast<unsigned int*>(::operator new(sizeof(unsigned int) * (size_number_result + size_next_number)));

            memcpy(new_digits_result,
                   digits_result,
                   sizeof(unsigned int) * size_number_result);
            memcpy(new_digits_result + size_number_result,
                   digits_next_number,
                   sizeof(unsigned int) * size_next_number);

            ::operator delete(digits_result);

            digits_result = new_digits_result;
            size_number_result += size_next_number;
        }

        dynamic_cast<bigint_implementation*>(next_number)->deallocate_with_guard(digits_next_number);
    }

    bigint *result = new bigint_implementation(nullptr,
                                               1,
                                               digits_result,
                                               size_number_result);

    ::operator delete(digits_result);

    return result;
}

bigint *division_burnickel_ziegler::normalize(
        bigint *&dividend,
        bigint *&divider,
        bigint::bigint_multiplication const *multiplication_implementation)
{
    auto [sign_divider, digits_divider, size_number_divider] = bigint_implementation::get_representation_data(divider);
    bigint *normalize = nullptr;

    if (digits_divider[0] < BASE / 2)
    {
        normalize = new bigint_implementation(nullptr,
                                                      BASE / (digits_divider[0] + 1),
                                                      nullptr,
                                                      1);
        bigint *dividend_temp_1 = multiplication_implementation->multiply(dividend, normalize);
        bigint *divider_temp_1 = multiplication_implementation->multiply(divider, normalize);

        delete dividend;
        delete divider;

        dividend = dividend_temp_1;
        divider = divider_temp_1;
    }

    dynamic_cast<bigint_implementation*>(divider)->deallocate_with_guard(digits_divider);

    return normalize;
}

std::pair<bigint*, bigint*> division_burnickel_ziegler::divide(
        bigint const *dividend,
        bigint const *divider,
        bigint::bigint_multiplication const *multiplication_implementation)
{
    //return subtract_with_shift(dividend, divider, multiplication_implementation);
    return div_two_halves_by_one(dividend, divider, multiplication_implementation);
}

std::pair<bigint*, bigint*> division_burnickel_ziegler::subtract_with_shift(
        bigint const *minuend,
        bigint const *subtrahend,
        bigint::bigint_multiplication const *multiplication_implementation)
{
    auto [sign_minuend, digits_minuend, size_number_minuend] = bigint_implementation::get_representation_data(minuend);
    auto [sign_subtrahend, digits_subtrahend, size_number_subtrahend] = bigint_implementation::get_representation_data(subtrahend);

    delete_leading_zeros(minuend,
                         digits_minuend,
                         size_number_minuend);
    delete_leading_zeros(subtrahend,
                         digits_subtrahend,
                         size_number_subtrahend);

    bigint *bigint_zero = new bigint_implementation(nullptr,
                                                    0,
                                                    nullptr,
                                                    1);
    bigint *minuend_temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(minuend)->_memory,
                                                     sign_minuend,
                                                     digits_minuend,
                                                     size_number_minuend);
    bigint *result_first = new bigint_implementation(nullptr,
                                                     0,
                                                     nullptr,
                                                     1);
    bigint *bigint_2 = new bigint_implementation(nullptr,
                                                 2,
                                                 nullptr,
                                                 1);

    while (*minuend_temp < bigint_zero)
    {
        auto [sign_minuend_temp, digits_minuend_temp, size_number_minuend_temp] = bigint_implementation::get_representation_data(minuend_temp);
        bigint *unsigned_minuend_temp = new bigint_implementation(dynamic_cast<bigint_implementation*>(minuend_temp)->_memory,
                                                   abs(sign_minuend_temp),
                                                   digits_minuend_temp,
                                                   size_number_minuend_temp);
        dynamic_cast<bigint_implementation*>(minuend_temp)->deallocate_with_guard(digits_minuend_temp);

        bigint *subtrahend_temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(subtrahend)->_memory,
                                                            sign_subtrahend,
                                                            digits_subtrahend,
                                                            size_number_subtrahend);
        bigint *shift = new bigint_implementation(nullptr,
                                                     1,
                                                     nullptr,
                                                     1);

        bigint *shift_temp = nullptr;
        bigint *temp = nullptr;

        bigint_implementation::copy(temp, subtrahend_temp);
        bigint_implementation::copy(shift_temp, shift);

        while (*subtrahend_temp < unsigned_minuend_temp)
        {
            bigint_implementation::copy(temp, subtrahend_temp);
            bigint_implementation::copy(shift_temp, shift);

            bigint *result_multiply_subtrahend_temp = multiplication_implementation->multiply(subtrahend_temp, bigint_2);;
            bigint *result_multiply_shift = multiplication_implementation->multiply(shift, bigint_2);

            delete subtrahend_temp;
            delete shift;

            subtrahend_temp = result_multiply_subtrahend_temp;
            shift = result_multiply_shift;
        }

        *result_first += shift_temp;
        *minuend_temp += temp;

        delete subtrahend_temp;
        delete shift_temp;
        delete unsigned_minuend_temp;
        delete shift;
        delete temp;
    }

    dynamic_cast<bigint_implementation const*>(minuend)->deallocate_with_guard(digits_minuend);
    dynamic_cast<bigint_implementation const*>(subtrahend)->deallocate_with_guard(digits_subtrahend);
    delete bigint_zero;
    delete bigint_2;

    return {result_first, minuend_temp};
}

std::pair<bigint*, bigint*> division_burnickel_ziegler::div_two_halves_by_one(
        bigint const *dividend,
        bigint const *divider,
        bigint::bigint_multiplication const *multiplication_implementation)
{
    dynamic_cast<bigint_implementation*>(const_cast<bigint*>(dividend))->delete_leading_zeros();
    dynamic_cast<bigint_implementation*>(const_cast<bigint*>(divider))->delete_leading_zeros();

    auto [sign_dividend, digits_dividend, size_number_dividend] = bigint_implementation::get_representation_data(dividend);
    auto [sign_divider, digits_divider, size_number_divider] = bigint_implementation::get_representation_data(divider);
    size_t size_number_quotient = (size_number_dividend - size_number_divider) + 1;

    bigint *dividend_temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(dividend)->_memory,
                                                      sign_dividend,
                                                      digits_dividend,
                                                      size_number_dividend);
    bigint *divider_temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(divider)->_memory,
                                                     sign_divider,
                                                     digits_divider,
                                                     size_number_divider);

    if (*dividend_temp == divider_temp)
    {
        delete dividend_temp;
        delete divider_temp;
        dynamic_cast<bigint_implementation const*>(dividend)->deallocate_with_guard(digits_dividend);
        dynamic_cast<bigint_implementation const*>(divider)->deallocate_with_guard(digits_divider);

        return {new bigint_implementation(nullptr,
                                          1,
                                          nullptr,
                                          1),
                new bigint_implementation(nullptr,
                                          0,
                                          nullptr,
                                          1)};
    }

    if (*dividend_temp < divider_temp)
    {
        delete dividend_temp;
        delete divider_temp;

        bigint *quotient = new bigint_implementation(nullptr,
                                                     0,
                                                     nullptr,
                                                     1);
        bigint *remainder = new bigint_implementation(dynamic_cast<bigint_implementation const*>(dividend)->_memory,
                                                      sign_dividend,
                                                      digits_dividend,
                                                      size_number_dividend);

        dynamic_cast<bigint_implementation const*>(dividend)->deallocate_with_guard(digits_dividend);
        dynamic_cast<bigint_implementation const*>(divider)->deallocate_with_guard(digits_divider);

        return {quotient,
                remainder};
    }

    bigint *bigint_normalize = normalize(dividend_temp, divider_temp, multiplication_implementation);

    size_t n = size_number_dividend;

    if (size_number_dividend / size_number_divider < 2)
    {
        n = size_number_divider * 2;
    }

    n = (n - 1) / 4 + 1;

    if (n * 2 < size_number_quotient)
    {
        n += size_number_quotient - n * 2;
    }

    bigint **halves_dividend = split_number_by_length(dividend_temp, COUNT_FOUR_HALVES, n);
    bigint **halves_divider = split_number_by_length(divider_temp, COUNT_TWO_HALVES, n);

    auto [q1, R] = div_three_halves_by_two(n,
                                           halves_dividend[0],
                                           halves_dividend[1],
                                           halves_dividend[2],
                                           halves_divider[0],
                                           halves_divider[1],
                                           multiplication_implementation);

    bigint **halves_R = split_number_by_length(R, COUNT_TWO_HALVES, n);

    auto [q2, S] = div_three_halves_by_two(n,
                                           halves_R[0],
                                           halves_R[1],
                                           halves_dividend[3],
                                           halves_divider[0],
                                           halves_divider[1],
                                           multiplication_implementation);

    dynamic_cast<bigint_implementation const*>(dividend)->deallocate_with_guard(digits_dividend);
    dynamic_cast<bigint_implementation const*>(divider)->deallocate_with_guard(digits_divider);
    delete dividend_temp;
    delete divider_temp;

    for (int i = 0; i < COUNT_FOUR_HALVES; i++)
    {
        delete halves_dividend[i];
    }
    delete halves_dividend;

    for (int i = 0; i < COUNT_TWO_HALVES; i++)
    {
        delete halves_divider[i];
        delete halves_R[i];
    }
    delete halves_divider;
    delete halves_R;

    delete R;

    bigint *quotient = glue_numbers(2, q1, q2);
    bigint *remainder = nullptr;

    delete q1;
    delete q2;

    if (bigint_normalize != nullptr)
    {
        std::pair<bigint*, bigint*> temp_remainder = divide(S, bigint_normalize, multiplication_implementation);
        remainder = temp_remainder.first;

        delete temp_remainder.second;
        delete bigint_normalize;
        delete S;
    }
    else
    {
        remainder = S;
    }

    return {quotient, remainder};
}

std::pair<bigint*, bigint*> division_burnickel_ziegler::div_three_halves_by_two(
        size_t length,
        bigint const *first_half_dividend,
        bigint const *second_half_dividend,
        bigint const *third_half_dividend,
        bigint const *first_half_divider,
        bigint const *second_half_divider,
        bigint::bigint_multiplication const *multiplication_implementation)
{
    bigint *bigint_base = new bigint_implementation(nullptr,
                                                    1,
                                                    nullptr,
                                                    1);
    bigint *bigint_one = new bigint_implementation(nullptr,
                                                   1,
                                                   nullptr,
                                                   1);
    bigint *bigint_zero = new bigint_implementation(nullptr,
                                                    0,
                                                    nullptr,
                                                    1);
    bigint *B = glue_numbers(2, first_half_divider, second_half_divider);

    bigint *Q = nullptr;
    bigint *D = nullptr;
    bigint *R1 = nullptr;

    bigint *A1_A2 = glue_numbers(2, first_half_dividend, second_half_dividend);

    if (*first_half_dividend >= first_half_divider)
    {
        *bigint_base <<= length;
        Q = *bigint_base - bigint_one;
        bigint *Q_multiply_B1 = multiplication_implementation->multiply(Q, first_half_divider);
        R1 = *A1_A2 - Q_multiply_B1;
        delete Q_multiply_B1;
    }
    else
    {
        std::pair<bigint*, bigint*> Q_R1 = div_two_halves_by_one(A1_A2, first_half_divider, multiplication_implementation);
        Q = Q_R1.first;
        R1 = Q_R1.second;
    }

    D = multiplication_implementation->multiply(Q, second_half_divider);

    bigint *R1_A3 = glue_numbers(2, R1, third_half_dividend);
    bigint *R = *R1_A3 - D;

    if (*R < bigint_zero)
    {
        std::pair<bigint*, bigint*> temp_result = subtract_with_shift(R, B, multiplication_implementation);
        delete R;

        *Q -= temp_result.first;
        R = temp_result.second;

        delete temp_result.first;
    }

    delete R1_A3;
    delete D;
    delete A1_A2;
    delete B;
    delete R1;
    delete bigint_one;
    delete bigint_base;
    delete bigint_zero;

    return {Q, R};
}