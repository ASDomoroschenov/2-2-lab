#include <iostream>
#include <sstream>
#include <string>
#include "allocator/allocator.h"
#include "memory/memory.h"

int main()
{
    memory *alc = new allocator();
    
    std::string *str = reinterpret_cast<std::string*>(alc->allocate(sizeof(std::string)));
    
    *str = "123";
    
    std::cout << *str << std::endl;

    delete alc;

    return 0;
}