#include <iostream>
#include "generator/Generator.h"
#include "utils/test/ContainerTest.h"
#include <cds/container/fcqueue.h>

int main() {
    test::framework::Generator generator(20, 10, 30, 40, 100);
    generator.generate(true);

    test::framework::container::ContainerTest<cds::container::FCQueue<int>> test();
    return 0;
}
