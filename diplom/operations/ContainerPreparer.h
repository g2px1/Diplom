//
// Created by Kirill Zhukov on 02.10.2023.
//

#ifndef DIPLOM_CONTAINERPREPARER_H
#define DIPLOM_CONTAINERPREPARER_H

#include <vector>
#include <functional>
#include <cstdio>
#include "ContainerFunctions.h"

/**
 * @class ContainerPreparer
 * @brief Used to generate vector of container's functions. This class was created, to reduce delays while accessing functions from container under test
 * */
template<class T>
class ContainerPreparer {
public:
    /**
     * @brief Constructor for class
     * @param availableFunctions is used to check if the container under test has methods
     * */
    [[maybe_unused]] explicit ContainerPreparer(sequence::AvailableFunctions availableFunctions);

public:
    /**
     * @brief returns prepared vector of container's operations
     * */
    [[nodiscard]] const std::vector<std::function<void(T &, int, int)>> &getFuncPtrs() const;
    /**
     * @brief is used to initialize vector of functions
     * */
    virtual void init();

private:
    /**
     * @brief vector of container's functions
     * */
    std::vector<std::function<void(T &, int, int)>> func_ptrs;
    /**
     * @brief is used to check if the container under test has methods
     * */
    sequence::AvailableFunctions availableFunctions;
};

template<class T>
void ContainerPreparer<T>::init() {
    // Now, we're checking available operations. We need to do this, to minimize delays
    if (sequence::hasInsertFront(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { v.insert(v.begin(), value); });
    }
    if (sequence::hasInsertBack(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { v.insert(v.begin() + (v.size() - 1), value); });
    }
    if (sequence::hasInsertIndexed(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { v.insert(v.begin() + position, value); });
    }
    if (sequence::hasAccessElement(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { return v.at(position); });
    }
    if (sequence::hasEmplace(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { return v.emplace_back(value); });
    }
    if (sequence::hasDeleteFront(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { return v.erase(v.begin()); });
    }
    if (sequence::hasDeleteFront(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { return v.erase(v.begin() + (v.size() - 1)); });
    }
    if (sequence::hasDeleteIndexed(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](std::vector<int> &v, int value, int position = 0) { return v.erase(v.begin() + position); });
    }
}

template<class T>
[[maybe_unused]] ContainerPreparer<T>::ContainerPreparer(sequence::AvailableFunctions availableFunctions) {
    if (availableFunctions == 0) {
        std::perror("There is no available functions in provided container");
        std::exit(5);
    }
    this->availableFunctions = availableFunctions;
    this->init();
}

template<class T>
const std::vector<std::function<void(T &, int, int)>> &ContainerPreparer<T>::getFuncPtrs() const {
    return func_ptrs;
}

#endif //DIPLOM_CONTAINERPREPARER_H
