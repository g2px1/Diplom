//
// Created by Kirill Zhukov on 02.10.2023.
//

#ifndef DIPLOM_POOL_H
#define DIPLOM_POOL_H

#include <cstdio>
#include <array>
#include <thread>
#include <future>
#include "ContainerTest.h"

using std::thread;

int64_t threadFunction() {
    return 0;
}

/**
 * @class Pool
 * @brief Pool contains vectors of <b>std::threads</b>, <b>std::promise</b>, <b>std::future</b> to handle threads and time measurements from test/-s
 * @tparam U type of data which is used in tests by threads
 * @tparam V container itself
 * @tparam T size of threads pool
 * */
template<class U, class V, std::size_t T>
class Pool {
public:
    /**
     * @brief Constructor for class
     * @param data vector of test data
     * @param container itself
     * */
    Pool(std::vector<U> &&data, V &&container);

public:
    /**
     * @brief used to start thread function
     * */
    void startThreads();
private:
    /**
     * @brief thread pool itself
     * */
    std::array<thread, T> pool;
    /**
     * @brief used to return value from thread
     * */
    std::array<std::promise<int64_t>, T> promise;
    /**
     * @brief used to return value from thread
     * */
    std::array<std::future<int64_t>, T> future;
    /**
     * @brief test for container
     * */
    std::unique_ptr<ContainerTest<V>> containerTest;
    /**
     * @brief mutex
     * */
    std::mutex mtx;
    /**
     * @brief used to notify waiting threads
     * */
    std::condition_variable cv;
    /**
     * @brief used to start threads
     * */
    bool start = false;
};

template<class U, class V, std::size_t T>
void Pool<U, V, T>::startThreads() {
    this->start = true;
    this->cv.notify_all();
}

template<class U, class V, std::size_t T>
Pool<U, V, T>::Pool(std::vector<U> &&data, V &&container) {
    this->containerTest = ContainerTest<V>(container);
    for (int64_t i = 0; i < T; i++) {
        this->future[i] = this->promise[i].get_future();
        this->pool[i] = std::thread([&, data] {
            std::unique_lock<std::mutex> lock(mtx);
            while (!this->start) {
                cv.wait(lock);
            }

            int result = 0;
            this->promise[i].set_value(result);
        });
    }
}

#endif //DIPLOM_POOL_H
