#include "bigint_concrete.h"
#include <sstream>
#include <string>
#include <cstring>

template<typename T>
std::string bigint_concrete::to_string(
        T object)
{
    std::stringstream stream;
    stream << object;

    return stream.str();
}

bool bigint_concrete::validate_value(
        const std::string &value)
{
    std::string temp = value;

    if (value.length() == 0 ||
        value[0] == '+')
    {
        return false;
    }

    if (value[0] == '-')
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

bool bigint_concrete::gets_into_int(
        const std::string &number)
{
    long_number<std::string> *upper_bound = new string_number(std::to_string(UPPER_BOUND));
    long_number<std::string> *lower_bound = new string_number(std::to_string(LOWER_BOUND));
    long_number<std::string> *this_number = new string_number(number);

    if ((*this_number < upper_bound) && (*this_number > lower_bound))
    {
        delete upper_bound;
        delete lower_bound;
        delete this_number;

        return true;
    }

    delete upper_bound;
    delete lower_bound;
    delete this_number;

    return false;
}

size_t bigint_concrete::get_size() const
{
    return *reinterpret_cast<size_t*>(_number_representation + sizeof(memory*));
}

void *bigint_concrete::get_representation() const
{
    return _number_representation;
}

void *bigint_concrete::to_base(
        std::string number,
        memory *alc)
{
    void *number_base = nullptr;

    if (gets_into_int(number))
    {
        number_base = alc->allocate(sizeof(memory*) + sizeof(size_t) + sizeof(int));
        *reinterpret_cast<memory**>(number_base) = alc;
        *reinterpret_cast<size_t*>(number_base + sizeof(memory*)) = 1;
        *reinterpret_cast<int*>(number_base + sizeof(memory*) + sizeof(size_t)) = std::atoi(number.c_str());

        return number_base;
    }

    int sign = 0;
    unsigned int remainder = 0;
    size_t size_number = 1;

    if (number[0] == '-')
    {
        sign = 1;
        number = number.substr(1, number.length() - 1);
    }

    long_number<std::string> *string_base = new string_number(std::to_string(BASE));
    long_number<std::string> *temp = new string_number(number);

    while (*temp > string_base)
    {
        *temp /= BASE;
        size_number++;
    }

    delete temp;

    number_base = alc->allocate(sizeof(memory*) + sizeof(size_t) + sizeof(int) + sizeof(unsigned int) * size_number);
    *reinterpret_cast<memory**>(number_base) = alc;
    *reinterpret_cast<size_t*>(number_base + sizeof(memory*)) = size_number;
    *reinterpret_cast<int*>(number_base + sizeof(memory*) + sizeof(size_t)) = sign;

    unsigned int counter = 1;
    auto *array_digits = reinterpret_cast<unsigned int*>(number_base + sizeof(memory*) + sizeof(size_t) + sizeof(int));

    long_number<std::string> *this_number = new string_number(number);

    while (*this_number > string_base)
    {
        long_number<std::string> *mod_res = *this_number % BASE;

        remainder = static_cast<unsigned int>(std::atol((mod_res)->get_number().c_str()));
        *this_number /= BASE;
        array_digits[size_number - counter++] = remainder;

        delete mod_res;
    }

    array_digits[size_number - counter] = static_cast<unsigned int>(std::atol(this_number->get_number().c_str()));

    delete this_number;
    delete string_base;

    return number_base;
}

std::string bigint_concrete::to_10() const
{
    int sign_this = *reinterpret_cast<int*>(_number_representation + sizeof(memory*) + sizeof(size_t));
    size_t len_number = *reinterpret_cast<size_t*>(_number_representation + sizeof(memory*));

    long_number<std::string> *string_base = new string_number(std::to_string(BASE));
    long_number<std::string> *result = new string_number("0");

    if (is_int_number(_number_representation))
    {
        delete string_base;
        delete result;

        return to_string(sign_this);
    }

    unsigned int *array_digits = get_array_digits();
    size_t size = get_size();

    for (int i = 0; i < size; i++)
    {
        long_number<std::string> *temp = new string_number(std::to_string(array_digits[i]));
        long_number<std::string> *pow_res = *string_base ^ (size - i - 1);
        long_number<std::string> *res = *pow_res * temp;

        *result += res;

        delete temp;
        delete pow_res;
        delete res;
    }

    std::string result_str = sign_this == 1 ? "-" + result->get_number() : result->get_number();

    delete string_base;
    delete result;

    return result_str;
}

void *bigint_concrete::set_number(
        vector_type result,
        memory *alc)
{
    void *new_number = nullptr;
    std::string str_number = (result[0] == 1) ? ("-" + std::to_string(result[1])) : (std::to_string(result[1]));

    if (result.size() == 2 && gets_into_int(str_number))
    {
        new_number = alc->allocate(sizeof(memory*) + sizeof(size_t) + sizeof(int));
        *reinterpret_cast<memory**>(new_number) = alc;
        *reinterpret_cast<size_t*>(new_number + sizeof(memory*)) = result.size() - 1;
        *reinterpret_cast<int*>(new_number + sizeof(memory*) + sizeof(size_t)) = std::atoi(str_number.c_str());
    }
    else
    {
        new_number = alc->allocate(sizeof(memory*) + sizeof(size_t) + sizeof(int) + sizeof(unsigned int) * (result.size() - 1));
        *reinterpret_cast<memory**>(new_number) = alc;
        *reinterpret_cast<size_t*>(new_number + sizeof(memory*)) = result.size() - 1;
        *reinterpret_cast<int*>(new_number + sizeof(memory*) + sizeof(size_t)) = result[0];
        auto *array_digits = reinterpret_cast<unsigned int*>(new_number + sizeof(memory*) + sizeof(size_t) + sizeof(int));

        for (int i = 1; i < result.size(); i++)
        {
            array_digits[i - 1] = result[i];
        }
    }

    return new_number;
}

bool bigint_concrete::is_int_number(
        void *number)
{
    return *reinterpret_cast<size_t*>(number - 2 * sizeof(void*) - sizeof(size_t)) == sizeof(memory*) + sizeof(size_t) + sizeof(int);
}

unsigned int *bigint_concrete::get_array_digits() const
{
    return reinterpret_cast<unsigned int*>(_number_representation + sizeof(memory*) + sizeof(size_t) + sizeof(int));
}

vector_type bigint_concrete::get_vector(
        void *other) const
{
    auto *begin = reinterpret_cast<unsigned int*>(other + sizeof(memory*) + sizeof(size_t));
    auto *end = begin + get_size() + 1;
    vector_type result(begin, end);

    return result;
}

bigint_concrete::bigint_concrete(
        void *target_copy)
{
    memory *alc = *reinterpret_cast<memory**>(target_copy);

    if (is_int_number(target_copy))
    {
        size_t to_allocate = sizeof(memory*) + sizeof(size_t) + sizeof(int);
        _number_representation = alc->allocate(to_allocate);
        memcpy(_number_representation, target_copy, to_allocate);
    }
    else
    {
        size_t len_number = *reinterpret_cast<size_t*>(target_copy + sizeof(memory*));
        size_t to_allocate = sizeof(memory*) + sizeof(size_t) + sizeof(int) + len_number * sizeof(unsigned int);
        _number_representation = alc->allocate(to_allocate);
        memcpy(_number_representation, target_copy, to_allocate);
    }
}

bigint_concrete::bigint_concrete(
        const std::string &number,
        memory *alc)
{
    if (validate_value(number))
    {
        _number_representation = to_base(number, alc);
    }
    else
    {
        throw std::invalid_argument("Invalid initial value");
    }
}

bigint *bigint_concrete::add(
        bigint const * const summand)
{
    int sign_this = *reinterpret_cast<int*>(_number_representation + sizeof(memory*) + sizeof(size_t));
    int sign_other = *reinterpret_cast<int*>(summand->get_representation() + sizeof(memory*) + sizeof(size_t));
    unsigned int remainder = 0;
    memory *alc = *reinterpret_cast<memory**>(_number_representation);
    vector_type result;
    vector_type number_representation;
    vector_type addendum;

    if (is_int_number(_number_representation))
    {
        number_representation.push_back(sign_this < 0);
        number_representation.push_back(static_cast<unsigned int>(abs(sign_this)));
    }
    else
    {
        number_representation = get_vector(_number_representation);
    }

    if (is_int_number(summand->get_representation()))
    {
        addendum.push_back(sign_other < 0);
        addendum.push_back(static_cast<unsigned int>(abs(sign_other)));
    }
    else
    {
        addendum = get_vector(summand->get_representation());
    }

    if (addendum[0] == 1 && number_representation[0] == 1)
    {
        result.push_back(1);
    }
    else
    {
        if (addendum[0] == 0 && number_representation[0] == 0)
        {
            result.push_back(0);
        }
        else
        {
            bigint *copy_number = new bigint_concrete(summand->get_representation());
            memory *alc = *reinterpret_cast<memory**>(summand->get_representation());
            void *number = copy_number->get_representation();
            size_t len_number = *reinterpret_cast<size_t*>(number + sizeof(memory*));
            int sign = *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t));

            if (is_int_number(number))
            {
                *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t)) = sign > 0 ? -sign : abs(sign);
            }
            else
            {
                *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t)) = sign == 0 ? 1 : 0;
            }

            bigint *result = subtract(copy_number);
            delete copy_number;

            return result;
        }
    }

    if (number_representation.size() < addendum.size())
    {
        size_t count_zeros = abs(number_representation.size() - addendum.size());

        for (int i = 0; i < count_zeros; i++)
        {
            number_representation.insert(number_representation.begin() + 1, 0);
        }
    }

    if (addendum.size() < number_representation.size())
    {
        size_t count_zeros = abs(number_representation.size() - addendum.size());

        for (int i = 0; i < count_zeros; i++)
        {
            addendum.insert(addendum.begin() + 1, 0);
        }
    }

    for(int i = addendum.size() - 1; i >= 1; i--)
    {
        result.insert(result.begin() + 1, (static_cast<unsigned long>(number_representation[i]) + static_cast<unsigned long>(addendum[i]) + remainder) % BASE);
        remainder = (static_cast<unsigned long>(number_representation[i]) + static_cast<unsigned long>(addendum[i]) + remainder) / BASE;
    }

    if (remainder)
    {
        result.insert(result.begin() + 1, remainder);
    }

    alc->deallocate(_number_representation);
    _number_representation = set_number(result, alc);

    return this;
}

bigint *bigint_concrete::sum(
        bigint const * const summand) const
{
    bigint *new_obj = new bigint_concrete(_number_representation);

    return new_obj->add(summand);
}

bigint *bigint_concrete::subtract(
        bigint const * const subtrahend_number)
{
    int sign_this = *reinterpret_cast<int*>(_number_representation + sizeof(memory*) + sizeof(size_t));
    int sign_other = *reinterpret_cast<int*>(subtrahend_number->get_representation() + sizeof(memory*) + sizeof(size_t));
    memory *alc = *reinterpret_cast<memory**>(_number_representation);
    vector_type result;
    vector_type number_representation;
    vector_type subtrahend;
    short sign_minuend = 0;
    short sign_subtrahend = 0;

    if (is_int_number(_number_representation))
    {
        number_representation.push_back(sign_this < 0);
        number_representation.push_back(abs(sign_this));
        sign_minuend = sign_this < 0 ? -1 : 1;
    }
    else
    {
        number_representation = get_vector(_number_representation);
        sign_minuend = number_representation[0] == 1 ? -1 : 1;
    }

    if (is_int_number(subtrahend_number->get_representation()))
    {
        subtrahend.push_back(sign_other < 0);
        subtrahend.push_back(abs(sign_other));
        sign_subtrahend = sign_other < 0 ? -1 : 1;
    }
    else
    {
        subtrahend = get_vector(subtrahend_number->get_representation());
        sign_subtrahend = subtrahend[0] == 1 ? -1 : 1;
    }

    if ((sign_minuend == -1 && sign_subtrahend == -1) ||
        (sign_minuend == 1 && sign_subtrahend == 1))
    {
        result.push_back(lower_than(subtrahend_number));
    }
    else
    {
        bigint *copy_number = new bigint_concrete(subtrahend_number->get_representation());
        memory *alc = *reinterpret_cast<memory**>(subtrahend_number->get_representation());
        void *number = copy_number->get_representation();
        size_t len_number = *reinterpret_cast<size_t*>(number + sizeof(memory*));
        int sign = *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t));

        if (is_int_number(number))
        {
            *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t)) = sign > 0 ? -sign : abs(sign);
        }
        else
        {
            *reinterpret_cast<int*>(number + sizeof(memory*) + sizeof(size_t)) = sign == 0 ? 1 : 0;
        }

        bigint *result = add(copy_number);
        delete copy_number;

        return result;
    }

    if (number_representation.size() < subtrahend.size())
    {
        size_t count_zeros = abs(number_representation.size() - subtrahend.size());

        for (int i = 0; i < count_zeros; i++)
        {
            number_representation.insert(number_representation.begin() + 1, 0);
        }
    }

    if (subtrahend.size() < number_representation.size())
    {
        size_t count_zeros = abs(number_representation.size() - subtrahend.size());

        for (int i = 0; i < count_zeros; i++)
        {
            subtrahend.insert(subtrahend.begin() + 1, 0);
        }
    }

    if (sign_minuend == -1 && sign_subtrahend == -1)
    {
        if (this < subtrahend_number)
        {
            subtrahend.swap(number_representation);
        }
    }
    else
    {
        if (this > subtrahend_number)
        {
            subtrahend.swap(number_representation);
        }
    }

    for (size_t i = subtrahend.size() - 1; i >= 1; i--)
    {
        if ((subtrahend[i] < number_representation[i]) && i > 2)
        {
            subtrahend[i - 1]--;
            int sign = sign_subtrahend * (static_cast<long long>(subtrahend[i]) + BASE) - sign_minuend * (static_cast<long long>(number_representation[i])) < 0 ? -1 : 1;
            result.insert(result.begin() + 1, sign * (sign_subtrahend * (static_cast<long long>(subtrahend[i]) + BASE) - sign_minuend * (static_cast<long long>(number_representation[i]))));
        }
        else
        {
            int sign = sign_subtrahend * (static_cast<long long>(subtrahend[i])) - sign_minuend * (static_cast<long long>(number_representation[i])) < 0 ? -1 : 1;
            result.insert(result.begin() + 1, sign * (sign_subtrahend * (static_cast<long long>(subtrahend[i])) - sign_minuend * (static_cast<long long>(number_representation[i]))));
        }
    }

    alc->deallocate(_number_representation);
    _number_representation = set_number(result, alc);

    return this;
}

bigint *bigint_concrete::subtraction(
        bigint const * const subtrahend_number) const
{
    bigint *new_obj = new bigint_concrete(_number_representation);

    return new_obj->subtract(subtrahend_number);
}

bool bigint_concrete::lower_than(
        const bigint *other) const
{
    int sign_this = *reinterpret_cast<int*>(_number_representation + sizeof(memory*) + sizeof(size_t));
    int sign_other = *reinterpret_cast<int*>(other->get_representation() + sizeof(memory*) + sizeof(size_t));
    vector_type number_representation;
    vector_type to_compare;

    if (is_int_number(_number_representation))
    {
        number_representation.push_back(sign_this < 0);
        number_representation.push_back(abs(sign_this));
    }
    else
    {
        number_representation = get_vector(_number_representation);
    }

    if (is_int_number(other->get_representation()))
    {
        to_compare.push_back(sign_other < 0);
        to_compare.push_back(abs(sign_other));
    }
    else
    {
        to_compare = get_vector(other->get_representation());
    }

    if (number_representation[0] == 1 && to_compare[0] == 0)
    {
        return true;
    }

    if (number_representation[0] == 0 && to_compare[0] == 1)
    {
        return false;
    }

    if (number_representation.size() < to_compare.size())
    {
        return !(number_representation[0] == 1 && to_compare[0] == 1);
    }

    if (number_representation.size() > to_compare.size())
    {
        return number_representation[0] == 1 && to_compare[0] == 1;
    }

    for (int i = 1; i < number_representation.size(); i++)
    {
        if (number_representation[i] < to_compare[i])
        {
            if (number_representation[0] == 1)
            {
                return false;
            }

            return true;
        }
        else
        {
            if (number_representation[i] > to_compare[i])
            {
                if (number_representation[0] == 1)
                {
                    return true;
                }

                return false;
            }
        }
    }

    return false;
}

bool bigint_concrete::greater_than(
        const bigint *other) const
{
    return !lower_than(other);
}

bool bigint_concrete::lower_than_or_equal_to(
        const bigint *other) const
{
    return lower_than(other) || equals(other);
}

bool bigint_concrete::greater_than_or_equal_to(
        const bigint *other) const
{
    return greater_than(other) || equals(other);
}

bool bigint_concrete::equals(
        const bigint *other) const
{
    int sign_this = *reinterpret_cast<int*>(_number_representation + sizeof(memory*) + sizeof(size_t));
    int sign_other = *reinterpret_cast<int*>(other->get_representation() + sizeof(memory*) + sizeof(size_t));
    vector_type number_representation;
    vector_type to_compare;

    if (sign_this != 1 && sign_this != 0)
    {
        number_representation.push_back(sign_this < 0);
        number_representation.push_back(sign_this);
    }
    else
    {
        number_representation = get_vector(_number_representation);
    }

    if (sign_other != 1 && sign_other != 0)
    {
        to_compare.push_back(sign_other < 0);
        to_compare.push_back(sign_other);
    }
    else
    {
        to_compare = get_vector(other->get_representation());
    }

    if (number_representation[0] != to_compare[0] ||
        number_representation.size() != to_compare.size())
    {
        return false;
    }

    for (int i = 1; i < number_representation.size(); i++)
    {
        if (number_representation[i] != to_compare[i])
        {
            return false;
        }
    }

    return true;
}

bool bigint_concrete::not_equals(
        const bigint *other) const
{
    return !equals(other);
}

bigint_concrete::~bigint_concrete()
{
    memory *alc = *reinterpret_cast<memory**>(_number_representation);
    alc->deallocate(_number_representation);
}

std::ostream& operator<<(
        std::ostream &stream,
        const bigint_concrete *item)
{
    return stream << item->to_10();
}

std::ostream& operator<<(
        std::ostream& stream,
        const bigint *item)
{
    return stream << reinterpret_cast<const bigint_concrete*>(item);
}