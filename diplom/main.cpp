#include <iostream>
#include "generator/Generator.h"

int main() {
    test::framework::Generator generator(10, 10, 40, 40, 100);
    generator.generator(true);
    return 0;
}
