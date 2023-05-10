cmake_minimum_required(VERSION 3.24)
project(task10)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/allocator_buddies)
include_directories(src/allocator_descriptor)
include_directories(src/allocator_list)
include_directories(src/bigint)
include_directories(src/bigint_concrete)
include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/logger_holder)
include_directories(src/long_number)
include_directories(src/memory)
include_directories(src/memory_holder)
include_directories(src/string_number)
include_directories(src/vector_number)

add_compile_options(-w)

add_executable(task10
        src/allocator_descriptor/allocator_descriptor.cpp
        src/allocator_descriptor/allocator_descriptor.h
        src/allocator_list/allocator_list.cpp
        src/allocator_list/allocator_list.h
        src/allocator_buddies/allocator_buddies.cpp
        src/allocator_buddies/allocator_buddies.h
        src/bigint/bigint.cpp
        src/bigint/bigint.h
        src/bigint_concrete/bigint_concrete.cpp
        src/bigint_concrete/bigint_concrete.h
        src/builder/builder.cpp
        src/builder/builder.h
        src/builder_concrete/builder_concrete.cpp
        src/builder_concrete/builder_concrete.h
        src/logger/logger.cpp
        src/logger/logger.h
        src/logger_concrete/logger_concrete.cpp
        src/logger_concrete/logger_concrete.h
        src/logger_holder/logger_holder.cpp
        src/logger_holder/logger_holder.h
        src/long_number/long_number.cpp
        src/long_number/long_number.h
        src/memory/memory.cpp
        src/memory/memory.h
        src/memory_holder/memory_holder.cpp
        src/memory_holder/memory_holder.h
        src/string_number/string_number.cpp
        src/string_number/string_number.h
        src/vector_number/vector_number.cpp
        src/vector_number/vector_number.h
        src/task10.cpp)
