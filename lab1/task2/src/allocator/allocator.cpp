#include "allocator.h"

template<typename T>
std::string to_string(T object)
{
    std::stringstream stream;
    stream << object;

    return stream.str();
}

std::string get_bytes(void *object)
{
    std::string result = "";
    unsigned char *bytes = reinterpret_cast<unsigned char*>(object);
    size_t size_object = *reinterpret_cast<size_t*>(reinterpret_cast<void**>(object) - 1);

    for (int i = 0; i < size_object; i++)
    {
        result += to_string(static_cast<int>(bytes[i])) + " ";
    }

    return result;
}

allocator::allocator()
{
    builder *log_builder = new builder_concrete();

    _logger_allocator = log_builder->add_stream("log/log.txt", logger::severity::INFORMATION)
                                   ->build();
    
    _logger_allocator->log("allocator is created", logger::severity::INFORMATION);

    delete log_builder;
}

void *allocator::allocate(size_t const &size) const
{
    void *mem = ::operator new(size + sizeof(size_t));
    size_t *size_space = reinterpret_cast<size_t*>(mem);
    *size_space = size;
    
    _logger_allocator->log("block (" + to_string(mem) + ") size allocated from allocator: " + to_string(size), logger::severity::INFORMATION);
    
    return reinterpret_cast<void*>(size_space + 1);
}

void allocator::deallocate(void *object) const
{
    size_t *size_space = reinterpret_cast<size_t*>(object) - 1;
    
    _logger_allocator->log("deallocated block (" + to_string(size_space) + ") : " + get_bytes(object), logger::severity::INFORMATION);
    
    ::operator delete(size_space);
}

allocator::~allocator()
{
    _logger_allocator->log("allocator is destroyed", logger::severity::INFORMATION);
    delete _logger_allocator;
}