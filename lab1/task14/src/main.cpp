#include <iostream>
#include <cstring>
#include "associative_container.h"
#include "binary_search_tree.h"
#include "splay_tree.h"
#include "memory.h"
#include "allocator_list.h"
#include "allocator_descriptor.h"
#include "allocator_buddies.h"

class compare_int
{
public:

    int operator()(int first, int second)
    {
        return first - second;
    }
};

void binary_search_tree_demo()
{
    srand(time(NULL));

    builder *builder = new builder_concrete();
    logger *log = builder
            ->add_stream("log.txt", logger::severity::TRACE)
            ->build();

    memory *mem1 = new allocator_list(100000, nullptr);
    memory *mem2 = new allocator_descriptor(50000, mem1);
    memory *mem = new allocator_buddies(10000, nullptr, mem2);

    auto *tree = new splay_tree<int, std::string, compare_int>(nullptr, log);

    *tree += associative_container<int, std::string>::key_value_pair{3, std::move(std::string("1234"))};
    *tree += associative_container<int, std::string>::key_value_pair{2, std::move(std::string("2345"))};
    *tree += associative_container<int, std::string>::key_value_pair{4, std::move(std::string("3456"))};
    *tree += associative_container<int, std::string>::key_value_pair{1, std::move(std::string("4567"))};
    *tree += associative_container<int, std::string>::key_value_pair{5, std::move(std::string("5678"))};
    *tree += associative_container<int, std::string>::key_value_pair{0, std::move(std::string("6789"))};
    *tree += associative_container<int, std::string>::key_value_pair{6, std::move(std::string("7890"))};

    tree->remove(3);
    tree->remove(2);
    tree->remove(4);
    tree->remove(1);
    tree->remove(5);
    tree->remove(0);
    tree->remove(6);

    delete tree;
    delete mem;
    delete mem2;
    delete mem1;
    delete log;
    delete builder;
}

int main()
{
    binary_search_tree_demo();

    return 0;
}