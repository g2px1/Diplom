#include <iostream>
#include <functional>
#include "PRNG.h"
#include "ContainerTest.h"
#include "ContainerFunctions.h"
#include "Pool.h"
#include "ContainerPreparer.h"

int main() {
    sequence::AvailableFunctionsBuilder availableFunctionsBuilder{};
    sequence::AvailableFunctions availableFunctions = availableFunctionsBuilder.addAll()->build();

    PRNG prng(1);

    std::vector<int64_t> containerToTest;
    ContainerPreparer<std::vector<int64_t>> containerPreparer(availableFunctions);
    SequenceContainerTester<std::vector<int64_t>, int64_t> sequenceContainerTester =
            SequenceContainerTester<std::vector<int64_t>, int64_t>(containerToTest, containerPreparer, 10000000);

    std::thread th([&sequenceContainerTester] {
        Pool<SequenceContainerTester<std::vector<int64_t>, int64_t>, 4> pool(sequenceContainerTester);
        pool.startThreads();
        pool.joinThreads();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    th.join();
    return 0;
}
