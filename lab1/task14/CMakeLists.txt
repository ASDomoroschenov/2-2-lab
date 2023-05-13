cmake_minimum_required(VERSION 3.24)
project(task14)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/allocator_buddies)
include_directories(src/allocator_descriptor)
include_directories(src/allocator_list)
include_directories(src/associative_container)
include_directories(src/binary_search_tree)
include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/logger_holder)
include_directories(src/memory)
include_directories(src/memory_holder)
include_directories(src/splay_tree)

add_compile_options(-w)

add_executable(task14
        src/allocator_buddies/allocator_buddies.cpp
        src/allocator_buddies/allocator_buddies.h
        src/allocator_descriptor/allocator_descriptor.cpp
        src/allocator_descriptor/allocator_descriptor.h
        src/allocator_list/allocator_list.cpp
        src/allocator_list/allocator_list.h
        src/associative_container/associative_container.cpp
        src/associative_container/associative_container.h
        src/binary_search_tree/binary_search_tree.cpp
        src/binary_search_tree/binary_search_tree.h
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
        src/memory/memory.cpp
        src/memory/memory.h
        src/memory_holder/memory_holder.cpp
        src/memory_holder/memory_holder.h
        src/splay_tree/splay_tree.cpp
        src/splay_tree/splay_tree.h
        src/main.cpp)
