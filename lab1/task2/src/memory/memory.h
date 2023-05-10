#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class memory {
public:
    memory() = default;

    memory(memory const&) = delete;

    memory& operator=(memory const&) = delete;

    virtual ~memory();

    virtual void *allocate(size_t const&) const = 0;

    void *operator+=(size_t const&);

    virtual void deallocate(void*) const = 0;

    void operator-=(void *object);
};

#endif