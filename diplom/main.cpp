#include <iostream>
#include "PRNG.h"
#include "ContainerTest.h"
#include "ContainerFunctions.h"


#include <functional> // For std::function and std::bind

int main() {
    sequence::AvailableFunctionsBuilder availableFunctionsBuilder{};
    sequence::AvailableFunctions availableFunctions = availableFunctionsBuilder.addAll()->build();


    return 0;
}
