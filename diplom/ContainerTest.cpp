//
// Created by Kirill Zhukov on 06.09.2023.
//

#include "ContainerTest.h"

template<class T>
ContainerTest<T>::ContainerTest(CONTAINER_TYPE type, T &&testing_container) : containerType(type), container(testing_container) {}