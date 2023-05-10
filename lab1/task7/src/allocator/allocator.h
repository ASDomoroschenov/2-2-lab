#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

#include "logger.h"
#include "logger_concrete.h"
#include "builder.h"
#include "builder_concrete.h"
#include "memory.h"
#include "logger_holder.h"

class allocator final : public memory, private logger_holder
{

private:

    void *_allocated_memory;
    memory::METHOD_SUITABLE _method;

public:

    allocator(
            allocator const&) = delete;

    void operator=(
            allocator const&) = delete;

    void *get_next_occupied_block(
            void*) const;
    
    size_t get_memory_size() const;
    
    size_t get_block_size(
            void const*) const;
    
    void *get_first_occupied_block() const;

    void *get_first_suitable_block(
            size_t const &size) const;

    void *get_best_suitable_block(
            size_t const &size) const;
    
    void *get_worse_suitable_block(
            size_t const &size) const;
    
    allocator(
        size_t const &size,
        memory *outer_allocator = nullptr,
        logger *logger_allocator = nullptr,
        memory::METHOD_SUITABLE method_allocation = memory::METHOD_SUITABLE::FIRST_SUITABLE);
    
    void *allocate(
            size_t const &size) const override;

    void deallocate(
            void *deallocated_block) const override;
    
    ~allocator() override;

private:

    logger *get_logger() const override;

};

#endif // ALLOCATOR_H