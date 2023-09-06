//
// Created by Kirill Zhukov on 06.09.2023.
//

#ifndef DIPLOM_PRNG_H
#define DIPLOM_PRNG_H

#include <random>

class PRNG {
public:
    explicit PRNG();
    [[maybe_unused]] explicit PRNG(int64_t userSeed);
public:
    [[nodiscard]] int64_t getSeed() const;
protected:
    std::unique_ptr<int64_t> seed;
    std::mt19937 gen32;
    std::mt19937_64 gen64;
};

#endif //DIPLOM_PRNG_H
