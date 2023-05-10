#include <iostream>
#include <cstring>
#include "associative_container.h"
#include "binary_search_tree.h"
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

int main()
{
    builder *build_log = new builder_concrete();

    logger *log_alc = build_log->add_stream("log.txt", logger::severity::TRACE)
                               ->build();

    memory *alc_descriptor = new allocator_descriptor(10000000,
                                                      nullptr,
                                                      log_alc,
                                                      memory::METHOD_SUITABLE::FIRST_SUITABLE);

    associative_container<int, std::string> *tree = new binary_search_tree<int, std::string, functor_int>(alc_descriptor, log_alc);

    tree->insert(1, "a");
    tree->insert(2, "b");
    tree->insert(-1, "d");
    tree->insert(3, "e");
    tree->insert(4, "e");

    tree->bypass_container();

    tree->remove(2);
    tree->remove(1);
    tree->remove(-1);
    tree->remove(3);
    tree->remove(4);

    tree->bypass_container();

    delete tree;
    delete alc_descriptor;
    delete log_alc;
    delete build_log;

    return 0;
}