#include <iostream>
extern "C" {
    // GPIO declarations
    #include "pigpio.h"
}
int main(int argc, char * argv[])
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}