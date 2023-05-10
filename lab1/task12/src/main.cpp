#include <iostream>
#include <cstring>
#include "associative_container.h"
#include "binary_search_tree.h"
#include "avl_tree.h"
#include "memory.h"
#include "allocator_list.h"
#include "allocator_descriptor.h"
#include "allocator_buddies.h"

class functor_int
{
public:

    int operator()(int first, int second)
    {
        return first - second;
    }
};

void binary_search_tree_demo()
{
    builder *builder = new builder_concrete();
    logger *log = builder
            ->add_stream("file1.txt", logger::severity::TRACE)
            ->add_stream("file2.txt", logger::severity::DEBUG)
            ->add_stream("file3.txt", logger::severity::INFORMATION)
            ->add_stream("console", logger::severity::TRACE)
            ->build();

    memory *mem1 = new allocator_list(100000, nullptr);
    memory *mem2 = new allocator_descriptor(50000, mem1);
    memory *mem = new allocator_buddies(10000, nullptr, mem2);

    auto *tree = new binary_search_tree<int, std::string, functor_int>(mem);

    *tree += associative_container<int, std::string>::key_value_pair{0, std::move(std::string("1234"))};
    *tree += associative_container<int, std::string>::key_value_pair{-1, std::move(std::string("2345"))};
    *tree += associative_container<int, std::string>::key_value_pair{1, std::move(std::string("3456"))};
    *tree += associative_container<int, std::string>::key_value_pair{-2, std::move(std::string("4567"))};
    *tree += associative_container<int, std::string>::key_value_pair{2, std::move(std::string("5678"))};
    *tree += associative_container<int, std::string>::key_value_pair{-3, std::move(std::string("6789"))};
    *tree += associative_container<int, std::string>::key_value_pair{3, std::move(std::string("7890"))};

    associative_container<int, std::string>::key_value_pair find;
    (*tree)[&find];

    auto const &str = find._value;
    *const_cast<std::string *>(&str) = "12345678";

    std::cout << "Prefix iterator:" << std::endl;
    auto end_prefix = tree->end_prefix();

    for (auto it = tree->begin_prefix(); it != end_prefix; ++it)
    {
        for (auto x = 0; x < std::get<0>(*it); x++)
        {
            std::cout << "    ";
        }

        std::cout << "key: " << std::get<1>(*it) << ", value: \"" << std::get<2>(*it) << "\"" << std::endl;
    }

    std::cout << std::endl << "Infix iterator:" << std::endl;
    auto end_infix = tree->end_infix();
    for (auto it = tree->begin_infix(); it != end_infix; ++it)
    {
        for (auto x = 0; x < std::get<0>(*it); x++)
        {
            std::cout << "    ";
        }

        std::cout << "key: " << std::get<1>(*it) << ", value: \"" << std::get<2>(*it) << "\"" << std::endl;
    }

    std::cout << std::endl << "Postfix iterator:" << std::endl;
    auto end_postfix = tree->end_postfix();
    for (auto it = tree->begin_postfix(); it != end_postfix; ++it)
    {
        for (auto x = 0; x < std::get<0>(*it); x++)
        {
            std::cout << "    ";
        }

        std::cout << "key: " << std::get<1>(*it) << ", value: \"" << std::get<2>(*it) << "\"" << std::endl;
    }

    auto removed_value = std::move(*tree -= 0);
    std::cout << "removed_value: " << removed_value << std::endl;

    for (auto it = tree->begin_prefix(); it != end_prefix; ++it)
    {
        for (auto x = 0; x < std::get<0>(*it); x++)
        {
            std::cout << "    ";
        }

        std::cout << "key: " << std::get<1>(*it) << ", value: \"" << std::get<2>(*it) << "\"" << std::endl;
    }

    delete tree;
    delete mem;
    delete mem2;
    delete mem1;
    delete log;
    delete builder;
}

int&& foo()
{
    int y = 123;
    int&& x = 0;

    x = y;
    y = 100;

    return std::move(x);
}

int main()
{
    binary_search_tree_demo();

    return 0;
}