#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class memory
{
public:
    memory(memory const&) = delete;
    
    void operator=(memory const&) = delete;

    memory() = default;
    
    virtual ~memory() = default;

    virtual void *allocate(size_t const &size) const = 0;

    void *operator+=(size_t const &size) const;

    virtual void deallocate(void*) const = 0;

    void operator-=(void *memory_block) const;
};

#endif // MEMORY_H