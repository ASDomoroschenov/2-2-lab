cmake_minimum_required(VERSION 3.24)
project(task12)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-w)

include_directories(src/associative_container)
include_directories(src/binary_search_tree)
include_directories(src/memory)
include_directories(src/logger)
include_directories(src/logger_concrete)
include_directories(src/builder)
include_directories(src/builder_concrete)
include_directories(src/avl_tree)
include_directories(src/memory_holder)
include_directories(src/logger_holder)
include_directories(src/allocator_list)
include_directories(src/allocator_descriptor)
include_directories(src/allocator_buddies)

add_executable(
        task12

        src/builder/builder.h
        src/builder/builder.cpp

        src/builder_concrete/builder_concrete.h
        src/builder_concrete/builder_concrete.cpp

        src/logger/logger.h
        src/logger/logger.cpp

        src/logger_concrete/logger_concrete.h
        src/logger_concrete/logger_concrete.cpp

        src/logger_holder/logger_holder.h
        src/logger_holder/logger_holder.cpp

        src/memory/memory.h
        src/memory/memory.cpp

        src/allocator_list/allocator_list.h
        src/allocator_list/allocator_list.cpp

        src/allocator_descriptor/allocator_descriptor.h
        src/allocator_descriptor/allocator_descriptor.cpp

        src/allocator_buddies/allocator_buddies.h
        src/allocator_buddies/allocator_buddies.cpp

        src/memory_holder/memory_holder.h
        src/memory_holder/memory_holder.cpp

        src/associative_container/associative_container.h
        src/associative_container/associative_container.cpp

        src/binary_search_tree/binary_search_tree.h
        src/binary_search_tree/binary_search_tree.cpp

        src/avl_tree/avl_tree.h
        src/avl_tree/avl_tree.cpp

        src/main.cpp)
