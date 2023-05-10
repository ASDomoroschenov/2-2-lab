#include <iostream>
#include <string>
#include "memory.h"
#include "builder.h"
#include "builder_concrete.h"
#include "logger.h"
#include "logger_concrete.h"
#include "bigint.h"
#include "bigint_concrete.h"

int main(int argc, char **argv)
{
    long_number<std::string> *temp_1 = new string_number("123456");
    long_number<std::string> *temp_2 = new string_number("123");
    long_number<std::string> *temp_3 = (*temp_1 / temp_2);

    std::cout << temp_3->get_number() << std::endl;

    return 0;
}