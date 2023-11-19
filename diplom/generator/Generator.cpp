//
// Created by Kirill Zhukov on 19.11.2023.
//

#include "Generator.h"

test::framework::Generator::Generator(uint8_t insert_percantage, uint8_t delete_percantage, uint8_t read_percantage,
                                      uint8_t write_percantage, uint64_t operations_quantity) : push(insert_percantage),
    pop(delete_percantage), read(read_percantage), write(write_percantage), operations_q(operations_quantity) {
    int8_t total_distribution = insert_percantage + delete_percantage + read_percantage + write_percantage;
    if (total_distribution != 100) {
        std::cerr << "Wrong distribution: " << static_cast<int>(total_distribution) << "%, should be 100%";
    }
    std::random_device rd;
    this->gen_engine = std::mt19937_64(rd());
}

void test::framework::Generator::generate(bool writeLogFile, const std::string&file_name) {
    double push_operation_q = static_cast<double>(this->operations_q * this->push) / 100;
    double pop_operation_q = static_cast<double>(this->operations_q * this->pop) / 100;
    double read_operation_q = static_cast<double>(this->operations_q * this->read) / 100;
    double write_operation_q = static_cast<double>(operations_q) - push_operation_q - pop_operation_q -
                               read_operation_q;

    std::vector<std::pair<int16_t, int>> operations;
    operations.reserve(this->operations_q);

    std::uniform_int_distribution<> value_dist(1, 100); // Диапазон значений для PUSH и WRITE
    std::uniform_int_distribution<> index_dist(1, static_cast<int>(this->operations_q)); // Диапазон индексов для READ

    std::discrete_distribution<> op_dist({push_operation_q, pop_operation_q, read_operation_q, write_operation_q});
    for (size_t i = 0; i < this->operations_q; ++i) {
        int operationIndex = op_dist(this->gen_engine);
        int argument = 0;

        switch (operationIndex) {
            case 0: // PUSH
                argument = value_dist(this->gen_engine);
            break;
            case 2: // READ
                argument = index_dist(this->gen_engine);
            break;
            case 3: // WRITE
                argument = value_dist(this->gen_engine);
                break;
        }
        operations.emplace_back(OP_OPERATIONS[operationIndex], argument);
    }

    // Перенос сгенерированных операций в this->operations
    this->operations = std::move(operations);
    if (writeLogFile) [[unlikely]]
    {
        this->write_log(file_name);
    }
}

void test::framework::Generator::write_log(const std::string&file_name) const {
    FILE* fd = fopen(file_name.c_str(), "wb");
    if (!fd) {
        std::cerr << "Log file can't be opened, reason (errno): " << errno;
        exit(9);
    }

    for (size_t i = 0; i < this->operations.size(); i++) {
        fprintf(fd, "[%zu]: %s, arg: %d\n", i, op2s(this->operations[i].first), this->operations[i].second);
    }
    fclose(fd);
}

char* test::framework::Generator::op2s(int16_t op) {
    switch (op) {
        case 0x0:
            return (char *)"INSERT";
        case 0x1:
            return (char *)"DELETE";
        case 0x2:
            return (char *)"READ";
        case 0x3:
            return (char *)"WRITE";
        default:
            std::cerr << "Unknown operation – exit(9)";
            exit(9);
    }
}

const std::vector<std::pair<int16_t, int>>& test::framework::Generator::get_operations() const {
    return this->operations;
}
