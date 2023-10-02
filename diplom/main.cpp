#include <iostream>
#include "PRNG.h"
#include "ContainerTest.h"


#include <functional> // For std::function and std::bind

int main() {
    PRNG prng;
    std::cout << prng.generateNumber64() << std::endl;


#if 0
    std::vector<int> vec;
    // Define a vector to store std::function objects that can modify vector and receive an int as parameter.
    std::vector<std::function<void(std::vector<int>&, int)>> func_ptrs_with_arg;
    // Store push_back
    func_ptrs_with_arg.emplace_back([](std::vector<int>& v, int value) { v.push_back(value); });
    // Store insert at the beginning of the vector
    func_ptrs_with_arg.emplace_back([](std::vector<int>& v, int value) {
        if (v.size() > value && value >= 0)
            v.insert(v.begin() + value, 100);  // For illustration, inserting 100 at the specified position
    });
    // Store erase
    func_ptrs_with_arg.emplace_back([](std::vector<int>& v, int position) {
        if (position < v.size() && position >= 0)
            v.erase(v.begin() + position);
    });
    // Apply the stored functions with different values.
    func_ptrs_with_arg[0](vec, 10);  // push_back 10
    func_ptrs_with_arg[0](vec, 20);  // push_back 20
    func_ptrs_with_arg[1](vec, 1);   // insert 100 at position 1
    func_ptrs_with_arg[2](vec, 0);   // erase the first element (10)
    for (const auto& v : vec) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
#endif

    return 0;
}
