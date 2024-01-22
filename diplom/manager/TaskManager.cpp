//
// Created by Kirill Zhukov on 22.01.2024.
//

#include "TaskManager.h"

namespace test {
    namespace framework {
        TaskManager::TaskManager(int threads_num, wrapper::ContainerWrapper *containerWrapper,
                                 operation_distribution &operationDistribution) : threads_num(threads_num),
                                                                                  operationDistribution(
                                                                                          operationDistribution) {
            this->containerWrapper = containerWrapper;
            this->threads.reserve(threads_num);
        }

        TaskManager::~TaskManager() {
            delete this->containerWrapper;
        }

        void TaskManager::startTest() {
            generator::Generator op_generator = generator::Generator(this->operationDistribution.insert_percantage,
                                                                     this->operationDistribution.erase_percantage,
                                                                     this->operationDistribution.read_percantage,
                                                                     this->operationDistribution.write_percantage,
                                                                     this->operationDistribution.operations_quantity);
            op_generator.generate(true);
            this->threads.emplace_back([&, this]() {
                auto operations = op_generator.get_operations();
                for (auto& op : operations) {

                }
            });
        }
    }
}