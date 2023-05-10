#include <iostream>
#include <string>
#include "memory.h"
#include "allocator.h"
#include "builder.h"
#include "builder_concrete.h"
#include "logger.h"
#include "logger_concrete.h"
#include "bigint.h"
#include "bigint_concrete.h"

void factorial_bigint(int bound)
{
    bigint *number = new bigint_concrete("1");

    for (int i = 1; i <= bound; i++)
    {
        bigint *temp = new bigint_concrete(std::to_string(i));

        *number *= temp;

        delete temp;
    }

    std::cout << number << std::endl;

    delete number;
}

void factorial_string_number(int bound)
{
    long_number<std::string> *number = new string_number("1");

    for (int i = 1; i <= bound; i++)
    {
        long_number<std::string> *temp = new string_number(std::to_string(i));

        *number *= temp;

        delete temp;
    }

    std::cout << number->get_number() << std::endl;

    delete number;
}

void factorial_vector_number(int bound)
{
    long_number<vector_type> *number = new vector_number(vector_type{0, 1}, 10);

    for (int i = 1; i <= bound; i++)
    {
        long_number<vector_type> *temp = new vector_number(vector_type{0, i}, 10);

        *number *= temp;

        delete temp;
    }

    vector_type result = number->get_number();

    for (int i = 1; i < result.size(); i++)
    {
        std::cout << result[i];
    }

    std::cout << std::endl;

    delete number;
}

int main(int argc, char **argv)
{
    auto start = clock();
    factorial_bigint(299);
    auto end = clock();

    std::cout << static_cast<double>((end - start)) / CLOCKS_PER_SEC << "с" << std::endl;

    return 0;
}