#include <iostream>
#include "bigint_implementation.h"
#include "bigint_multiplication.h"
#include "bigint_division.h"
#include "long_number.h"
#include "string_number.h"

void factorial_bigint(int n)
{
    auto start = clock();

    bigint *factorial = new bigint_implementation("1");
    bigint::bigint_multiplication *multiplication = new multiplication_karatsuba();

    for (int i = 2; i <= n; i++)
    {
        bigint *temp = new bigint_implementation(std::to_string(i));
        bigint *temp_res = multiplication->multiply(factorial, temp);

        delete factorial;
        delete temp;

        factorial = temp_res;
    }

//    std::cout << factorial << std::endl;
    delete factorial;
    delete multiplication;

    auto end = clock();

    std::cout << (static_cast<double>((end - start)) / CLOCKS_PER_SEC) << std::endl;
}

void test_multiply_naive(
        std::string const &first_item,
        std::string const &second_item)
{
    auto start = clock();

    bigint::bigint_multiplication *multiplication = new multiplication_naive();

    bigint *number_1 = new bigint_implementation(first_item, nullptr);
    bigint *number_2 = new bigint_implementation(second_item, nullptr);

    bigint *result_op = multiplication->multiply(number_1, number_2);
    std::cout << result_op << std::endl;

    delete number_1;
    delete number_2;
    delete result_op;
    delete multiplication;

    auto end = clock();

    std::cout << (static_cast<double>((end - start)) / CLOCKS_PER_SEC) << std::endl;
}

void test_multiply_karatsuba(
        std::string const &first_item,
        std::string const &second_item)
{
    auto start = clock();

    bigint::bigint_multiplication *multiplication = new multiplication_karatsuba();

    bigint *number_1 = new bigint_implementation(first_item, nullptr);
    bigint *number_2 = new bigint_implementation(second_item, nullptr);

    bigint *result_op = multiplication->multiply(number_1, number_2);
    std::cout << result_op << std::endl;

    delete number_1;
    delete number_2;
    delete result_op;
    delete multiplication;

    auto end = clock();

    std::cout << (static_cast<double>((end - start)) / CLOCKS_PER_SEC) << std::endl;
}

//BASE 4294967296

int main()
{
    auto start = clock();

    bigint::bigint_multiplication *multiplication = new multiplication_karatsuba();
    bigint::bigint_division *division = new division_burnickel_ziegler();

    bigint *number_1 = new bigint_implementation("567898765432345678909876543456789876543567898765432345678909876543456789876543567898765432345678909876543456789876543567898765432345678909876543456789876543", nullptr);
    bigint *number_2 = new bigint_implementation("56789876543234567890987654345678987654343242", nullptr);

    std::cout << "number_1: ";
    number_1->output();
    std::cout << "number_2: ";
    number_2->output();

    std::pair<bigint*, bigint*> result_op = division->divide(number_1, number_2, multiplication);
    std::cout << "quotient: " << result_op.first << std::endl;
    std::cout << "remainder: " << result_op.second << std::endl;

    delete number_1;
    delete number_2;
    delete result_op.first;
    delete result_op.second;
    delete multiplication;
    delete division;

    auto end = clock();

    std::cout << (static_cast<double>((end - start)) / CLOCKS_PER_SEC) << std::endl;

    return 0;
}