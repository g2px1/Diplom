//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_CONTAINERTEST_H
#define DIPLOM_CONTAINERTEST_H

#include <cstdio>
#include <utility>
#include "DurationCounter.h"
#include "PRNG.h"
#include "ContainerPreparer.h"
#include "Generator.h"

/**
 *  @class ContainerTest
 *  @brief Basic class for testing all types of containers. Stores container itself
 * */
template<class T>
class ContainerTest {
public:
#if 0
    explicit ContainerTest(T &&testing_container, ContainerPreparer<T> &&containerPreparer);
#endif
    explicit ContainerTest(T &testing_container, ContainerPreparer<T> &containerPreparer);

public:
    /**
     * @brief begin test
     * */
    virtual uint64_t test() = 0;

protected:
    /**
     * @brief container to test
     * */
    T container;
    /**
     * @brief used ro prepare container's functions for testing
     * */
    ContainerPreparer<T> containerPreparer;
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
template<class T, class V>
class SequenceContainerTester : public ContainerTest<T> {
public:
    /**
     * @brief Constructor for class
     * @param container container to test
     * @param data test data
     * */
    SequenceContainerTester(T &&container, ContainerPreparer<T> &&containerPreparer, int64_t operations);
    /**
     * @brief Constructor for class
     * @param container container to test
     * @param data test data
     * */
    SequenceContainerTester(T &container, ContainerPreparer<T> &containerPreparer, int64_t operations);

public:
    /**
     * @brief begin test
     * */
    uint64_t test() override;

public:
private:
    /**
     * @brief vector of dataSet to be tested
     * */
    std::vector<V> dataSet;
    int64_t operations;
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

#if 0
template<class T>
ContainerTest<T>::ContainerTest(T &&testing_container, ContainerPreparer<T> &&containerPreparer) : container(testing_container), containerPreparer(containerPreparer) {}
#endif

template<class T>
ContainerTest<T>::ContainerTest(T &testing_container, ContainerPreparer<T> &containerPreparer) : container(testing_container), containerPreparer(containerPreparer) {}

template<class T, class V>
SequenceContainerTester<T, V>::SequenceContainerTester(T &&container, ContainerPreparer<T> &&containerPreparer, int64_t operations)
        : ContainerTest<T>(std::forward<T>(container), std::forward<T>(containerPreparer)), operations(operations) {
            this->dataSet.reserve(operations);
}

template<class T, class V>
SequenceContainerTester<T, V>::SequenceContainerTester(T &container, ContainerPreparer<T> &containerPreparer, int64_t operations)
        : ContainerTest<T>(container, containerPreparer), operations(operations) {
            this->dataSet.reserve(operations);
}

template<class T>
AssociativeTester<T>::AssociativeTester(T &&container)
        : ContainerTest<T>(std::forward<T>(container)) {
}

template<class T>
TreeTester<T>::TreeTester(T &&container)
        : ContainerTest<T>(std::forward<T>(container)) {
}

template<class T, class V>
uint64_t SequenceContainerTester<T, V>::test() {
    generator::integer::IntGenerator intGenerator = generator::integer::IntGenerator<T>(this->containerPreparer, this->operations, this->containerPreparer.getSize()-1, 1);
    auto funcPtrs = this->containerPreparer.getFuncPtrs();
    BasicDurationCounter durationCounter{};
    for (auto operation : intGenerator.intGenerator()) {
        funcPtrs.at(operation[0])(this->container, operation[1], operation[2]);
    }
    auto res = durationCounter.finishManually();
    std::cout << "time: " << res << "ms" << std::endl;
    return res;
}

#endif //DIPLOM_CONTAINERTEST_H
