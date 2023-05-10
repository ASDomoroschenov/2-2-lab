cmake_minimum_required(VERSION 3.24)
project(task3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/memory)
include_directories(src/allocator_list)

add_executable(task3
        src/builder/builder.h
        src/builder/builder.cpp

        src/builder_concrete/builder_concrete.h
        src/builder_concrete/builder_concrete.cpp

        src/logger/logger.h
        src/logger/logger.cpp

        src/logger_concrete/logger_concrete.h
        src/logger_concrete/logger_concrete.cpp

        src/memory/memory.h
        src/memory/memory.cpp

        src/allocator_list/allocator_list.h
        src/allocator_list/allocator_list.cpp

        src/task3.cpp)
