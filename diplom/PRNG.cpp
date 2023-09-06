//
// Created by Kirill Zhukov on 06.09.2023.
//

#include "PRNG.h"

[[maybe_unused]] PRNG::PRNG(int64_t userSeed) {
    this->seed = std::make_unique<int64_t>(userSeed);
    this->gen32.seed(userSeed);
    this->gen64.seed(userSeed);
}

int64_t PRNG::getSeed() const {
    if (!this->seed) {
        return INT64_MIN;
    }
    return (*this->seed);
}

PRNG::PRNG() {
    std::random_device dev;
    this->gen32.seed(dev());
    this->gen64.seed(dev());
}

int32_t PRNG::generateNumber32(int min = INT32_MIN, int max = INT32_MAX) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(this->gen32);
}

int64_t PRNG::generateNumber64(int64_t min = INT64_MIN, int64_t max = INT64_MAX) {
    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(this->gen64);
}