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
#include "long_number.h"
#include "string_number.h"
#include "vector_number.h"

template<typename tvalue>
std::ostream &operator<<(
        std::ostream &stream,
        const long_number<tvalue> *target_print)
{
    tvalue to_print = target_print->get_number();
    int counter = 0;

    if (to_print[0] == 1 || to_print[0] == 0)
    {
        if (to_print[0] == 1)
        {
            stream << "-";
        }

        counter++;
    }

    for (; counter < to_print.size(); counter++)
    {
        stream << to_print[counter];
    }

    return stream;
}

int main(int argc, char **argv)
{
    builder *log_builder = new builder_concrete();
    logger *log_bigint = log_builder->add_stream("log/log.txt", logger::severity::INFORMATION)
                                    ->build();

    memory *alc = new allocator(100000000, nullptr, log_bigint, memory::METHOD_SUITABLE::FIRST_SUITABLE);

    bigint *res = new bigint_concrete("0", alc);

    for (int i = 1; i <= 100; i++)
    {
        bigint *temp = new bigint_concrete(std::to_string(i), alc);

        *res += temp;

        delete temp;
    }

    std::cout << res << std::endl;

    delete res;
    delete alc;
    delete log_builder;
    delete log_bigint;

    return 0;
}