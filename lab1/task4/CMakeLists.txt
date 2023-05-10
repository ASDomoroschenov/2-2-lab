cmake_minimum_required(VERSION 3.24)
project(task4)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/allocator_descriptor)
include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/memory)

add_compile_options(-w)

add_executable(task4
        src/allocator_descriptor/allocator_descriptor.cpp
        src/allocator_descriptor/allocator_descriptor.h
        src/builder/builder.cpp
        src/builder/builder.h
        src/builder_concrete/builder_concrete.cpp
        src/builder_concrete/builder_concrete.h
        src/logger/logger.cpp
        src/logger/logger.h
        src/logger_concrete/logger_concrete.cpp
        src/logger_concrete/logger_concrete.h
        src/memory/memory.cpp
        src/memory/memory.h
        src/task4.cpp)
