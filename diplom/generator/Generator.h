//
// Created by Kirill Zhukov on 19.11.2023.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include <random>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cinttypes>

namespace test::framework {
    /// @brief set of operations' indexes: 0x0 - PUSH, 0x1 - POP, 0x2 - READ, 0x3 - WRITE
    constexpr int16_t OP_OPERATIONS[4] = {0x0, 0x1, 0x2, 0x3};

    class Generator {
    public:
        Generator(uint8_t push_percantage, uint8_t pop_percantage, uint8_t read_percantage, uint8_t write_percantage,
                  uint64_t operations_quantity);

        /// @brief generates set of operations
        /// @param writeLogFile flag is <b>true</b> if you want to write logs to a file, otherwise <b>false</b>
        void generate(bool writeLogFile, const std::string&file_name = "default_log_file.txt");

        void write_log(const std::string&file_name) const;

        static char* op2s(int16_t op);

    public:
        const std::vector<std::pair<int16_t, int>>& get_operations() const;

    private:
        std::mt19937_64 gen_engine;

        /// @brief abstract name for operations such as `enqueue` etc.
        uint8_t push;
        /// @brief abstract name for operations such as `dequeue` etc.
        uint8_t pop;
        /// @brief abstract name for operations such as `at`, operator `[]` etc.
        uint8_t read;
        /// @brief abstract name for operations such as `insert` etc.
        uint8_t write;
        /// @brief operation quantity to be generated
        uint64_t operations_q;
        /// @brief operations sequence
        std::vector<std::pair<int16_t, int>> operations;
    };
}; // test::framework


#endif //GENERATOR_H