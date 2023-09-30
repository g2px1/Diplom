//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_CONTAINERTEST_H
#define DIPLOM_CONTAINERTEST_H

#include <cstdio>
#include <utility>


/**
 *  @class ContainerTest
 *  @brief Basic class for testing all types of containers. Stores container itself
 *  @param container container to test
 * */
template<class T>
class ContainerTest {
public:
    explicit ContainerTest(T &&testing_container);

public:
    /**
     * @brief begin test
     * */
    virtual uint64_t test() = 0;
private:
    T container;
};

/**
 * @class SequenceContainerTester
 * @brief Used for testing sequence containers, e.g
 * <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/array">std::array</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/list">std::list</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/forward_list">std::forward_list</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/deque">std::deque</a>,
 * etc.
 * */
template<class T>
class SequenceContainerTester : public ContainerTest<T> {
public:
    explicit SequenceContainerTester(T &&container);

public:
    uint64_t test() override;
};

/**
 * @class AssociativeTester
 * @brief Used for testing associative containers, e.g
 * <a href="https://en.cppreference.com/w/cpp/container/set">std::set</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/multiset">std::multiset</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/map">std::map</a>,
 * <a href="https://en.cppreference.com/w/cpp/container/multimap">std::multimap</a>,
 * etc.
 * */
template<class T>
class AssociativeTester : public ContainerTest<T> {
public:
    explicit AssociativeTester(T &&container);

public:
    uint64_t test() override;
};

/**
 * @class TreeTester
 * @brief Used for testing trees
 * */
template<class T>
class TreeTester : public ContainerTest<T> {
public:
    explicit TreeTester(T &&container);

public:
    uint64_t test() override;
};

#endif //DIPLOM_CONTAINERTEST_H
