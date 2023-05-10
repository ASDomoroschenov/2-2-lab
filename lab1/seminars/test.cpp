#include <iostream>

int main()
{
    int b = 1;
    int c = 2;
    int * const a = &b;

    *a = 1;

    return 0;
}