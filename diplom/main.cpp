#include <iostream>
#include "PRNG.h"

int main() {
    PRNG prng;
//    int64_t a = prng.getSeed();
//    std::cout << a << std::endl;
    std::cout << prng.generateNumber64() << std::endl;
    return 0;
}
