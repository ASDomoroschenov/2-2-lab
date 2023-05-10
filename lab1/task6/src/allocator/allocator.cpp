#include "allocator.h"
#include <sstream>

template <typename T>
std::string to_string(T object)
{
    std::stringstream stream;
    stream << object;

    return stream.str();
}

std::string get_bytes(void *object)
{
    std::string result = "";
    int sign = *reinterpret_cast<int*>(object + sizeof(memory*) + sizeof(size_t));
    size_t size_object = *reinterpret_cast<size_t*>(object + sizeof(memory*));

    if (*reinterpret_cast<size_t*>(object - 2 * sizeof(void*) - sizeof(size_t)) == sizeof(memory*) + sizeof(size_t) + sizeof(int))
    {
        return to_string(sign);
    }

    unsigned int *bytes = reinterpret_cast<unsigned int*>(object + sizeof(memory*) + sizeof(size_t));

    for (int i = 0; i < size_object; i++)
    {
        result += to_string(bytes[i]) + " ";
    }

    return result;
}

logger *allocator::get_logger() const
{
    return *reinterpret_cast<logger**>(_allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*));
}

void *allocator::get_next_occupied_block(void *memory_block) const
{
    return *reinterpret_cast<void**>(memory_block + sizeof(size_t) + sizeof(void*));
}

size_t allocator::get_memory_size() const
{
    return *reinterpret_cast<size_t*>(_allocated_memory);
}

size_t allocator::get_block_size(void const *memory_block) const
{
    return *reinterpret_cast<size_t const*>(memory_block);
}

void *allocator::get_first_occupied_block() const
{
    return *reinterpret_cast<void**>(_allocated_memory + sizeof(size_t));
}

void *allocator::get_first_suitable_block(size_t const &size) const
{
    void *current_occupied_block = get_first_occupied_block();
    void *allocated_block = nullptr;

    if (current_occupied_block == nullptr)
    {
        if (size + sizeof(size_t) + 2 * sizeof(void*) <= get_memory_size())
        {
            allocated_block = _allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*) + sizeof(logger*);
            *reinterpret_cast<size_t*>(allocated_block) = size;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = nullptr;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = nullptr;
            *reinterpret_cast<void**>(_allocated_memory + sizeof(size_t)) = allocated_block;

            return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
        }
    }
    else
    {
        while (current_occupied_block != nullptr)
        {
            void *next_occupied_block = get_next_occupied_block(current_occupied_block);
            
            if (next_occupied_block != nullptr)
            {
                unsigned char *end_adress = reinterpret_cast<unsigned char*>(next_occupied_block);
                unsigned char *current_adress = reinterpret_cast<unsigned char*>(current_occupied_block) + sizeof(size_t) + 2 * sizeof(void*) + get_block_size(current_occupied_block);
                size_t distance = end_adress - current_adress;

                if (size + sizeof(size_t) + 2 * sizeof(void*) <= distance)
                {
                    allocated_block = reinterpret_cast<void*>(current_adress);
                    *reinterpret_cast<size_t*>(allocated_block) = size;
                    *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = current_occupied_block;
                    *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = next_occupied_block;
                    *reinterpret_cast<void**>(current_occupied_block + sizeof(size_t) + sizeof(void*)) = allocated_block;
                    *reinterpret_cast<void**>(next_occupied_block + sizeof(size_t)) = allocated_block;

                    return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
                }
            }
            else
            {
                unsigned char *end_adress = reinterpret_cast<unsigned char*>(_allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*) + sizeof(logger*) + get_memory_size());
                unsigned char *current_adress = reinterpret_cast<unsigned char*>(current_occupied_block + sizeof(size_t) + 2 * sizeof(void*) + get_block_size(current_occupied_block));
                size_t distance = end_adress - current_adress;

                if (size + sizeof(size_t) + 2 * sizeof(void*) <= distance)
                {
                    allocated_block = current_occupied_block + sizeof(size_t) + 2 * sizeof(void*) + get_block_size(current_occupied_block);
                    *reinterpret_cast<size_t*>(allocated_block) = size;
                    *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = current_occupied_block;
                    *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = nullptr;
                    *reinterpret_cast<void**>(current_occupied_block + sizeof(size_t) + sizeof(void*)) = allocated_block;

                    return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
                }
            }

            current_occupied_block = next_occupied_block;
        }
    }

    return nullptr;
}

void *allocator::get_best_suitable_block(size_t const &size) const
{
    void *current_occupied_block = get_first_occupied_block();
    void *allocated_block = nullptr;
    void *prev_block = nullptr;
    void *next_block = nullptr;
    size_t max_size = 0;

    if (current_occupied_block == nullptr)
    {
        if (size + sizeof(size_t) + sizeof(void*) <= get_memory_size())
        {
            allocated_block = _allocated_memory + sizeof(size_t) + sizeof(memory*) + sizeof(logger*) + sizeof(void*);
            *reinterpret_cast<size_t*>(allocated_block) = size;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = nullptr;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = nullptr;
            *reinterpret_cast<void**>(_allocated_memory + sizeof(size_t)) = allocated_block;

            return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
        }
    }
    else
    {
        while (current_occupied_block != nullptr)
        {
            void *next_occupied_block = get_next_occupied_block(current_occupied_block);
            unsigned char *end_address = nullptr;
            unsigned char *current_address = reinterpret_cast<unsigned char*>(current_occupied_block + sizeof(size_t) + 2 * sizeof(void*)) + get_block_size(current_occupied_block);

            if (next_occupied_block == nullptr)
            {
                end_address = reinterpret_cast<unsigned char*>(_allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*) + sizeof(logger*) + get_memory_size());
            }
            else
            {
                end_address = reinterpret_cast<unsigned char*>(next_occupied_block);
            }

            size_t distance = end_address - current_address;

            if (size + sizeof(size_t) + 2 * sizeof(void*) <= distance &&
                distance > max_size)
            {
                prev_block = current_occupied_block;
                next_block = next_occupied_block;
            }

            current_occupied_block = next_occupied_block;
        }

        allocated_block = prev_block + sizeof(size_t) + 2 * sizeof(void*) + get_block_size(prev_block);
        *reinterpret_cast<size_t*>(allocated_block) = size;
        *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = prev_block;
        *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = next_block;
        *reinterpret_cast<void**>(prev_block + sizeof(size_t) + sizeof(void*)) = allocated_block;

        if (next_block != nullptr)
        {
            *reinterpret_cast<void**>(next_block + sizeof(size_t)) = allocated_block;
        }

        return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
    }

    return nullptr;
}

void *allocator::get_worse_suitable_block(size_t const &size) const
{
    void *current_occupied_block = get_first_occupied_block();
    void *allocated_block = nullptr;
    void *prev_block = nullptr;
    void *next_block = nullptr;
    size_t min_size = get_memory_size();

    if (current_occupied_block == nullptr)
    {
        if (size + sizeof(size_t) + sizeof(void*) <= get_memory_size())
        {
            allocated_block = _allocated_memory + sizeof(size_t) + sizeof(memory*) + sizeof(logger*) + sizeof(void*);
            *reinterpret_cast<size_t*>(allocated_block) = size;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = nullptr;
            *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = nullptr;
            *reinterpret_cast<void**>(_allocated_memory + sizeof(size_t)) = allocated_block;

            return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
        }
    }
    else
    {
        while (current_occupied_block != nullptr)
        {
            void *next_occupied_block = get_next_occupied_block(current_occupied_block);
            unsigned char *end_address = nullptr;
            unsigned char *current_address = reinterpret_cast<unsigned char*>(current_occupied_block + sizeof(size_t) + 2 * sizeof(void*)) + get_block_size(current_occupied_block);

            if (next_occupied_block == nullptr)
            {
                end_address = reinterpret_cast<unsigned char*>(_allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*) + sizeof(logger*) + get_memory_size());
            }
            else
            {
                end_address = reinterpret_cast<unsigned char*>(next_occupied_block);
            }

            size_t distance = end_address - current_address;

            if (size + sizeof(size_t) + 2 * sizeof(void*) <= distance &&
                distance < min_size)
            {
                prev_block = current_occupied_block;
                next_block = next_occupied_block;
            }

            current_occupied_block = next_occupied_block;
        }

        allocated_block = prev_block + sizeof(size_t) + 2 * sizeof(void*) + get_block_size(prev_block);
        *reinterpret_cast<size_t*>(allocated_block) = size;
        *reinterpret_cast<void**>(allocated_block + sizeof(size_t)) = prev_block;
        *reinterpret_cast<void**>(allocated_block + sizeof(size_t) + sizeof(void*)) = next_block;
        *reinterpret_cast<void**>(prev_block + sizeof(size_t) + sizeof(void*)) = allocated_block;

        if (next_block != nullptr)
        {
            *reinterpret_cast<void**>(next_block + sizeof(size_t)) = allocated_block;
        }

        return allocated_block + sizeof(size_t) + 2 * sizeof(void*);
    }

    return nullptr;
}

allocator::allocator(
    size_t const &size,
    memory *outer_allocator,
    logger *logger_allocator,
    memory::METHOD_SUITABLE method_allocation)
{
    _method = method_allocation;

    if (outer_allocator != nullptr)
    {
        _allocated_memory = outer_allocator->allocate(size);
    }
    else
    {
        _allocated_memory = ::operator new(size + sizeof(size_t) + sizeof(void*) + sizeof(memory*) + sizeof(logger*));
    }

    size_t *size_memory = reinterpret_cast<size_t*>(_allocated_memory);
    *size_memory = size;

    void **first_occupied_block = reinterpret_cast<void**>(_allocated_memory + sizeof(size_t));
    *first_occupied_block = nullptr;
    
    memory **outer_allocator_space = reinterpret_cast<memory**>(_allocated_memory + sizeof(size_t) + sizeof(void*));
    *outer_allocator_space = outer_allocator;

    logger **logger_space = reinterpret_cast<logger**>(_allocated_memory + sizeof(size_t) + sizeof(void*) + sizeof(memory*));
    *logger_space = logger_allocator;

    if (*logger_space != nullptr)
    {
        (*logger_space)->log("allocator is created", logger::severity::INFORMATION);
        (*logger_space)->log("size of memory allocated for allocator: " + to_string(size), logger::severity::INFORMATION);
    }
}

void *allocator::allocate(size_t const &size) const
{   
    memory *alc = *reinterpret_cast<memory**>(_allocated_memory + sizeof(size_t) + sizeof(void*));
    logger *log_memory = get_logger();
    void *allocated_block = nullptr;

    if (alc == nullptr)
    {
        switch (_method)
        {
            case memory::METHOD_SUITABLE::FIRST_SUITABLE:
                allocated_block = get_first_suitable_block(size);
                break;
            case memory::METHOD_SUITABLE::BEST_SUITABLE:
                allocated_block = get_best_suitable_block(size);
                break;
            case memory::METHOD_SUITABLE::WORSE_SUITABLE:
                allocated_block = get_worse_suitable_block(size);
                break;
            default: break;
        }
        
        if (log_memory != nullptr && allocated_block != nullptr)
        {
            log_memory->log("block (" + to_string(allocated_block - sizeof(size_t) - 2 * sizeof(void*)) + ") size allocated from allocator: " + to_string(size), logger::severity::INFORMATION);
        }
    }
    else
    {
        return alc->allocate(size);
    }

    return allocated_block;
}

void allocator::deallocate(void *deallocated_block) const
{
    if (deallocated_block == nullptr)
    {
        return;
    }

    memory *alc = *reinterpret_cast<memory**>(_allocated_memory + sizeof(size_t) + sizeof(void*));
    logger *log_memory = get_logger();

    if (alc == nullptr)
    {
        void *prev_block = *reinterpret_cast<void**>(deallocated_block - 2 * sizeof(void*));
        void *next_block = *reinterpret_cast<void**>(deallocated_block - sizeof(void*));
        
        if (next_block != nullptr)
        {
            *reinterpret_cast<void**>(next_block + sizeof(size_t)) = prev_block;
        }

        if (prev_block != nullptr)
        {
            *reinterpret_cast<void**>(prev_block + sizeof(size_t) + sizeof(void*)) = next_block;   
        }
    }
    else
    {
        alc->deallocate(deallocated_block);
    }

    if (log_memory != nullptr)
    {
        log_memory->log("deallocated block (" + to_string(deallocated_block - sizeof(size_t) - 2 * sizeof(void*)) + ") : " + get_bytes(deallocated_block), logger::severity::INFORMATION);
    }
}

allocator::~allocator()
{
    logger *log_memory = get_logger();
    memory *alc = *reinterpret_cast<memory**>(_allocated_memory + sizeof(size_t) + sizeof(void*));

    if (log_memory != nullptr)
    {
        log_memory->log("allocator is destroyed", logger::severity::INFORMATION);
    }

    if (alc != nullptr)
    {
        alc->deallocate(_allocated_memory);
    }
    else
    {
        delete _allocated_memory;
    }
}