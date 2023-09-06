//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_CONTAINERTEST_H
#define DIPLOM_CONTAINERTEST_H

typedef unsigned char u1;

enum CONTAINER_TYPE : u1 {
    SEQUENCE_CONTAINER,
    MAP,
    TREE
};

template <class T>
class ContainerTest {
public:
    ContainerTest(CONTAINER_TYPE type, T &&testing_container);
public:
    void test();
private:

protected:
    CONTAINER_TYPE containerType;
    T container;
};

#endif //DIPLOM_CONTAINERTEST_H
