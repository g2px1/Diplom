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
 * @tparam T container
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
     * @brief returns prepared vector of container's dataSet
     * */
    [[nodiscard]] const std::vector<std::function<void(T &, int, int)>> &getFuncPtrs() const;
    /**
     * @brief is used to initialize vector of functions
     * */
    virtual void init();

    virtual std::size_t getSize();
private:
    /**
     * @brief vector of container's functions
     * */
    std::vector<std::function<void(T &, int, int)>> func_ptrs;
    /**
     * @brief vector of operations types
     * */
    std::vector<sequence::AvailableFunctions> functionTypes;
    /**
     * @brief is used to check if the container under test has methods
     * */
    sequence::AvailableFunctions availableFunctions;
};

template<class T>
std::size_t ContainerPreparer<T>::getSize() {
    return this->func_ptrs.size();
}

template<class T>
void ContainerPreparer<T>::init() {
    // Now, we're checking available dataSet. We need to do this, to minimize delays
    if (sequence::hasInsertFront(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { v.insert(v.begin(), value); });
        this->functionTypes.push_back(sequence::AvailableFunctions::INSERT_FRONT);
    }
    if (sequence::hasInsertBack(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { v.insert(v.begin() + (v.size() - 1), value); });
        this->functionTypes.push_back(sequence::AvailableFunctions::INSERT_BACK);
    }
    if (sequence::hasInsertIndexed(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { v.insert(v.begin() + position, value); });
        this->functionTypes.push_back(sequence::AvailableFunctions::INSERT_INDEXED);
    }
    if (sequence::hasAccessElement(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { return v.at(position); });
        this->functionTypes.push_back(sequence::AvailableFunctions::ACCESS_ELEMENT);
    }
    if (sequence::hasEmplace(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { return v.emplace_back(value); });
        this->functionTypes.push_back(sequence::AvailableFunctions::EMPLACE);
    }
    if (sequence::hasDeleteFront(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { return v.erase(v.begin()); });
        this->functionTypes.push_back(sequence::AvailableFunctions::DELETE_FRONT);
    }
    if (sequence::hasDeleteBack(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { return v.erase(v.begin() + (v.size() - 1)); });
        this->functionTypes.push_back(sequence::AvailableFunctions::DELETE_BACK);
    }
    if (sequence::hasDeleteIndexed(availableFunctions)) {
        this->func_ptrs.emplace_back(
                [](T &v, int value, int position = 0) { return v.erase(v.begin() + position); });
        this->functionTypes.push_back(sequence::AvailableFunctions::DELETE_INDEXED);
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
