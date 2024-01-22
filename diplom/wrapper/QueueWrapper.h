//
// Created by Kirill Zhukov on 19.11.2023.
//

#ifndef QUEUEWRAPPER_H
#define QUEUEWRAPPER_H

#include "ContainerWrapper.h"

template<class Queue>
class QueueWrapper final : public test::framework::wrapper::ContainerWrapper {
public:
    ~QueueWrapper() override = default;

    void insert(void* value, test::framework::wrapper::operationType opType) override;

    void del(void* value, test::framework::wrapper::operationType opType) override;

    void read(void* value, test::framework::wrapper::operationType opType) override;

    void write(void* value, test::framework::wrapper::operationType opType) override;

private:
    Queue q;
};



#endif //QUEUEWRAPPER_H
