#include <iostream>
#include <stdexcept>
#include "memory.h"
#include "allocator_descriptor.h"

void fill(int *&arr)
{
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
}

void output(int *&arr)
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

int main()
{
    builder *log_builder = new builder_concrete();
    logger *logger_memory = log_builder->add_stream("log.txt", logger::severity::INFORMATION)
                                       ->build();

    memory *alc = new allocator_descriptor(10000, nullptr, logger_memory, memory::METHOD_SUITABLE::FIRST_SUITABLE);

    auto *arr_1 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_2 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_3 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_4 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_5 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_6 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_7 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));
    auto *arr_8 = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));

    alc->deallocate(arr_1);
    alc->deallocate(arr_7);
    alc->deallocate(arr_5);
    alc->deallocate(arr_4);
    alc->deallocate(arr_3);
    alc->deallocate(arr_8);
    alc->deallocate(arr_2);
    alc->deallocate(arr_6);

    delete alc;
    delete log_builder;
    delete logger_memory;

    return 0;
}