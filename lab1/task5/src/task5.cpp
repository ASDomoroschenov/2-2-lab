#include <iostream>
#include <stdexcept>
#include "memory.h"
#include "allocator_buddies.h"

int main()
{
    srand(time(NULL));
    builder *log_builder = new builder_concrete();
    logger *logger_memory = log_builder->add_stream("log/log.txt", logger::severity::INFORMATION)
                                       ->build();

    memory *alc = new allocator_buddies(1000, logger_memory, nullptr);

    unsigned char *mem = reinterpret_cast<unsigned char*>(alc->allocate(1024 - 4 * sizeof(short)));
    void *mem_1 = alc->allocate(0);

    alc->deallocate(mem_1);
    alc->deallocate(mem);

    delete alc;
    delete log_builder;
    delete logger_memory;

    return 0;
}