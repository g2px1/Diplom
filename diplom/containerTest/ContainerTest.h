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
    /**
     * @brief container to test
     * */
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
template<class T, class V>
class SequenceContainerTester : public ContainerTest<T> {
public:
    /**
     * @brief Constructor for class
     * @param container container to test
     * @param data test data
     * */
    SequenceContainerTester(T &&container, std::vector<V> &&data);
    /**
     * @brief Constructor for class
     * @param container container to test
     * @param data test data
     * */
    SequenceContainerTester(T &container, std::vector<V> &data);

public:
    /**
     * @brief begin test
     * */
    uint64_t test() override;

public:
private:
    /**
     * @brief vector of operations to be tested
     * */
    std::vector<V> operations;
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

template<class T>
ContainerTest<T>::ContainerTest(T &&testing_container) : container(testing_container) {}

template<class T, class V>
SequenceContainerTester<T, V>::SequenceContainerTester(T &&container, std::vector<V> &&data)
        : ContainerTest<T>(std::forward<T>(container)), operations(std::move(data)) {
}

template<class T, class V>
SequenceContainerTester<T, V>::SequenceContainerTester(T &container, std::vector<V> &data)
        : ContainerTest<T>(std::forward<T>(container)), operations(std::move(data)) {
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
    return 0;
}

#endif //DIPLOM_CONTAINERTEST_H
