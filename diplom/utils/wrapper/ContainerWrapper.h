//
// Created by Kirill Zhukov on 19.11.2023.
//

#ifndef CONTAINERWRAPPER_H
#define CONTAINERWRAPPER_H


namespace test::framework::wrapper {
    enum operationType {
        FRONT = 0x0,
        INDEXED = 0x1,
        DELETE = 0x2
    };

    class ContainerWrapper {
    public:
        virtual void insert(void* value, operationType opType) = 0;

        virtual void del(void* value, operationType opType) = 0;

        virtual void read(void* value, operationType opType) = 0;

        virtual void write(void* value, operationType opType) = 0;
    };
}; // test::framework::wrapper


#endif //CONTAINERWRAPPER_H
