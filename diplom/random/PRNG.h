//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_PRNG_H
#define DIPLOM_PRNG_H

#include <random>

/**
 * @class PRNG
 * @brief Pseudo-random number generator. Provides interface to generate numbers: 32, 64 bit.
 * */
class PRNG {
public:
    explicit PRNG();

    [[maybe_unused]] explicit PRNG(int64_t userSeed);

public:
    /**
     * @brief getSeed - getter for seed
     * */
    [[nodiscard]] int64_t getSeed() const;

    /**
     * @brief generateNumber32 returns random 32-bit number
     * @param min - lower limit of the generator
     * @param max - upper limit of the generator
     * */
    int32_t generateNumber32(int min = INT32_MIN, int max = INT32_MAX);

    /**
     * @brief generateNumber64 returns random 64-bit number
     * @param min - lower limit of the generator
     * @param max - upper limit of the generator
     * */
    int64_t generateNumber64(int64_t min = INT64_MIN, int64_t max = INT64_MAX);

protected:
    /**
     * @brief pointer to <b>int64_t</b> which is used for generating random numbers
     * */
    std::unique_ptr<int64_t> seed;
    /**
     * @brief Mersenne twister 32-bit number generator
     * */
    std::mt19937 gen32;
    /**
     * @brief Mersenne twister 64-bit number generator
     * */
    std::mt19937_64 gen64;
};

#endif //DIPLOM_PRNG_H
