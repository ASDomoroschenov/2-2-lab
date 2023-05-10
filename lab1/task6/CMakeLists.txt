cmake_minimum_required(VERSION 3.24)
project(task6)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-w)

include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/memory)
include_directories(src/allocator)
include_directories(src/long_number)
include_directories(src/string_number)
include_directories(src/vector_number)
include_directories(src/bigint)
include_directories(src/bigint_concrete)

add_executable(task6
        src/task6.cpp
        src/builder/builder.h
        src/builder/builder.cpp
        src/builder_concrete/builder_concrete.h
        src/builder_concrete/builder_concrete.cpp
        src/logger/logger.h
        src/logger/logger.cpp
        src/logger_concrete/logger_concrete.h
        src/logger_concrete/logger_concrete.cpp
        src/memory/memory.cpp
        src/memory/memory.h
        src/allocator/allocator.h
        src/allocator/allocator.cpp
        src/long_number/long_number.h
        src/long_number/long_number.cpp
        src/string_number/string_number.h
        src/string_number/string_number.cpp
        src/vector_number/vector_number.h
        src/vector_number/vector_number.cpp
        src/bigint/bigint.h
        src/bigint/bigint.cpp
        src/bigint_concrete/bigint_concrete.h
        src/bigint_concrete/bigint_concrete.cpp)
