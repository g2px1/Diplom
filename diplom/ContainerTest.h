//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_CONTAINERTEST_H
#define DIPLOM_CONTAINERTEST_H

#include <cstdio>
#include <utility>

template<class T>
class ContainerTest {
public:
    template<class U>
    friend
    class SequenceContainer;

public:
    explicit ContainerTest(T &&testing_container);

public:
    virtual uint64_t test() = 0;

private:
    T container;
protected:
};

template<class T>
class SequenceContainerTester : public ContainerTest<T> {
public:
    explicit SequenceContainerTester(T &&container);
public:
    uint64_t test() override;
};

template<class T>
class MapTester : public ContainerTest<T> {
public:
    explicit MapTester(T &&container);
public:
    uint64_t test() override;
};

template<class T>
class TreeTester : public ContainerTest<T> {
public:
    explicit TreeTester(T &&container);
public:
    uint64_t test() override;
};

#endif //DIPLOM_CONTAINERTEST_H
