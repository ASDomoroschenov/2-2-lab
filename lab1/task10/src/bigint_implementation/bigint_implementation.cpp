#include <climits>

#include "bigint_implementation.h"
#include "long_number.h"
#include "string_number.h"

//1 2 3 - 3
//0 0 0 0 0 0 - 6


//begin region translate

std::tuple<int, unsigned int*, size_t> bigint_implementation::translate_to_array(
        const std::string &str_number) const
{
    auto *digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int)));
    size_t temp_size = 1;
    int sign = 1;
    int index_sign = 0;

    if (str_number[0] == '-')
    {
        sign = -1;
        index_sign++;
    }

    std::string number_without_sign = str_number.substr(index_sign, str_number.length() - index_sign);

    long_number<std::string> *string_base = new string_number(std::to_string(BASE));
    long_number<std::string> *this_number = new string_number(number_without_sign);

    int counter = 1;

    while (*this_number > string_base)
    {
        long_number<std::string> *res_module = *this_number % BASE;
        digits[temp_size - counter] = static_cast<unsigned int>(std::atol(res_module->get_number().c_str()));
        *this_number /= BASE;

        if (temp_size == counter)
        {
            temp_size *= 2;
            auto *temp_digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * temp_size));
            memcpy(temp_digits + (temp_size - counter), digits, sizeof(unsigned int) * counter);
            deallocate_with_guard(digits);
            digits = temp_digits;
        }

        counter++;

        delete res_module;
    }

    if (temp_size == counter)
    {
        temp_size *= 2;
        auto *temp_digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * temp_size));
        memcpy(temp_digits + (temp_size - counter), digits, sizeof(unsigned int) * counter);
        deallocate_with_guard(digits);
        digits = temp_digits;
    }

    digits[temp_size - counter++] = static_cast<unsigned int>(std::atol(this_number->get_number().c_str()));

    delete this_number;
    delete string_base;

    auto *new_digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int*) * counter));
    memcpy(new_digits, digits + temp_size - counter + 1, sizeof(unsigned int) * (counter - 1));
    deallocate_with_guard(digits);

    return std::make_tuple(sign, new_digits, counter - 1);
}

std::string bigint_implementation::translate_to_string_number() const
{
    if (_digits == nullptr)
    {
        return std::to_string(_sign);
    }

    long_number<std::string> *string_base = new string_number(std::to_string(BASE));
    long_number<std::string> *result = new string_number("0");

    for (int i = 0; i < _size_number; i++)
    {
        long_number<std::string> *temp = new string_number(std::to_string(_digits[i]));
        long_number<std::string> *pow_res = *string_base ^ (_size_number - i - 1);
        long_number<std::string> *res = *pow_res * temp;

        result->add(res);

        delete temp;
        delete pow_res;
        delete res;
    }

    std::string result_str = ((_sign < 0) ? ("-" + result->get_number()) : (result->get_number()));

    delete string_base;
    delete result;

    return result_str;
}

//end region translate


//begin region help functions

bool bigint_implementation::check_string_number(
        std::string const &string_number)
{
    int index = 0;

    if (string_number[0] == '-')
    {
        index++;
    }

    while (index < string_number.length())
    {
        if (!isdigit(string_number[index]))
        {
            return false;
        }

        index++;
    }

    return true;
}

bool bigint_implementation::fit_in_int(
        std::string const &string_number)
{
    try
    {
        std::stoi(string_number);
    }
    catch (std::exception &ex)
    {
        return false;
    }

    return true;
}

bigint_implementation::bigint_implementation(
        memory *memory_init,
        int _sign_init,
        unsigned int *digits_init,
        size_t size_number_init) :
        _memory(memory_init),
        _sign(_sign_init),
        _size_number(size_number_init)
{
    if (digits_init != nullptr)
    {
        _digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * _size_number));
        memcpy(_digits, digits_init, sizeof(unsigned int) * _size_number);
    }
    else
    {
        _digits = nullptr;
    }
}

std::tuple<int, unsigned int*, size_t> bigint_implementation::get_representation_data(
        bigint const *target_get)
{
    int sign_copy = dynamic_cast<bigint_implementation const*>(target_get)->_sign;
    size_t size_number_copy = dynamic_cast<bigint_implementation const*>(target_get)->_size_number;
    auto *digits_copy = reinterpret_cast<unsigned int*>(dynamic_cast<bigint_implementation const*>(target_get)->allocate_with_guard(sizeof(unsigned int) * size_number_copy));

    if (dynamic_cast<bigint_implementation const*>(target_get)->_digits == nullptr)
    {
        digits_copy[0] = abs(sign_copy);
    }
    else
    {
        memcpy(digits_copy, dynamic_cast<bigint_implementation const*>(target_get)->_digits, sizeof(unsigned int) * size_number_copy);
    }

    return std::make_tuple(sign_copy, digits_copy, size_number_copy);
}

void bigint_implementation::delete_leading_zeros()
{
    if (_digits != nullptr)
    {
        int shift = 0;

        while (shift < _size_number - 1 && _digits[shift] == 0)
        {
            shift++;
        }

        auto *new_digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * (_size_number - shift)));
        memcpy(new_digits, _digits + shift, sizeof(unsigned int) * (_size_number - shift));
        deallocate_with_guard(_digits);
        _size_number -= shift;
        _digits = new_digits;
    }
}

void bigint_implementation::copy(
        bigint *&dest,
        bigint *src)
{
    auto [sign_src, digits_src, size_number_src] = get_representation_data(src);
    delete dest;

    dest = new bigint_implementation(dynamic_cast<bigint_implementation*>(src)->_memory,
                                     sign_src,
                                     digits_src,
                                     size_number_src);

    dynamic_cast<bigint_implementation*>(src)->deallocate_with_guard(digits_src);
}

//end region help functions

void bigint_implementation::output() const
{
    if (_digits != nullptr)
    {
        for (int i = 0; i < _size_number; i++)
        {
            std::cout << _digits[i] << " ";
        }
    }
    else
    {
        std::cout << _sign;
    }

    std::cout << std::endl;
}

//begin region memory_holder

memory *bigint_implementation::get_memory() const
{
    return _memory;
}

//end region memory_holder


//begin region addition

bigint *bigint_implementation::add(
        bigint const *summand)
{
    auto [sign_this, digits_this, size_number_this] = get_representation_data(this);
    auto [sign_summand, digits_summand, size_number_summand] = get_representation_data(summand);

    if ((sign_this < 0 && sign_summand > 0) ||
        (sign_this > 0 && sign_summand < 0))
    {
        deallocate_with_guard(digits_this);
        dynamic_cast<bigint_implementation const*>(summand)->deallocate_with_guard(digits_summand);

        bigint *temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(summand)->_memory,
                                                 -1 * dynamic_cast<bigint_implementation const*>(summand)->_sign,
                                                 dynamic_cast<bigint_implementation const*>(summand)->_digits,
                                                 dynamic_cast<bigint_implementation const*>(summand)->_size_number);
        bigint *result_sub = subtract(temp);

        delete temp;

        return result_sub;
    }
    
    int sign_result = 1;
    auto *digits_result = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * (std::max(size_number_this, size_number_summand) + 1)));
    size_t size_number_result = std::max(size_number_this, size_number_summand) + 1;

    for (int i = 0; i < size_number_result; i++)
    {
        digits_result[i] = 0;
    }

    if (sign_summand < 0 && _sign < 0)
    {
        sign_result = -1;
    }

    int index_result = size_number_result - 1;
    int i = std::max(size_number_summand, size_number_this);
    int index_this = _size_number - 1;
    int index_summand = size_number_summand - 1;
    unsigned long long temp = 0;

    while (i > 0)
    {
        unsigned long long digit_this = ((index_this < 0) ? (0) : (digits_this[index_this--]));
        unsigned long long digit_summand = ((index_summand < 0) ? (0) : (digits_summand[index_summand--]));

        temp += digit_this + digit_summand;
        digits_result[index_result--] = temp % BASE;
        temp /= BASE;
        i--;
    }

    if (temp)
    {
        digits_result[index_result] = temp;
    }

    int shift = 0;

    while (shift < size_number_result && digits_result[shift] == 0)
    {
        shift++;
    }

    deallocate_with_guard(_digits);

    if (shift == size_number_result && digits_result[shift - 1] < INT_MAX)
    {
        _sign = digits_result[shift - 1];
        _digits = nullptr;
        _size_number = 1;
    }
    else
    {
        _sign = sign_result;

        _digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * (size_number_result - shift)));
        memcpy(_digits, digits_result + shift, sizeof(unsigned int) * (size_number_result - shift));
        _size_number = size_number_result - shift;
    }

    deallocate_with_guard(digits_result);
    deallocate_with_guard(digits_this);
    dynamic_cast<bigint_implementation const*>(summand)->deallocate_with_guard(digits_summand);

    return this;
}

//end region addition


//begin region sum

bigint *bigint_implementation::sum(
        bigint const *summand) const
{
    bigint *temp = new bigint_implementation(_memory,
                                             _sign,
                                             _digits,
                                             _size_number);

    return temp->add(summand);
}

//end region sum


//begin region subtract

bigint *bigint_implementation::subtract(
        bigint const *subtrahend)
{
    auto [sign_this, digits_this, size_number_this] = get_representation_data(this);
    auto [sign_subtrahend, digits_subtrahend, size_number_subtrahend] = get_representation_data(subtrahend);

    if ((sign_this < 0 && sign_subtrahend > 0) ||
        (sign_this > 0 && sign_subtrahend < 0))
    {
        deallocate_with_guard(digits_this);
        dynamic_cast<bigint_implementation const*>(subtrahend)->deallocate_with_guard(digits_subtrahend);

        bigint *temp = new bigint_implementation(dynamic_cast<bigint_implementation const*>(subtrahend)->_memory,
                                                 -1 * dynamic_cast<bigint_implementation const*>(subtrahend)->_sign,
                                                 dynamic_cast<bigint_implementation const*>(subtrahend)->_digits,
                                                 dynamic_cast<bigint_implementation const*>(subtrahend)->_size_number);
        bigint *result_add = add(temp);

        delete temp;

        return result_add;
    }

    int sign_result = 1;
    auto *digits_result = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * std::max(size_number_this, size_number_subtrahend)));
    size_t size_number_result = std::max(size_number_this, size_number_subtrahend);

    for (int i = 0; i < size_number_result; i++)
    {
        digits_result[i] = 0;
    }

    if ((sign_subtrahend > 0 && sign_this > 0) ||
        (sign_subtrahend < 0 && sign_this < 0))
    {
        sign_result = ((*this < subtrahend) ? (-1) : (1));
    }

    if (sign_this < 0 && sign_subtrahend < 0)
    {
        if (*this > subtrahend)
        {
            auto *temp_ptr = digits_this;
            digits_this = digits_subtrahend;
            digits_subtrahend = temp_ptr;

            auto temp_size = size_number_this;
            size_number_this = size_number_subtrahend;
            size_number_subtrahend = temp_size;
        }
    }
    else
    {
        if (*this < subtrahend)
        {
            auto *temp_ptr = digits_this;
            digits_this = digits_subtrahend;
            digits_subtrahend = temp_ptr;

            auto temp_size = size_number_this;
            size_number_this = size_number_subtrahend;
            size_number_subtrahend = temp_size;
        }
    }

    int index_result = size_number_result - 1;
    unsigned long long remainder = 0;
    int i = std::max(size_number_subtrahend, size_number_this);
    int index_this = size_number_this - 1;
    int index_subtrahend = size_number_subtrahend - 1;
    long long temp = 0;

    while (i > 0)
    {
        long long digit_this = ((index_this < 0) ? (0) : (digits_this[index_this--]));
        long long digit_subtrahend = ((index_subtrahend < 0) ? (0) : (digits_subtrahend[index_subtrahend--]));
//        long long difference = digit_this - digit_subtrahend;
//
//        if (difference >= 0)
//        {
//            digits_result[index_result--] = difference;
//        }
//        else
//        {
//            int j = i;
//
//            while (j >= 0)
//            {
//                digits_this[j] = (digits_this[j]) ? ((digits_this[j] - 1) % BASE) : (BASE - 1);
//
//                if (digits_this[j] != BASE - 1)
//                {
//                    break;
//                }
//                else
//                {
//                    j--;
//                }
//            }
//
//            digits_result[index_result--] = difference + BASE;
//        }

        temp += digit_this - digit_subtrahend + BASE;
        digits_result[index_result--] = temp % BASE;
        temp = temp / BASE - 1;

        i--;
    }

    int shift = 0;

    while (shift < size_number_result && digits_result[shift] == 0)
    {
        shift++;
    }

    deallocate_with_guard(_digits);

    if (shift == size_number_result && digits_result[shift - 1] < INT_MAX)
    {
        _sign = digits_result[shift - 1];
        _digits = nullptr;
        _size_number = 1;
    }
    else
    {
        _sign = sign_result;

        _digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * (size_number_result - shift)));
        memcpy(_digits, digits_result + shift, sizeof(unsigned int) * (size_number_result - shift));
        _size_number = size_number_result - shift;
    }

    deallocate_with_guard(digits_result);
    deallocate_with_guard(digits_this);
    dynamic_cast<bigint_implementation const*>(subtrahend)->deallocate_with_guard(digits_subtrahend);

    return this;
}

//end region subtract


//begin region subtraction

bigint *bigint_implementation::subtraction(
        bigint const *subtrahend) const
{
    bigint *temp = new bigint_implementation(_memory,
                                             _sign,
                                             _digits,
                                             _size_number);

    return temp->subtract(subtrahend);
}

//end region subtraction


//begin region shift

bigint *bigint_implementation::shift_left(
        size_t count_digits)
{
    auto [sign_this, digits_this, size_number_this] = get_representation_data(this);

    if (size_number_this == 1 && digits_this[0] == 0)
    {
        return this;
    }

    auto *new_digits_this = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * (size_number_this + count_digits)));

    for (size_t i = size_number_this; i < count_digits; i++)
    {
        new_digits_this[i] = 0;
    }

    memcpy(new_digits_this,
           digits_this,
           sizeof(unsigned int) * size_number_this);

    deallocate_with_guard(_digits);
    deallocate_with_guard(digits_this);
    _digits = new_digits_this;
    _size_number += count_digits;

    return this;
}

//end region shift


//begin region comparison

bool bigint_implementation::lower_than(
        bigint const *other) const
{
    auto [sign_this, digits_this, size_number_this] = get_representation_data(this);
    auto [sign_other, digits_other, size_number_other] = get_representation_data(other);

    bool is_negative = false;

    if (sign_this <= 0 && sign_other <= 0)
    {
        is_negative = true;
    }

    if (sign_this < 0 && sign_other > 0)
    {
        deallocate_with_guard(digits_this);
        deallocate_with_guard(digits_other);

        return true;
    }

    if (sign_this > 0 && sign_other < 0)
    {
        deallocate_with_guard(digits_this);
        deallocate_with_guard(digits_other);

        return false;
    }

    if (size_number_this < size_number_other)
    {
        deallocate_with_guard(digits_this);
        deallocate_with_guard(digits_other);

        return !is_negative;
    }

    if (size_number_this > size_number_other)
    {
        deallocate_with_guard(digits_this);
        deallocate_with_guard(digits_other);

        return is_negative;
    }

    for (int i = 0; i < size_number_other; i++)
    {
        if (digits_this[i] < digits_other[i])
        {
            deallocate_with_guard(digits_this);
            deallocate_with_guard(digits_other);

            return !is_negative;
        }
        else
        {
            if (digits_this[i] > digits_other[i])
            {
                deallocate_with_guard(digits_this);
                deallocate_with_guard(digits_other);

                return is_negative;
            }
        }
    }

    deallocate_with_guard(digits_this);
    deallocate_with_guard(digits_other);

    return false;
}

bool bigint_implementation::greater_than(
        bigint const *other) const
{
    return !lower_than(other);
}

bool bigint_implementation::lower_than_or_equal_to(
        bigint const *other) const
{
    return lower_than(other) || equals(other);
}

bool bigint_implementation::greater_than_or_equal_to(
        bigint const *other) const
{
    return greater_than(other) || equals(other);
}

bool bigint_implementation::equals(
        bigint const *other) const
{
    auto [sign_this, digits_this, size_number_this] = get_representation_data(this);
    auto [sign_other, digits_other, size_number_other] = get_representation_data(other);

    if (dynamic_cast<bigint_implementation const*>(other)->_digits == nullptr)
    {
        digits_other[0] = abs(sign_other);
    }
    else
    {
        memcpy(digits_other, dynamic_cast<bigint_implementation const*>(other)->_digits, sizeof(unsigned int) * size_number_other);
    }

    if (size_number_other != size_number_this ||
        size_number_this != size_number_other)
    {
        deallocate_with_guard(digits_this);
        deallocate_with_guard(digits_other);

        return false;
    }

    for (int i = 0; i < size_number_this; i++)
    {
        if (digits_this[i] != digits_other[i])
        {
            deallocate_with_guard(digits_this);
            deallocate_with_guard(digits_other);

            return false;
        }
    }

    deallocate_with_guard(digits_this);
    deallocate_with_guard(digits_other);

    return true;
}

bool bigint_implementation::not_equals(
        bigint const *other) const
{
    return !equals(other);
}

//end region comparison


//begin region constructor

bigint_implementation::bigint_implementation(
        std::string const &string_number,
        memory *memory_init)
{
    _memory = memory_init;

    if (check_string_number(string_number))
    {
        if (fit_in_int(string_number))
        {
            _sign = std::stoi(string_number);
            _digits = nullptr;
            _size_number = 1;
        }
        else
        {
            auto number = std::move(translate_to_array(string_number));

            _sign = std::get<0>(number);
            _digits = std::get<1>(number);
            _size_number = std::get<2>(number);
        }
    }
    else
    {
        throw std::invalid_argument("ERROR: Invalid number to initialize");
    }
}

//end region constructor


//begin region copy/move semantic

bigint_implementation::bigint_implementation(
        bigint_implementation const &copy_target)
{

}

bigint_implementation &bigint_implementation::operator=(
        bigint_implementation const &copy_target)
{
    return *this;
}

bigint_implementation::bigint_implementation(
        bigint_implementation &&move_target) noexcept
{

}

bigint_implementation &bigint_implementation::operator=(
        bigint_implementation &&move_target) noexcept
{
    return *this;
}

//end region copy/move semantic


//begin region destructor

bigint_implementation::~bigint_implementation()
{
    if (_digits != nullptr)
    {
        deallocate_with_guard(_digits);
    }
}

//end region destructor


//begin region output

std::ostream& operator<<(
        std::ostream &stream,
        const bigint_implementation *target_output)
{
    return stream << target_output->translate_to_string_number();
}

std::ostream& operator<<(
        std::ostream &stream,
        bigint const *target_output)
{
    return stream << reinterpret_cast<const bigint_implementation*>(target_output);
}

//end region output
