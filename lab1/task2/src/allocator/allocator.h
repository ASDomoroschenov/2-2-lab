#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
#include <sstream>
#include "../memory/memory.h"
#include "../../../task1/src/logger/logger.h"
#include "../../../task1/src/logger_concrete/logger_concrete.h"
#include "../../../task1/src/builder/builder.h"
#include "../../../task1/src/builder_concrete/builder_concrete.h"

class allocator : public memory {
private:
    logger *_logger_allocator;
public:
    allocator();

    allocator(allocator const&) = delete;

    allocator& operator=(allocator const&) = delete;

    void *allocate(size_t const&) const override;

    void deallocate(void *object) const override;

    ~allocator();
};

#endif