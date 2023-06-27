#ifndef STRING_NUMBER_H
#define STRING_NUMBER_H

#include <iostream>
#include <string>
#include <sstream>
#include "long_number.h"

class string_number final : public long_number<std::string>
{

private:

    //begin region help functions

    static bool validate_value(
            const std::string&);

    static size_t make_equal_length(
            std::string &,
            std::string &);

    static std::string naive_multiply(
            std::string,
            std::string);

    static std::string karatsuba(
            std::string,
            std::string);

    //end region help functions

public:

    //begin region constructor

    explicit string_number(
            std::string);

    //end region constructor


    //begin region addition

    long_number<std::string> *add(
            const long_number<std::string>*) override;

    //end region addition


    //begin region sum

    long_number<std::string> *sum(
            const long_number<std::string>*) const override;

    //end region sum


    //begin region subtract

    long_number<std::string> *subtract(
            const long_number<std::string>*) override;

    //end region subtract


    //begin region subtraction

    long_number<std::string> *subtraction(
            const long_number<std::string>*) const override;

    //end region subtraction


    //begin region multiply

    long_number<std::string> *multiply(
            const long_number<std::string>*) override;

    //end region multiply


    //begin region multiplication

    long_number<std::string> *multiplication(
            const long_number<std::string>*) const override;

    //end region multiplication


    //begin region div

    long_number<std::string> *div(
            const unsigned long&) override;

    //end region div


    //begin region division

    long_number<std::string> *division(
            const unsigned long&) override;

    //end region division


    //begin region mod

    long_number<std::string> *mod(
            const unsigned long&) override;

    //end region mod


    //begin region module

    long_number<std::string> *module(
            const unsigned long&) override;

    //end region module


    //begin region pow

    long_number<std::string> *pow(
            unsigned long) override;

    //end region pow


    //begin region comparison

    bool lower_than(
            const long_number<std::string>*) const override;

    bool greater_than(
            const long_number<std::string>*) const override;

    bool lower_than_or_equal_to(
            const long_number<std::string>*) const override;

    bool greater_than_or_equal_to(
            const long_number<std::string>*) const override;

    bool equals(
            const long_number<std::string>*) const override;

    bool not_equals(
            const long_number<std::string>*) const override;

    //end region comparison


    //begin region destructor

    ~string_number() override = default;

    //end region destructor

};

#endif // STRING_NUMBER_H