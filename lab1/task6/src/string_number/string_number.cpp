#include "string_number.h"

bool string_number::validate_value(
        const std::string &initial_value)
{
    std::string temp = initial_value;

    if (initial_value.length() == 0 ||
        initial_value[0] == '+')
    {
        return false;
    }

    if (initial_value[0] == '-')
    {
        temp = temp.substr(1, temp.length() - 1);
    }

    for (char symbol : temp)
    {
        if (!isdigit(symbol))
        {
            return false;
        }
    }

    return true;
}

size_t string_number::make_equal_length(
        std::string &number_1,
        std::string &number_2)
{
    unsigned long len = std::max(number_1.length(), number_2.length());

    number_1 = std::string(len - number_1.length(), '0') + number_1;
    number_2 = std::string(len - number_2.length(), '0') + number_2;

    return len;
}

string_number::string_number(
        std::string init_value)
{
    if (validate_value(init_value))
    {
        _number = std::move(init_value);
    }
    else
    {
        throw std::invalid_argument("Initial value is not a number");
    }
}

long_number<std::string> *string_number::add(
        const long_number<std::string> *target)
{
    int remainder = 0;
    std::string result;
    std::string target_add = target->get_number();
    std::string number_str = get_number();
    std::string sign;

    if (number_str[0] == '-' && target_add[0] != '-')
    {
        target_add = "-" + target_add;
        long_number<std::string> *temp = new string_number(target_add);
        long_number<std::string> *result = subtract(temp);

        delete temp;

        return result;
    }

    if (number_str[0] != '-' && target_add[0] == '-')
    {
        target_add = target_add.substr(1, target_add.length() - 1);
        long_number<std::string> *temp = new string_number(target_add);
        long_number<std::string> *result = subtract(temp);

        delete temp;

        return result;
    }

    if (number_str[0] == '-' && target_add[0] == '-')
    {
        number_str = number_str.substr(1, number_str.length() - 1);
        target_add = target_add.substr(1, target_add.length() - 1);
        sign = "-";
    }

    make_equal_length(number_str, target_add);

    for(int i = target_add.length() - 1; i >= 0; i--)
    {
        result.insert(0, std::to_string(((number_str[i] - '0') + (target_add[i] - '0') + remainder) % 10));
        remainder = ((number_str[i] - '0') + (target_add[i] - '0') + remainder) / 10;
    }

    if (remainder)
    {
        result.insert(0, std::to_string(remainder));
    }

    while (!result.empty() && result[0] == '0')
    {
        result = result.substr(1, result.length() - 1);
    }

    if (result.empty())
    {
        _number = "0";
    }
    else
    {
        _number = sign + result;
    }

    return this;
}

long_number<std::string> *string_number::sum(
        const long_number<std::string> *target) const
{
    long_number<std::string> *temp = new string_number(_number);

    return temp->add(target);
}

long_number<std::string> *string_number::subtract(
        const long_number<std::string> *target)
{
    std::string number_str = get_number();
    std::string target_sub = target->get_number();
    std::string result;
    std::string sign;
    int difference = 0;

    if (number_str[0] == '-' && target_sub[0] != '-')
    {
        target_sub = "-" + target_sub;
        long_number<std::string> *temp = new string_number(target_sub);
        long_number<std::string> *result = add(temp);

        delete temp;

        return result;
    }

    if (number_str[0] != '-' && target_sub[0] == '-')
    {
        target_sub = target_sub.substr(1, target_sub.length() - 1);
        long_number<std::string> *temp = new string_number(target_sub);
        long_number<std::string> *result = add(temp);

        delete temp;

        return result;
    }

    if ((number_str[0] == '-' && target_sub[0] == '-') ||
        (number_str[0] != '-' && target_sub[0] != '-'))
    {
        sign = *this < target ? "-" : "";
    }

    if (number_str[0] == '-' && target_sub[0] == '-')
    {
        if (*this > target)
        {
            number_str.swap(target_sub);
        }
    }
    else
    {
        if (*this < target)
        {
            number_str.swap(target_sub);
        }
    }

    if (number_str[0] == '-')
    {
        number_str = number_str.substr(1, number_str.length() - 1);
    }

    if (target_sub[0] == '-')
    {
        target_sub = target_sub.substr(1, target_sub.length() - 1);
    }

    make_equal_length(number_str, target_sub);

    for (int i = number_str.length() - 1; i >= 0; i--)
    {
        difference = (number_str[i] - '0') - (target_sub[i] - '0');

        if (difference >= 0)
        {
            result.insert(0, std::to_string(difference));
        }
        else
        {
            int j = i - 1;

            while (j >= 0)
            {
                number_str[j] = number_str[j] - '0' ? ((number_str[j] - '0') - 1) % 10 + '0' : '9';

                if (number_str[j] != '9')
                {
                    break;
                }
                else
                {
                    j--;
                }
            }

            result.insert(0, std::to_string(difference + 10));
        }
    }

    while (!result.empty() && result[0] == '0')
    {
        result = result.substr(1, result.length() - 1);
    }

    if (result.empty())
    {
        _number = "0";
    }
    else
    {
        _number = sign + result;
    }

    return this;
}

long_number<std::string> *string_number::subtraction(
        const long_number<std::string> *target) const
{
    long_number<std::string> *temp = new string_number(_number);

    return temp->subtract(target);
}

std::string string_number::naiv_mult(
        std::string number,
        std::string multiplier)
{
    int remainder = 0;
    std::string to_addition;
    std::string addition_result;
    int shift = 0;

    if (number == "0" || multiplier == "0")
    {
        return "0";
    }

    for (int i = multiplier.length() - 1; i >= 0; i--)
    {
        for (int j = number.length() - 1; j >= 0; j--)
        {
            to_addition.insert(0, std::to_string(((number[j] - '0') * (multiplier[i] - '0') + remainder) % 10));
            remainder = ((number[j] - '0') * (multiplier[i] - '0') + remainder) / 10;
        }

        if (remainder)
        {
            to_addition.insert(0, std::to_string(remainder));
        }

        to_addition.append(std::string(shift++, '0'));
        addition_result.insert(0, std::string(abs(addition_result.length() - to_addition.length()), '0'));

        long_number<std::string> *temp_number_1 = new string_number(to_addition);
        long_number<std::string> *temp_number_2 = new string_number(addition_result);

        *temp_number_1 += temp_number_2;

        addition_result = temp_number_1->get_number();

        delete temp_number_1;
        delete temp_number_2;

        to_addition = "";
        remainder = 0;
    }

    while (!addition_result.empty() && addition_result[0] == '0')
    {
        addition_result.erase(addition_result.begin());
    }

    if (addition_result.empty())
    {
        return "0";
    }

    return addition_result;
}

std::string string_number::karatsuba(
        std::string number,
        std::string multiplier)
{
    int max_length = std::max(number.length(), multiplier.length());

    if (max_length < 10)
    {
        return naiv_mult(number, multiplier);
    }

    size_t number_length = make_equal_length(number, multiplier);

    number = std::string(number_length % 2, '0') + number;
    multiplier = std::string(number_length % 2, '0') + multiplier;
    number_length += number_length % 2;

    std::string left_part_number = number.substr(0, number_length / 2);
    std::string right_part_number = number.substr(number_length / 2, number_length / 2);
    std::string left_part_multiplier = multiplier.substr(0, number_length / 2);
    std::string right_part_multiplier = multiplier.substr(number_length / 2, number_length / 2);

    std::string first_addendum = karatsuba(left_part_number, left_part_multiplier);
    std::string second_addendum = karatsuba(right_part_number, right_part_multiplier);

    long_number<std::string> *first_temp_left_part = new string_number(left_part_number);
    long_number<std::string> *first_temp_right_part = new string_number(right_part_number);
    long_number<std::string> *second_temp_left_part = new string_number(left_part_multiplier);
    long_number<std::string> *second_temp_right_part = new string_number(right_part_multiplier);

    long_number<std::string> *to_multiply_1 = (*first_temp_left_part + first_temp_right_part);
    long_number<std::string> *to_multiply_2 = (*second_temp_left_part + second_temp_right_part);

    std::string third_addendum = karatsuba(to_multiply_1->get_number(), to_multiply_2->get_number());

    delete first_temp_left_part;
    delete first_temp_right_part;
    delete second_temp_left_part;
    delete second_temp_right_part;
    delete to_multiply_1;
    delete to_multiply_2;

    long_number<std::string> *temp_first_addendum = new string_number(first_addendum);
    long_number<std::string> *temp_second_addendum = new string_number(second_addendum);
    long_number<std::string> *temp_third_addendum = new string_number(third_addendum);

    long_number<std::string> *diff_1 = (*temp_third_addendum - temp_first_addendum);
    long_number<std::string> *diff_2 = (*diff_1 - temp_second_addendum);

    third_addendum = diff_2->get_number();

    delete temp_first_addendum;
    delete temp_second_addendum;
    delete temp_third_addendum;
    delete diff_1;
    delete diff_2;

    first_addendum += std::string(number_length, '0');
    third_addendum += std::string(number_length / 2, '0');

    long_number<std::string> *temp_1 = new string_number(first_addendum);
    long_number<std::string> *temp_2 = new string_number(second_addendum);
    long_number<std::string> *temp_3 = new string_number(third_addendum);

    long_number<std::string> *sum_1 = (*temp_1 + temp_2);
    long_number<std::string> *sum_2 = (*sum_1 + temp_3);

    std::string result = sum_2->get_number();

    delete temp_1;
    delete temp_2;
    delete temp_3;
    delete sum_1;
    delete sum_2;

    while (!result.empty() && result[0] == '0')
    {
        result.erase(result.begin());
    }

    if (result.empty())
    {
        return "0";
    }

    return result;
}

long_number<std::string> *string_number::multiply(
        const long_number<std::string> *target)
{
    std::string number_str = get_number();
    std::string target_mult = target->get_number();
    std::string sign;

    if ((number_str[0] == '-' && target_mult[0] != '-') ||
        (number_str[0] != '-' && target_mult[0] == '-'))
    {
        sign = "-";
    }

    if (number_str[0] == '-')
    {
        number_str = number_str.substr(1, number_str.length() - 1);
    }

    if (target_mult[0] == '-')
    {
        target_mult = target_mult.substr(1, target_mult.length() - 1);
    }

    _number = sign + karatsuba(number_str, target_mult);

    return this;
}

long_number<std::string> *string_number::multiplication(
        const long_number<std::string> *target) const
{
    long_number<std::string> *temp = new string_number(get_number());

    return temp->multiply(target);
}

long_number<std::string> *string_number::div(
        const unsigned long &target)
{
    std::string number_str = get_number();
    unsigned long temp = 0;
    std::string answer;
    unsigned long index = 0;
    std::string sign;

    if (number_str[0] == '-')
    {
        number_str = number_str.substr(1, number_str.length() - 1);
        sign = "-";
    }

    while (temp < target && index < number_str.length())
    {
        temp = temp * 10 + (number_str[index++] - '0');
    }

    while (index <= number_str.length())
    {
        answer += std::to_string(temp / target);
        temp -= target * (temp / target);

        if (index != number_str.length())
        {
            temp = temp * 10 + (number_str[index++] - '0');
        }
        else
        {
            index++;
        }
    }

    if (answer.length() > 1)
    {
        while (answer[0] == '0')
        {
            answer = answer.substr(1, answer.length() - 1);
        }
    }

    if (answer != "0")
    {
        _number = sign + answer;
    }
    else
    {
        _number = answer;
    }

    return this;
}

long_number<std::string> *string_number::division(
        const unsigned long &target)
{
    long_number<std::string> *temp = new string_number(get_number());

    return temp->div(target);
}

long_number<std::string> *string_number::mod(
        const unsigned long &target)
{
    std::string number_str = get_number();
    unsigned long temp = 0;
    std::string answer;
    int index = 0;
    std::string sign;

    if (number_str[0] == '-')
    {
        number_str = number_str.substr(1, number_str.length() - 1);
        sign = "-";
    }

    while (temp < target && index < number_str.length())
    {
        temp = temp * 10 + (number_str[index++] - '0');
    }

    while (index <= number_str.length())
    {
        answer += std::to_string(temp / target);
        temp -= target * (temp / target);

        if (index != number_str.length())
        {
            temp = temp * 10 + (number_str[index++] - '0');
        }
        else
        {
            index++;
        }
    }

    if (temp != 0)
    {
        _number = sign + std::to_string(temp);
    }
    else
    {
        _number = std::to_string(temp);
    }

    return this;
}

long_number<std::string> *string_number::module(
        const unsigned long &target)
{
    long_number<std::string> *temp = new string_number(get_number());

    return temp->mod(target);
}

long_number<std::string> *string_number::pow(
        unsigned long step)
{
    long_number<std::string> *number_to_pow = new string_number(_number);
    long_number<std::string> *result = new string_number("1");

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

bool string_number::lower_than(
        const long_number<std::string> *target) const
{
    std::string number_str = _number;
    std::string to_cmp = target->get_number();
    bool is_negative = false;

    if (number_str[0] == '-' && to_cmp[0] == '-')
    {
        is_negative = true;
    }

    if (number_str[0] == '-' && to_cmp[0] != '-')
    {
        return true;
    }

    if (number_str[0] != '-' && to_cmp[0] == '-')
    {
        return false;
    }

    if (number_str.length() < to_cmp.length())
    {
        if (is_negative)
        {
            return false;
        }

        return true;
    }

    if (number_str.length() > to_cmp.length())
    {
        if (is_negative)
        {
            return true;
        }

        return false;
    }

    if (number_str[0] == '-')
    {
        number_str.erase(number_str.begin());
    }

    if (to_cmp[0] == '-')
    {
        to_cmp.erase(to_cmp.begin());
    }

    for (int i = 0; i < number_str.length(); i++)
    {
        if (number_str[i] - '0' < to_cmp[i] - '0')
        {
            if (is_negative)
            {
                return false;
            }

            return true;
        }
        else
        {
            if (number_str[i] - '0' > to_cmp[i] - '0')
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

bool string_number::greater_than(
        const long_number<std::string> *target) const
{
    return !lower_than(target);
}

bool string_number::lower_than_or_equal_to(
        const long_number<std::string> *target) const
{
    return lower_than(target) || equals(target);
}

bool string_number::greater_than_or_equal_to(
        const long_number<std::string> *target) const
{
    return greater_than(target) || equals(target);
}

bool string_number::equals(
        const long_number<std::string> *target) const
{
    std::string to_cmp = target->get_number();
    std::string number_str = get_number();

    return to_cmp == number_str;
}

bool string_number::not_equals(
        const long_number<std::string> *target) const
{
    return !equals(target);
}