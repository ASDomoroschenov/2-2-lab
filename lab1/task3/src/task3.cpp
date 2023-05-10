#include <iostream>
#include <stdexcept>
#include "memory.h"
#include "allocator_list.h"

int main()
{
    memory *alc = new allocator_list(1000);

    auto *arr = reinterpret_cast<int*>(alc->allocate(sizeof(int) * 4));

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    std::cout << arr[1] << std::endl;

    alc->deallocate(arr);

    return 0;
}