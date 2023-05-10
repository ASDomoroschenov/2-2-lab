#include "vector_number.h"

std::ostream &operator<<(
        std::ostream &stream,
        const vector_type &target_print)
{
    for (size_t i = 0; i < target_print.size(); i++)
    {
        stream << target_print[i] << " ";
    }

    return stream;
}

bool vector_number::validate_value(
        const vector_type &validate_value)
{
    if (validate_value[0] != 0 && validate_value[0] != 1)
    {
        return false;
    }

    for (const auto &item: validate_value)
    {
        if (item < 0)
        {
            return false;
        }
    }

    return true;
}

size_t vector_number::make_equal_length(
        vector_type &number_1,
        vector_type &number_2)
{
    size_t len = std::max(number_1.size(), number_2.size());
    size_t dif_number_1 = len - number_1.size();
    size_t dif_number_2 = len - number_2.size();

    for (size_t i = 0; i < dif_number_1; i++)
    {
        number_1.insert(number_1.begin(), 0);
    }

    for (size_t i = 0; i < dif_number_2; i++)
    {
        number_2.insert(number_2.begin(), 0);
    }

    return len;
}

vector_number::vector_number(
        vector_type initial_value)
{
    if (validate_value(initial_value))
    {
        _number = std::move(initial_value);
    }
    else
    {
        throw std::invalid_argument("Initial value is not a number");
    }
}

long_number<vector_type> *vector_number::add(
        const long_number<vector_type> *target)
{
    unsigned int remainder = 0;
    vector_type result;
    vector_type target_add = target->get_number();
    vector_type number_vec = get_number();
    int sign = 0;

    if (number_vec[0] == 1 && target_add[0] == 0)
    {
        target_add[0] = 1;
        long_number<vector_type> *temp = new vector_number(target_add);
        long_number<vector_type> *result = subtract(temp);

        delete temp;

        return result;
    }

    if (number_vec[0] == 0 && target_add[0] == 1)
    {
        target_add[0] = 0;
        long_number<vector_type> *temp = new vector_number(target_add);
        long_number<vector_type> *result = subtract(temp);

        delete temp;

        return result;
    }

    if (number_vec[0] == 1 && target_add[0] == 1)
    {
        sign = 1;
    }

    number_vec.erase(number_vec.begin());
    target_add.erase(target_add.begin());

    make_equal_length(number_vec, target_add);

    for(int i = target_add.size() - 1; i >= 0; i--)
    {
        result.insert(result.begin(), (static_cast<unsigned long long>(number_vec[i]) + static_cast<unsigned long long>(target_add[i]) + remainder) % BASE);
        remainder = (static_cast<unsigned long long>(number_vec[i]) + static_cast<unsigned long long>(target_add[i]) + remainder) / BASE;
    }

    if (remainder)
    {
        result.insert(result.begin(), remainder);
    }

    while (!result.empty() && result[0] == 0)
    {
        result.erase(result.begin());
    }

    if (result.empty())
    {
        _number = vector_type{0, 0};
    }
    else
    {
        result.insert(result.begin(), sign);
        _number = result;
    }

    return this;
}

long_number<vector_type> *vector_number::sum(
        const long_number<vector_type> *target) const
{
    long_number<vector_type> *temp = new vector_number(get_number());

    return temp->add(target);
}

long_number<vector_type> *vector_number::subtract(
        const long_number<vector_type> *target)
{
    vector_type number_vec = get_number();
    vector_type target_sub = target->get_number();
    vector_type result;
    int sign = 0;
    int difference = 0;

    if (number_vec[0] == 1 && target_sub[0] == 0)
    {
        target_sub[0] = 1;
        long_number<vector_type> *temp = new vector_number(target_sub);
        long_number<vector_type> *result = add(temp);

        delete temp;

        return result;
    }

    if (number_vec[0] == 0 && target_sub[0] == 1)
    {
        target_sub[0] = 0;
        long_number<vector_type> *temp = new vector_number(target_sub);
        long_number<vector_type> *result = add(temp);

        delete temp;

        return result;
    }

    if ((number_vec[0] == 1 && target_sub[0] == 1) ||
        (number_vec[0] == 0 && target_sub[0] == 0))
    {
        sign = *this < target ? 1 : 0;
    }

    if (number_vec[0] == 1 && target_sub[0] == 1)
    {
        if (*this > target)
        {
            number_vec.swap(target_sub);
        }
    }
    else
    {
        if (*this < target)
        {
            number_vec.swap(target_sub);
        }
    }

    number_vec.erase(number_vec.begin());
    target_sub.erase(target_sub.begin());

    make_equal_length(number_vec, target_sub);

//    std::cout << "number_vec: " << number_vec << std::endl;
//    std::cout << "target_sub: " << target_sub << std::endl;

    for (int i = number_vec.size() - 1; i >= 0; i--)
    {
        difference = number_vec[i] - target_sub[i];

        if (difference >= 0)
        {
            result.insert(result.begin(), difference);
        }
        else
        {
            int j = i - 1;

            while (j >= 0)
            {
                number_vec[j] = number_vec[j] ? (number_vec[j] - 1) % BASE : 9;

                if (number_vec[j] != 9)
                {
                    break;
                }
                else
                {
                    j--;
                }
            }

            result.insert(result.begin(), difference + 10);
        }
    }

    while (!result.empty() && result[0] == 0)
    {
        result.erase(result.begin());
    }

    if (result.empty())
    {
        _number = vector_type{0, 0};
    }
    else
    {
        result.insert(result.begin(), sign);
        _number = result;
    }

    return this;
}

long_number<vector_type> *vector_number::subtraction(
        const long_number<vector_type> *target) const
{
    long_number<vector_type> *temp = new vector_number(get_number());

    return temp->subtract(target);
}

vector_type vector_number::naiv_mult(
        vector_type number,
        vector_type multiplier)
{
    unsigned int remainder = 0;
    vector_type to_addition;
    vector_type addition_result;
    int shift = 0;

    if ((number.size() == 1 && number[0] == 0) ||
        (multiplier.size() == 1 && multiplier[0] == 0))
    {
        return vector_type{0};
    }

    for (int i = multiplier.size() - 1; i >= 0; i--)
    {
        for (int j = number.size() - 1; j >= 0; j--)
        {
            to_addition.insert(to_addition.begin(), (static_cast<unsigned long long>(number[j]) * static_cast<unsigned long long>(multiplier[i]) + remainder) % BASE);
            remainder = (static_cast<unsigned long long>(number[j]) * static_cast<unsigned long long>(multiplier[i]) + remainder) / BASE;
        }

        if (remainder)
        {
            to_addition.insert(to_addition.begin(), remainder);
        }

        for (int count = 0; count < shift; count++)
        {
            to_addition.push_back(0);
        }

        size_t len = abs(addition_result.size() - to_addition.size());

        for (int count = 0; count < len; count++)
        {
            addition_result.insert(addition_result.begin(), 0);
        }

        to_addition.insert(to_addition.begin(), 0);
        addition_result.insert(addition_result.begin(), 0);
        long_number<vector_type> *temp_number_1 = new vector_number(to_addition);
        long_number<vector_type> *temp_number_2 = new vector_number(addition_result);

        *temp_number_1 += temp_number_2;

        addition_result = temp_number_1->get_number();
        addition_result.erase(addition_result.begin());

        delete temp_number_1;
        delete temp_number_2;

        to_addition.clear();
        remainder = 0;
        shift++;
    }

    while (!addition_result.empty() && addition_result[0] == 0)
    {
        addition_result.erase(addition_result.begin());
    }

    if (addition_result.empty())
    {
        return vector_type{0};
    }

    return addition_result;
}

vector_type vector_number::karatsuba(
        vector_type number,
        vector_type multiplier)
{
    size_t max_length = std::max(number.size(), multiplier.size());

    if (max_length < 10)
    {
        return naiv_mult(number, multiplier);
    }

    size_t number_length = make_equal_length(number, multiplier);

    for (int i = 0; i < number_length % 2; i++)
    {
        number.insert(number.begin(), 0);
        multiplier.insert(multiplier.begin(), 0);
    }

    number_length += number_length % 2;

    vector_type left_part_number = vector_type(number.begin(), number.begin() + number_length / 2);
    vector_type right_part_number = vector_type(number.begin() + number_length / 2, number.end());
    vector_type left_part_multiplier = vector_type(multiplier.begin(), multiplier.begin() + number_length / 2);
    vector_type right_part_multiplier = vector_type(multiplier.begin() + number_length / 2, multiplier.end());

    vector_type first_addendum = karatsuba(left_part_number, left_part_multiplier);
    vector_type second_addendum = karatsuba(right_part_number, right_part_multiplier);

    left_part_number.insert(left_part_number.begin(), 0);
    left_part_multiplier.insert(left_part_multiplier.begin(), 0);
    right_part_number.insert(right_part_number.begin(), 0);
    right_part_multiplier.insert(right_part_multiplier.begin(), 0);

    long_number<vector_type> *first_temp_left_part = new vector_number(left_part_number);
    long_number<vector_type> *first_temp_right_part = new vector_number(right_part_number);
    long_number<vector_type> *second_temp_left_part = new vector_number(left_part_multiplier);
    long_number<vector_type> *second_temp_right_part = new vector_number(right_part_multiplier);

    long_number<vector_type> *to_multiply_1 = (*first_temp_left_part + first_temp_right_part);
    long_number<vector_type> *to_multiply_2 = (*second_temp_left_part + second_temp_right_part);

    vector_type to_multiply_vec_1 = to_multiply_1->get_number();
    vector_type to_multiply_vec_2 = to_multiply_2->get_number();

    to_multiply_vec_1.erase(to_multiply_vec_1.begin());
    to_multiply_vec_2.erase(to_multiply_vec_2.begin());

    vector_type third_addendum = karatsuba(to_multiply_vec_1, to_multiply_vec_2);

    delete first_temp_left_part;
    delete first_temp_right_part;
    delete second_temp_left_part;
    delete second_temp_right_part;
    delete to_multiply_1;
    delete to_multiply_2;

    first_addendum.insert(first_addendum.begin(), 0);
    second_addendum.insert(second_addendum.begin(), 0);
    third_addendum.insert(third_addendum.begin(), 0);

    long_number<vector_type> *temp_first_addendum = new vector_number(first_addendum);
    long_number<vector_type> *temp_second_addendum = new vector_number(second_addendum);
    long_number<vector_type> *temp_third_addendum = new vector_number(third_addendum);

    first_addendum.erase(first_addendum.begin());
    second_addendum.erase(second_addendum.begin());
//
//    std::cout << "temp_first_addendum:  " << temp_first_addendum->get_number() << std::endl;
//    std::cout << "temp_second_addendum: " << temp_second_addendum->get_number() << std::endl;
//    std::cout << "temp_third_addendum:  " << temp_third_addendum->get_number() << std::endl;

    long_number<vector_type> *diff_1 = (*temp_third_addendum - temp_first_addendum);

//    std::cout << "diff_1              : " << diff_1->get_number() << std::endl;

    long_number<vector_type> *diff_2 = (*diff_1 - temp_second_addendum);

//    std::cout << "diff_2    : " << diff_2->get_number() << std::endl;

//    std::cout << diff_2->get_number() << std::endl;

    vector_type new_third_addendum = diff_2->get_number();

    delete temp_third_addendum;
    delete diff_1;
    delete diff_2;

    for (int i = 0; i < number_length; i++)
    {
        first_addendum.push_back(0);
    }

    for (int i = 0; i < number_length / 2; i++)
    {
        new_third_addendum.push_back(0);
    }

    long_number<vector_type> *temp_3 = new vector_number(new_third_addendum);

    long_number<vector_type> *sum_1 = (*temp_first_addendum + temp_second_addendum);
    long_number<vector_type> *sum_2 = (*sum_1 + temp_3);

    vector_type result = sum_2->get_number();
    result.erase(result.begin());

    delete temp_first_addendum;
    delete temp_second_addendum;
    delete temp_3;
    delete sum_1;
    delete sum_2;

    while (!result.empty() && result[0] == 0)
    {
        result.erase(result.begin());
    }

    if (result.empty())
    {
        return vector_type{0};
    }

    return result;
}

long_number<vector_type> *vector_number::multiply(
        const long_number<vector_type> *target)
{
    vector_type number_vec = get_number();
    vector_type target_vec = target->get_number();
    int sign = 0;

    if (number_vec[0] != target_vec[0])
    {
        sign = 1;
    }

    number_vec.erase(number_vec.begin());
    target_vec.erase(target_vec.begin());

    vector_type result_multiply = karatsuba(number_vec, target_vec);
    result_multiply.insert(result_multiply.begin(), sign);

    _number = result_multiply;

    return this;
}

long_number<vector_type> *vector_number::multiplication(
        const long_number<vector_type> *target) const
{
    long_number<vector_type> *temp = new vector_number(get_number());

    return temp->multiply(target);
}

long_number<vector_type> *vector_number::div(
        const unsigned long &target)
{
    vector_type number_vec = get_number();
    unsigned long temp = 0;
    vector_type answer;
    unsigned long index = 0;
    int sign = 0;

    if (number_vec[0] == 1)
    {
        sign = 1;
    }

    number_vec.erase(number_vec.begin());

    while (temp < target && index < number_vec.size())
    {
        temp = temp * 10 + number_vec[index++];
    }

    while (index <= number_vec.size())
    {
        answer.push_back(temp / target);
        temp -= target * (temp / target);

        if (index != number_vec.size())
        {
            temp = temp * 10 + number_vec[index++];
        }
        else
        {
            index++;
        }
    }

    if (answer.size() > 1)
    {
        while (!answer.empty() && answer[0] == 0)
        {
            answer.erase(answer.begin());
        }
    }

    if (!answer.empty())
    {
        answer.insert(answer.begin(), sign);
        _number = answer;
    }
    else
    {
        _number = vector_type{0, 0};
    }

    return this;
}

long_number<vector_type> *vector_number::division(
        const unsigned long &target)
{
    long_number<vector_type> *temp = new vector_number(get_number());

    return temp->div(target);
}

long_number<vector_type> *vector_number::mod(
        const unsigned long &target)
{
    vector_type number_vec = get_number();
    unsigned long temp = 0;
    vector_type answer;
    unsigned long index = 0;
    int sign = 0;

    if (number_vec[0] == 1)
    {
        sign = 1;
    }

    number_vec.erase(number_vec.begin());

    while (temp < target && index < number_vec.size())
    {
        temp = temp * 10 + number_vec[index++];
    }

    while (index <= number_vec.size())
    {
        answer.push_back(temp / target);
        temp -= target * (temp / target);

        if (index != number_vec.size())
        {
            temp = temp * 10 + number_vec[index++];
        }
        else
        {
            index++;
        }
    }

    _number = vector_type{static_cast<unsigned int>(sign), static_cast<unsigned int>(temp)};

    return this;
}

long_number<vector_type> *vector_number::module(
        const unsigned long &target)
{
    long_number<vector_type> *temp = new vector_number(get_number());

    return temp->mod(target);
}

long_number<vector_type> *vector_number::pow(
        unsigned long step)
{
    long_number<vector_type> *number_to_pow = new vector_number(get_number());
    long_number<vector_type> *result = new vector_number(vector_type{0, 1});

    while (step)
    {
        if (step % 2 == 0)
        {
            step /= 2;
            *number_to_pow *= number_to_pow;
        }
        else
        {
            step--;
            *result *= number_to_pow;
        }
    }

    delete number_to_pow;

    return result;
}

bool vector_number::lower_than(
        const long_number<vector_type> *target) const
{
    vector_type number_vec = _number;
    vector_type to_cmp = target->get_number();
    bool is_negative = false;

    if (number_vec[0] == 1 && to_cmp[0] == 1)
    {
        is_negative = true;
    }

    if (number_vec[0] == 1 && to_cmp[0] == 0)
    {
        return true;
    }

    if (number_vec[0] == 0 && to_cmp[0] == 1)
    {
        return false;
    }

    if (number_vec.size() < to_cmp.size())
    {
        if (is_negative)
        {
            return false;
        }

        return true;
    }

    if (number_vec.size() > to_cmp.size())
    {
        if (is_negative)
        {
            return true;
        }

        return false;
    }

    number_vec.erase(number_vec.begin());
    to_cmp.erase(to_cmp.begin());

    for (size_t i = 0; i < number_vec.size(); i++)
    {
        if (number_vec[i] < to_cmp[i])
        {
            if (is_negative)
            {
                return false;
            }

            return true;
        }
        else
        {
            if (number_vec[i] > to_cmp[i])
            {
                if (is_negative)
                {
                    return true;
                }

                return false;
            }
        }
    }

    return false;
}

bool vector_number::greater_than(
        const long_number<vector_type> *target) const
{
    return !lower_than(target);
}

bool vector_number::lower_than_or_equal_to(
        const long_number<vector_type> *target) const
{
    return lower_than(target) || equals(target);
}

bool vector_number::greater_than_or_equal_to(
        const long_number<vector_type> *target) const
{
    return greater_than(target) || equals(target);
}

bool vector_number::equals(
        const long_number<vector_type> *target) const
{
    vector_type number_vec = get_number();
    vector_type to_cmp = target->get_number();

    if (number_vec.size() != to_cmp.size())
    {
        return false;
    }

    for (size_t i = 0; i < number_vec.size(); i++)
    {
        if (number_vec[i] != to_cmp[i])
        {
            return false;
        }
    }

    return true;
}

bool vector_number::not_equals(
        const long_number<vector_type> *target) const
{
    return !equals(target);
}