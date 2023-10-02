//
// Created by Kirill Zhukov on 22.09.2023.
//

#ifndef DIPLOM_DURATIONCOUNTER_H
#define DIPLOM_DURATIONCOUNTER_H

#include <utility>
#include "iostream"

/**
 * @class BasicDurationCounter
 * @brief Start time counting after initialization
 * @details Should be stopped manually by using necessary function
 * */
class BasicDurationCounter {
public:
    friend class LogDuration;
public:
    explicit BasicDurationCounter() = default;
    virtual ~BasicDurationCounter() = default;
public:
    /**
     * @details counting the total elapsed time through the difference between the start and the time of the given function call
     * @return total elapsed time in ms
     * */
    uint64_t finishManually();
private:
    /**
     * @brief time when test starts
     * */
    const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
};

/**
 * @class LogDuration
 * @brief Prints total elapsed time while destructor called in ms
 * @details Doesn't need any functions to measure time
 * */
class LogDuration : public BasicDurationCounter {
public:
    /**
     * @brief Constructor for class
     * */
    explicit LogDuration(std::string name) : id(std::move(name)) {}
    /**
     * @brief Destructor for class
     * */
    ~LogDuration() override {
        const auto end_time = std::chrono::steady_clock::now();
        const auto dur = end_time - this->start_time;
        std::cout << this->id << ": "
                  << "operation time"
                  << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }
private:
    /**
     * @brief name of test
     * */
    const std::string id;
};

#endif //DIPLOM_DURATIONCOUNTER_H
