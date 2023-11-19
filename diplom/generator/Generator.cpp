//
// Created by Kirill Zhukov on 19.11.2023.
//

#include "Generator.h"

test::framework::Generator::Generator(uint8_t push_percantage,
                                      uint8_t pop_percantage,
                                      uint8_t read_percantage,
                                      uint8_t write_percantage,
                                      uint64_t operations_quantity)
    : push(push_percantage), pop(pop_percantage), read(read_percantage),
      write(write_percantage), operations_q(operations_quantity) {
  int8_t total_distribution =
      push_percantage + pop_percantage + read_percantage + write_percantage;
  if (total_distribution != 100) {
    std::cerr << "Wrong distribution: " << (int)total_distribution
              << "%, should be 100%";
    exit(2);
  }
  std::random_device rd;
  this->gen_engine = std::mt19937_64(rd());
}

void test::framework::Generator::generator(bool writeLogFile,
                                           const std::string &file_name) {
  double push_operation_q =
      static_cast<double>(this->operations_q * this->push) / 100;
  double pop_operation_q =
      static_cast<double>(this->operations_q * this->pop) / 100;
  double read_operation_q =
      static_cast<double>(this->operations_q * this->read) / 100;
  double write_operation_q = static_cast<double>(operations_q) -
                             push_operation_q - pop_operation_q -
                             read_operation_q;

  std::vector<int16_t> operations;
  operations.reserve(this->operations_q);

  std::discrete_distribution<> d(
      {push_operation_q, pop_operation_q, read_operation_q, write_operation_q});
  for (size_t i = 0; i < this->operations_q; ++i) {
    int operationIndex = d(this->gen_engine); // Генерация индекса операции
    operations.push_back(OP_OPERATIONS[operationIndex]);
  }

  // Перенос сгенерированных операций в this->operations
  this->operations = std::move(operations);
  if (writeLogFile) [[unlikely]] {
    this->write_log(file_name);
  }
}

void test::framework::Generator::write_log(const std::string &file_name) {
  FILE *fd = fopen(file_name.c_str(), "wb");
  if (!fd) {
    std::cerr << "Log file can't be opened, reason (errno): " << errno;
    exit(9);
  }

  for (size_t i = 0; i < this->operations.size(); i++) {
    fprintf(fd, "[%zu]: %s\n", i, this->op2s(this->operations[i]));
  }
  fclose(fd);
}

char *test::framework::Generator::op2s(int16_t op) {
  switch (op) {
  case 0x0:
    return (char *)"PUSH";
  case 0x1:
    return (char *)"POP";
  case 0x2:
    return (char *)"READ";
  case 0x3:
    return (char *)"WRITE";
  default:
    std::cerr << "Unknown operation" << op;
    exit(9);
  }
}
