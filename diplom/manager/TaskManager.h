//
// Created by Kirill Zhukov on 22.01.2024.
//

#ifndef DIPLOM_TASKMANAGER_H
#define DIPLOM_TASKMANAGER_H

#include <thread>
#include <unistd.h>
#include "wrapper/ContainerWrapper.h"
#include "generator/Generator.h"

namespace test {
    namespace framework {

        struct operation_distribution {
            uint8_t push_percantage;
            uint8_t erase_percantage;
            uint8_t insert_percantage;
            uint8_t read_percantage;
            uint8_t write_percantage;
            uint64_t operations_quantity;
        };

        struct time_info {
            uint64_t push_time;
            uint64_t erase_time;
            uint64_t insert_time;
            uint64_t read_time;
            uint64_t write_percantage;
        };

        class TaskManager {
        public:
            TaskManager(int threads_num, wrapper::ContainerWrapper* containerWrapper, operation_distribution& operationDistribution);
            ~TaskManager();
        public:
            void startTest();
        private:
            int threads_num;
            operation_distribution operationDistribution;
            wrapper::ContainerWrapper *containerWrapper;
            std::vector<std::thread> threads;
            std::vector<time_info> average_time_info;
        };
    }
}

#endif //DIPLOM_TASKMANAGER_H
