//
// Created by Kirill Zhukov on 02.10.2023.
//

#ifndef DIPLOM_POOL_H
#define DIPLOM_POOL_H

#include <cstdio>
#include <array>
#include <thread>
#include <future>
#include <iostream>
#include "ContainerTest.h"

using std::thread;

int64_t threadFunction() {
    return 0;
}

/**
 * @class Pool
 * @brief Pool contains vectors of <b>std::threads</b>, <b>std::promise</b>, <b>std::future</b> to handle threads and time measurements from test/-s
 * @tparam U type of data which is used in tests by threads
 * @tparam V container test
 * @tparam T size of threads pool
 * */
template<class V, std::size_t T>
class Pool {
public:
    /**
     * @brief Constructor for class
     * @param data vector of test data
     * @param containerTest container's test
     * */
    explicit Pool(V &containerTest);

public:
    /**
     * @brief used to start thread function
     * */
    void startThreads();
    /**
     * @brief joins threads
     * */
    void joinThreads();
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
    V containerTest;
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

template<class V, std::size_t T>
void Pool<V, T>::joinThreads() {
    for (int64_t i = 0; i < T - 1; i++) {
        this->pool[i].join();
    }
}

template<class V, std::size_t T>
void Pool<V, T>::startThreads() {
    this->start = true;
    this->cv.notify_all();
}

template<class V, std::size_t T>
Pool<V, T>::Pool(V &containerTest) : containerTest(containerTest), mtx() {
    for (int64_t i = 0; i < T - 1; i++) {
        this->future[i] = this->promise[i].get_future();
        this->pool[i] = std::thread([&] {
#if 0
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return this->start; });
#endif
            for (int i = 0; i < 5; i++)
//                std::cout << "thread: " << std::this_thread::get_id() << '\n';
            this->containerTest.test();
        });
    }
}

#endif //DIPLOM_POOL_H
