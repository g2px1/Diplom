//
// Created by Kirill Zhukov on 06.09.2023.
//

#include "ContainerTest.h"

template<class T>
ContainerTest<T>::ContainerTest(T &&testing_container) : container(testing_container) {}

template<class T>
SequenceContainerTester<T>::SequenceContainerTester(T &&container)
        : ContainerTest<T>(std::forward<T>(container)) {
}

template<class T>
AssociativeTester<T>::AssociativeTester(T &&container)
        : ContainerTest<T>(std::forward<T>(container)) {
}

template<class T>
TreeTester<T>::TreeTester(T &&container)
        : ContainerTest<T>(std::forward<T>(container)) {
}

template<class T>
uint64_t SequenceContainerTester<T>::test() {
    return 0;
}