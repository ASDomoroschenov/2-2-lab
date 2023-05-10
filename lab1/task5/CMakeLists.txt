cmake_minimum_required(VERSION 3.24)
project(task5)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/allocator_buddies)
include_directories(src/memory)

add_executable(task5
        src/builder/builder.h
        src/builder/builder.cpp
        src/builder_concrete/builder_concrete.h
        src/builder_concrete/builder_concrete.cpp
        src/logger/logger.h
        src/logger/logger.cpp
        src/logger_concrete/logger_concrete.h
        src/logger_concrete/logger_concrete.cpp
        src/allocator_buddies/allocator_buddies.h
        src/allocator_buddies/allocator_buddies.cpp
        src/memory/memory.h
        src/memory/memory.cpp
        src/task5.cpp)
