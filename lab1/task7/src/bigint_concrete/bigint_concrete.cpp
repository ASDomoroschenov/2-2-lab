#include <cstring>
#include "bigint_concrete.h"

vector_type bigint_concrete::get_vec_number() const
{
    vector_type this_number;

    if (_size_number == 0)
    {
        this_number.push_back(_head_digit < 0);
        this_number.push_back(static_cast<unsigned int>(_head_digit));
    }
    else
    {
        this_number = vector_type(_number, _number + _size_number);
        this_number.insert(this_number.begin(), _head_digit);
    }

    return this_number;
}

memory *bigint_concrete::get_memory() const
{
    return _allocator;
}

logger *bigint_concrete::get_logger() const
{
    return _logger;
}

size_t bigint_concrete::get_size_number() const
{
    return _size_number;
}

bool bigint_concrete::validate_init_value(
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

std::string bigint_concrete::to_10() const
{
    if (_size_number == 0)
    {
        return std::to_string(_head_digit);
    }

    long_number<std::string> *string_base = new string_number(std::to_string(BASE));
    long_number<std::string> *result = new string_number("0");

    for (int i = 0; i < _size_number; i++)
    {
        long_number<std::string> *temp = new string_number(std::to_string(_number[i]));
        long_number<std::string> *pow_res = *string_base ^ (_size_number - i - 1);
        long_number<std::string> *res = *pow_res * temp;

        result->add(res);

        delete temp;
        delete pow_res;
        delete res;
    }

    std::string result_str = _head_digit == 1 ? "-" + result->get_number() : result->get_number();

    delete string_base;
    delete result;

    return result_str;
}

bigint *bigint_concrete::execute_operation(
        const bigint *target,
        OPERATION operation)
{
    vector_type this_number = get_vec_number();
    vector_type target_add_number = reinterpret_cast<const bigint_concrete*>(target)->get_vec_number();

    long_number<vector_type> *this_vec_number = new vector_number(this_number, BASE);
    long_number<vector_type> *target_op_vec_number = new vector_number(target_add_number, BASE);
    vector_type result;

    switch (operation)
    {
        case OPERATION::SUM:
            *this_vec_number += target_op_vec_number;
            break;
        case OPERATION::SUBTRACT:
            *this_vec_number -= target_op_vec_number;
            break;
        case OPERATION::MULT:
            *this_vec_number *= target_op_vec_number;
            break;
        default:
            break;
    }

    result = this_vec_number->get_number();

    delete this_vec_number;
    delete target_op_vec_number;

    if (result.size() == 2)
    {
        std::string string_result;

        if (result[0] == 1)
        {
            string_result = "-";
        }

        string_result += std::to_string(result[1]);

        long_number<std::string> *upper_bound = new string_number(std::to_string(UPPER_BOUND));
        long_number<std::string> *lower_bound = new string_number(std::to_string(LOWER_BOUND));
        long_number<std::string> *this_number = new string_number(string_result);

        if ((*this_number < upper_bound) && (*this_number > lower_bound))
        {
            delete upper_bound;
            delete lower_bound;
            delete this_number;

            _head_digit = std::stoi(string_result);

            if (_number != nullptr)
            {
                deallocate_with_guard(_number);
                _number = nullptr;
                _size_number = 0;
            }

            return this;
        }

        delete upper_bound;
        delete lower_bound;
        delete this_number;
    }

    _size_number = result.size() - 1;
    _head_digit = result[0];

    deallocate_with_guard(_number);
    _number = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * _size_number));

    for (int i = 1; i < result.size(); i++)
    {
        _number[i - 1] = result[i];
    }

    return this;
}

bigint_concrete::bigint_concrete(
        const bigint_concrete *to_copy) :
        _allocator(to_copy->_allocator),
        _logger(to_copy->_logger),
        _head_digit(to_copy->_head_digit),
        _size_number(to_copy->_size_number)
{
    _number = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * _size_number));
    memcpy(_number, to_copy->_number, sizeof(unsigned int) * _size_number);
}

bigint_concrete::bigint_concrete(
        const std::string &target_init,
        memory *allocator_init,
        logger *logger_init) :
        _allocator(allocator_init),
        _logger(logger_init),
        _head_digit(0),
        _size_number(0),
        _number(nullptr)
{
    if (validate_init_value(target_init))
    {
        if (gets_into_int(target_init))
        {
            _head_digit = std::atoi(target_init.c_str());
        }
        else
        {
            _size_number++;

            std::string number = target_init;

            if (number[0] == '-')
            {
                _head_digit = 1;
                number = number.substr(1, number.length() - 1);
            }

            long_number<std::string> *string_base = new string_number(std::to_string(BASE));
            long_number<std::string> *temp = new string_number(number);

            while (*temp > string_base)
            {
                *temp /= BASE;
                _size_number++;
            }

            delete temp;

            _number = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int) * _size_number));

            long_number<std::string> *this_number = new string_number(number);
            int counter = 1;

            while (*this_number > string_base)
            {
                _number[_size_number - counter++] = static_cast<unsigned int>(std::atol((*this_number % BASE)->get_number().c_str()));
                *this_number /= BASE;
            }

            _number[_size_number - counter] = static_cast<unsigned int>(std::atol(this_number->get_number().c_str()));

            delete this_number;
            delete string_base;
        }
    }
    else
    {
        throw std::invalid_argument("Invalid initial value");
    }
}

bigint *bigint_concrete::add(
        const bigint *target_add)
{
    return execute_operation(target_add, OPERATION::SUM);
}

bigint *bigint_concrete::sum(
        const bigint *target_sum) const
{
    bigint *new_obj = new bigint_concrete(this);

    return *new_obj += target_sum;
}

bigint *bigint_concrete::subtract(
        const bigint *target_sub)
{
    return execute_operation(target_sub, OPERATION::SUBTRACT);
}

bigint *bigint_concrete::subtraction(
        const bigint *target_subtraction) const
{
    bigint *new_obj = new bigint_concrete(this);

    return *new_obj -= target_subtraction;
}

bigint *bigint_concrete::mult(
        const bigint *target_mult)
{
    return execute_operation(target_mult, OPERATION::MULT);
}

bigint *bigint_concrete::multiplication(
        const bigint *target_multiplication) const
{
    bigint *new_obj = new bigint_concrete(this);

    return *new_obj *= target_multiplication;
}

bool bigint_concrete::lower_than(
        const bigint *target_cmp) const
{
    vector_type this_number = get_vec_number();
    vector_type target_add_number = reinterpret_cast<const bigint_concrete*>(target_cmp)->get_vec_number();

    long_number<vector_type> *this_vec_number = new vector_number(this_number, BASE);
    long_number<vector_type> *target_cmp_vec_number = new vector_number(target_add_number, BASE);

    bool result = *this_vec_number < target_cmp_vec_number;

    delete this_vec_number;
    delete target_cmp_vec_number;

    return result;
}

bool bigint_concrete::greater_than(
        const bigint *target_cmp) const
{
    return !lower_than(target_cmp);
}

bool bigint_concrete::lower_than_or_equal_to(
        const bigint *target_cmp) const
{
    return lower_than(target_cmp) || equals(target_cmp);
}

bool bigint_concrete::greater_than_or_equal_to(
        const bigint *target_cmp) const
{
    return greater_than(target_cmp) || equals(target_cmp);
}

bool bigint_concrete::equals(
        const bigint *target_cmp) const
{
    return !(lower_than(target_cmp) || greater_than(target_cmp));
}

bool bigint_concrete::not_equals(
        const bigint *target_cmp) const
{
    return !equals(target_cmp);
}

bigint_concrete::~bigint_concrete()
{
    deallocate_with_guard(_number);
}

void bigint_concrete::output() const
{
    if (_size_number == 0)
    {
        std::cout << _head_digit << std::endl;
    }
    else
    {
        std::cout << _head_digit << " ";

        for (int i = 0; i < _size_number; i++)
        {
            std::cout << _number[i] << " ";
        }

        std::cout << std::endl;
    }
}

std::ostream& operator<<(
        std::ostream &stream,
        const bigint_concrete *target_output)
{
    return stream << target_output->to_10();
}

std::ostream& operator<<(
        std::ostream &stream,
        const bigint *target_output)
{
    return stream << reinterpret_cast<const bigint_concrete*>(target_output);
}