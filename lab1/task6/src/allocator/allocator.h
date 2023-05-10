#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../../../task1/src/logger/logger.h"
#include "../../../task1/src/logger_concrete/logger_concrete.h"
#include "../../../task1/src/builder/builder.h"
#include "../../../task1/src/builder_concrete/builder_concrete.h"
#include "../memory/memory.h"
#include <iostream>

class allocator final : public memory
{
private:
    void *_allocated_memory;
    memory::METHOD_SUITABLE _method;
public:
    allocator(allocator const&) = delete;

    allocator& operator=(allocator const&) = delete;

    logger *get_logger() const;

    void *get_next_occupied_block(void *memory_block) const;
    
    size_t get_memory_size() const;
    
    size_t get_block_size(void const *memory_block) const;
    
    void *get_first_occupied_block() const;

    void *get_first_suitable_block(size_t const &size) const;

    void *get_best_suitable_block(size_t const &size) const;
    
    void *get_worse_suitable_block(size_t const &size) const;
    
    allocator(
        size_t const &size,
        memory *outer_allocator = nullptr,
        logger *logger_allocator = nullptr,
        memory::METHOD_SUITABLE method_allocation = memory::METHOD_SUITABLE::FIRST_SUITABLE);
    
    void *allocate(size_t const &size) const override;
    
    void comapct_memory() const;
    
    void deallocate(void *deallocated_block) const override;
    
    ~allocator();
};

#endif // ALLOCATOR_H