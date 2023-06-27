#include <iostream>
#include <cstring>
#include "associative_container.h"
#include "memory.h"
#include "allocator_list.h"
#include "allocator_descriptor.h"
#include "allocator_buddies.h"
#include "b_tree.h"
#include <vector>
#include <algorithm>

class compare_int
{

public:

    static int operator()(int first, int second)
    {
        return first - second;
    }

};

int main()
{
    srand(time(NULL));
    associative_container<int, std::string> *tree = new b_tree<int, std::string, compare_int>(5);

    for (int i = 0; i < 10000; i++)
    {
        int rand_key = rand() % 1000000;

        if (!tree->in(rand_key))
        {
            tree->insert(rand_key, "0");
        }
    }

    for (int i = 0; i < 100000; i++)
    {
        int rand_key = rand() % 1000000;

        if (tree->in(rand_key))
        {
            tree->remove(rand_key);
        }
    }

    delete tree;

    return 0;
}