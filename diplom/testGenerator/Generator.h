//
// Created by Kirill Zhukov on 05.10.2023.
//

#ifndef DIPLOM_GENERATOR_H
#define DIPLOM_GENERATOR_H

#include <cstdio>
#include <cstdint>
#include "PRNG.h"
#include "ContainerPreparer.h"

namespace generator {
    namespace integer {
        template<class T>
        class IntGenerator {
        public:
            IntGenerator(ContainerPreparer<T> &containerPreparer, int64_t operationsQuantity,
                         int64_t availableOperations,
                         int64_t seed = INT64_MIN);

        public:
            /**
             * @return vector of data.
             * first argument is operation.
             * second argument is first parameter of operation (optional).
             * third argument is second parameter of operation (optional).
             * */
            std::vector<std::array<int64_t, 3>> intGenerator();

        private:
            PRNG prng;
            int64_t operationsQuantity;
            int64_t availableOperations;
            ContainerPreparer<T> &containerPreparer;
        };

        template<class T>
        IntGenerator<T>::IntGenerator(ContainerPreparer<T> &containerPreparer, int64_t operationsQuantity,
                                      int64_t availableOperations, int64_t seed)
                : containerPreparer(containerPreparer), operationsQuantity(operationsQuantity), availableOperations(availableOperations) {
            if (seed != INT64_MIN)
                this->prng = PRNG(seed);
        }

        template<class T>
        std::vector<std::array<int64_t, 3>> IntGenerator<T>::intGenerator() {
            std::vector<std::array<int64_t, 3>> dataSet;
            dataSet.reserve(operationsQuantity);
            for (int64_t i = 0; i < operationsQuantity; i++) {
                dataSet[i][0] = this->prng.generateNumber64(0, this->availableOperations);
                dataSet[i][1] = this->prng.generateNumber64();
                dataSet[i][2] = this->prng.generateNumber64(0, this->availableOperations);
            }
            return dataSet;
        }
    }
    namespace custom {
        template<class T>
        class CustomData {
        };
    }
}
#endif //DIPLOM_GENERATOR_H
