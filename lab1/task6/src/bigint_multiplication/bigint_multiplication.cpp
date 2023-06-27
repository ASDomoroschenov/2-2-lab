#include <climits>
#include "bigint_multiplication.h"

//begin region naive multiplication

bigint *multiplication_naive::multiply(
        bigint const *left_multiplier,
        bigint const *right_multiplier) const
{
    unsigned int remainder = 0;
    unsigned int shift = 0;
    auto [sign_left_multiplier, digits_left_multiplier, size_number_left_multiplier] = bigint_implementation::get_representation_data(left_multiplier);
    auto [sign_right_multiplier, digits_right_multiplier, size_number_right_multiplier] = bigint_implementation::get_representation_data(right_multiplier);
    int sign_result = (((sign_left_multiplier < 0 && sign_right_multiplier > 0) || (sign_left_multiplier > 0 && sign_right_multiplier < 0)) ? (-1) : (1));
    bigint *result = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                               0,
                                               nullptr,
                                               1);

    if ((size_number_left_multiplier == 1 && digits_left_multiplier[0] == 0) ||
        (size_number_right_multiplier == 1 && digits_right_multiplier[0] == 0))
    {
        dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier);
        dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier);
        delete result;

        return new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                         0,
                                         nullptr,
                                         1);
    }

    for (int i = size_number_right_multiplier - 1; i >= 0; i--)
    {
        size_t size_number_addition = size_number_left_multiplier + 1 + shift;
        auto *temp_addition = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(left_multiplier)->allocate_with_guard(sizeof(unsigned int) * (size_number_addition)));
        int index_item_addition = size_number_addition - shift - 1;

        for (int j = size_number_left_multiplier - 1; j >= 0; j--)
        {
            unsigned long long digit_left_multiplier = digits_left_multiplier[j];
            unsigned long long digit_right_multiplier = digits_right_multiplier[i];

            temp_addition[index_item_addition--] = (digit_left_multiplier * digit_right_multiplier + remainder) % BASE;
            remainder = (digit_left_multiplier * digit_right_multiplier + remainder) / BASE;
        }

        if (remainder != 0)
        {
            temp_addition[index_item_addition--] = remainder;
        }

        for (int index = size_number_addition - shift; index < size_number_addition; index++)
        {
            temp_addition[index] = 0;
        }

        bigint *temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                                 sign_result,
                                                 temp_addition + index_item_addition + 1,
                                                 size_number_addition - (index_item_addition + 1));
        *result += temp;

        delete temp;
        dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(temp_addition);
        shift++;
        remainder = 0;
    }

    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier);

    return result;
}

//end region naive multiplication


//begin region karatsuba multiplication

bigint *multiplication_karatsuba::multiply_wrapper(
        bigint const *left_multiplier,
        bigint const *right_multiplier) const
{
    auto [sign_left_multiplier, digits_left_multiplier, size_number_left_multiplier] = bigint_implementation::get_representation_data(left_multiplier);
    auto [sign_right_multiplier, digits_right_multiplier, size_number_right_multiplier] = bigint_implementation::get_representation_data(right_multiplier);
    size_t max_length_numbers = std::max(size_number_left_multiplier, size_number_right_multiplier);

    if (max_length_numbers < 5)
    {
        dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier);
        dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier);

        bigint::bigint_multiplication *multiplication = new multiplication_naive();
        bigint *result_multiply_naive = multiplication->multiply(left_multiplier, right_multiplier);

        delete multiplication;

        return result_multiply_naive;
    }

    //begin region make equal length

    max_length_numbers += max_length_numbers % 2;

    auto *digits_left_multiplier_equal_length = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(left_multiplier)->allocate_with_guard(sizeof(unsigned int) * max_length_numbers));
    auto *digits_right_multiplier_equal_length = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(right_multiplier)->allocate_with_guard(sizeof(unsigned int) * max_length_numbers));

    for (int i = 0; i < max_length_numbers - size_number_left_multiplier; i++)
    {
        digits_left_multiplier_equal_length[i] = 0;
    }

    memcpy(digits_left_multiplier_equal_length + max_length_numbers - size_number_left_multiplier,
           digits_left_multiplier,
           sizeof(unsigned int) * size_number_left_multiplier);


    for (int i = 0; i < max_length_numbers - size_number_right_multiplier; i++)
    {
        digits_right_multiplier_equal_length[i] = 0;
    }

    memcpy(digits_right_multiplier_equal_length + max_length_numbers - size_number_right_multiplier,
           digits_right_multiplier,
           sizeof(unsigned int) * size_number_right_multiplier);

    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier);

    //end region make equal length


    //begin region separate numbers

    auto *left_half_left_multiplier = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(left_multiplier)->allocate_with_guard(sizeof(unsigned int) * (max_length_numbers / 2)));
    auto *right_half_left_multiplier = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(left_multiplier)->allocate_with_guard(sizeof(unsigned int) * (max_length_numbers / 2)));

    auto *left_half_right_multiplier = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(right_multiplier)->allocate_with_guard(sizeof(unsigned int) * (max_length_numbers / 2)));
    auto *right_half_right_multiplier = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(right_multiplier)->allocate_with_guard(sizeof(unsigned int) * (max_length_numbers / 2)));

    memcpy(left_half_left_multiplier,
           digits_left_multiplier_equal_length,
           sizeof(unsigned int) * (max_length_numbers / 2));
    memcpy(right_half_left_multiplier,
           digits_left_multiplier_equal_length + (max_length_numbers / 2),
           sizeof(unsigned int) * (max_length_numbers / 2));

    memcpy(left_half_right_multiplier,
           digits_right_multiplier_equal_length,
           sizeof(unsigned int) * (max_length_numbers / 2));
    memcpy(right_half_right_multiplier,
           digits_right_multiplier_equal_length + (max_length_numbers / 2),
           sizeof(unsigned int) * (max_length_numbers / 2));

    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier_equal_length);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier_equal_length);

    //end region separate numbers


    //begin region calculation of the first two terms

    bigint *bigint_left_half_left_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                                                         sign_left_multiplier,
                                                                         left_half_left_multiplier,
                                                                         max_length_numbers / 2);
    bigint *bigint_right_half_left_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                                                          sign_left_multiplier,
                                                                          right_half_left_multiplier,
                                                                          max_length_numbers / 2);
    bigint *bigint_left_half_right_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(right_multiplier)->_memory,
                                                                          sign_right_multiplier,
                                                                          left_half_right_multiplier,
                                                                          max_length_numbers / 2);
    bigint *bigint_right_half_right_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(right_multiplier)->_memory,
                                                                           sign_right_multiplier,
                                                                           right_half_right_multiplier,
                                                                           max_length_numbers / 2);

    bigint *first_term = multiply_wrapper(bigint_left_half_left_multiplier, bigint_left_half_right_multiplier);
    bigint *second_term = multiply_wrapper(bigint_right_half_left_multiplier, bigint_right_half_right_multiplier);

    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(left_half_left_multiplier);
    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(right_half_left_multiplier);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(left_half_right_multiplier);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(right_half_right_multiplier);

    //end region calculation of the first two terms


    //begin region calculation of third term

    bigint *first_temp_term = *bigint_left_half_left_multiplier + bigint_right_half_left_multiplier;
    bigint *second_temp_term = *bigint_left_half_right_multiplier + bigint_right_half_right_multiplier;

    bigint *third_temp_term = multiply_wrapper(first_temp_term, second_temp_term);

    bigint *difference = *third_temp_term - first_term;
    bigint *third_term = *difference - second_term;

    delete first_temp_term;
    delete second_temp_term;
    delete third_temp_term;
    delete difference;
    delete bigint_left_half_left_multiplier;
    delete bigint_right_half_left_multiplier;
    delete bigint_left_half_right_multiplier;
    delete bigint_right_half_right_multiplier;

    //end region calculation of third term


    //begin region calculation of result

    auto [sign_first_term, digits_first_term, size_number_first_term] = bigint_implementation::get_representation_data(first_term);
    auto [sign_third_term, digits_third_term, size_number_third_term] = bigint_implementation::get_representation_data(third_term);

    auto *digits_first = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation*>(first_term)->allocate_with_guard(sizeof(unsigned int*) * (size_number_first_term + max_length_numbers)));
    auto *digits_third = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation*>(third_term)->allocate_with_guard(sizeof(unsigned int*) * (size_number_third_term + max_length_numbers / 2)));

    memcpy(digits_first,
           digits_first_term,
           sizeof(unsigned int) * size_number_first_term);

    for (size_t i = size_number_first_term; i < size_number_first_term + max_length_numbers; i++)
    {
        digits_first[i] = 0;
    }

    memcpy(digits_third,
           digits_third_term,
           sizeof(unsigned int) * size_number_third_term);

    for (size_t i = size_number_third_term; i < size_number_third_term + max_length_numbers / 2; i++)
    {
        digits_third[i] = 0;
    }

    bigint *first_term_with_shift = new bigint_implementation(dynamic_cast<bigint_implementation*>(first_term)->_memory,
                                                              sign_first_term,
                                                              digits_first,
                                                              size_number_first_term + max_length_numbers);
    bigint *third_term_with_shift = new bigint_implementation(dynamic_cast<bigint_implementation*>(third_term)->_memory,
                                                              sign_third_term,
                                                              digits_third,
                                                              size_number_third_term + max_length_numbers / 2);

    bigint *first_sum = *first_term_with_shift + second_term;
    bigint *result_temp = *first_sum + third_term_with_shift;

    dynamic_cast<bigint_implementation*>(first_term)->deallocate_with_guard(digits_first);
    dynamic_cast<bigint_implementation*>(third_term)->deallocate_with_guard(digits_third);
    dynamic_cast<bigint_implementation*>(first_term)->deallocate_with_guard(digits_first_term);
    dynamic_cast<bigint_implementation*>(third_term)->deallocate_with_guard(digits_third_term);
    delete first_term;
    delete second_term;
    delete third_term;
    delete first_term_with_shift;
    delete third_term_with_shift;
    delete first_sum;

    //end region calculation of result


    //begin region removal leading zeros

    auto [sign_result_temp, digits_result_temp, size_number_result_temp] = bigint_implementation::get_representation_data(result_temp);
    int sign_result = 0;
    unsigned int *digits_result = nullptr;
    size_t size_number_result = 0;

    int shift = 0;

    while (digits_result_temp[shift] == 0 && shift < size_number_result_temp)
    {
        shift++;
    }

    if (shift == size_number_result_temp && digits_result_temp[shift] < INT_MAX)
    {
        sign_result = digits_result_temp[shift - 1];
        size_number_result = 1;
    }
    else
    {
        sign_result = sign_result_temp;

        digits_result = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation*>(result_temp)->allocate_with_guard(sizeof(unsigned int) * (size_number_result_temp - shift)));
        memcpy(digits_result, digits_result_temp + shift, sizeof(unsigned int) * (size_number_result_temp - shift));
        size_number_result = size_number_result_temp - shift;
    }

    dynamic_cast<bigint_implementation const*>(result_temp)->deallocate_with_guard(digits_result_temp);

    //end region removal leading zeros

    bigint *result = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                               sign_result,
                                               digits_result,
                                               size_number_result);

    dynamic_cast<bigint_implementation*>(result_temp)->deallocate_with_guard(digits_result);
    delete result_temp;

    return result;
}

bigint *multiplication_karatsuba::multiply(
        bigint const *left_multiplier,
        bigint const *right_multiplier) const
{
    auto [sign_left_multiplier, digits_left_multiplier, size_number_left_multiplier] = bigint_implementation::get_representation_data(left_multiplier);
    auto [sign_right_multiplier, digits_right_multiplier, size_number_right_multiplier] = bigint_implementation::get_representation_data(right_multiplier);
    int additional_sign = (((sign_left_multiplier < 0 && sign_right_multiplier > 0) || (sign_left_multiplier > 0 && sign_right_multiplier < 0)) ? (-1) : (1));

    bigint *abs_left_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(left_multiplier)->_memory,
                                                            abs(sign_left_multiplier),
                                                            digits_left_multiplier,
                                                            size_number_left_multiplier);
    bigint *abs_right_multiplier = new bigint_implementation(dynamic_cast<bigint_implementation const*>(right_multiplier)->_memory,
                                                             abs(sign_right_multiplier),
                                                             digits_right_multiplier,
                                                             size_number_right_multiplier);

    dynamic_cast<bigint_implementation const*>(left_multiplier)->deallocate_with_guard(digits_left_multiplier);
    dynamic_cast<bigint_implementation const*>(right_multiplier)->deallocate_with_guard(digits_right_multiplier);

    bigint *result = multiply_wrapper(abs_left_multiplier, abs_right_multiplier);

    delete abs_left_multiplier;
    delete abs_right_multiplier;

    auto [sign_result, digits_result, size_number_result] = bigint_implementation::get_representation_data(result);

    bigint *result_with_sign = new bigint_implementation(dynamic_cast<bigint_implementation const*>(result)->_memory,
                                                         sign_result * additional_sign,
                                                         digits_result,
                                                         size_number_result);
    dynamic_cast<bigint_implementation*>(result)->deallocate_with_guard(digits_result);
    delete result;

    return result_with_sign;
}

//end region karatsuba multiplication


//begin region schonhage_strassen multiplication

bigint *multiplication_schonhage_strassen::multiply(
        bigint const *left_multiplier,
        bigint const *right_multiplier) const
{
    return nullptr;
}

//end region schonhage_strassen multiplication