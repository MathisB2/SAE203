#include <iostream>
#include "vector.h"

int main(int argc, char *argv[])
{
    Vector v1(20,20);

    std::cout << v1.magnitude << std::endl;
    v1 = v1/v1.magnitude;
    std::cout << v1.magnitude << std::endl;
    return EXIT_SUCCESS;
}
