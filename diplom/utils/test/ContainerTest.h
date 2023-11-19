#ifndef CONTAINERTEST_H
#define CONTAINERTEST_H
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cstdint>

namespace test::framework::container {
    typedef enum containerType {
        SEQUENCE,
        ASSOCIATIVE
    } containerType;

    template<class Container>
    class ContainerTest {
    public:
        ContainerTest(const std::vector<std::pair<int16_t, int>>&operations, const containerType type)
            : operations(operations) {
            if (type != SEQUENCE && type != ASSOCIATIVE) {
                throw std::invalid_argument("Invalid container type");
            }
        }

    public:
        /// @brief Starts the container test
        /// @return key - int16_t is a command index, value - is array of length 2, first value is frequency of operation, second is total time spend on that operation
        virtual std::unordered_map<int16_t, std::array<int64_t, 2>> test();

    private:

    private:
        Container container;
        std::vector<std::pair<int16_t, int>> operations;
        containerType container_type;
    };

    template<class Container>
    std::unordered_map<int16_t, std::array<int64_t, 2>> ContainerTest<Container>::test() {
        std::unordered_map<int16_t, std::array<int64_t, 2>> measured_results;

        if (this->container_type == containerType::SEQUENCE) goto sequence;
        else goto associative;

    sequence: {
            for (uint64_t i = 0; i < this->operations.size(); i++) {
                auto operation_pair = this->operations.at(i);
                switch (operation_pair.first) {
                    case 0x0:
                        this->container.push(operation_pair.second);
                        break;
                    case 0x1:
                        // this->container.pop();
                        break;
                    case 0x2:
                        // this->container.at(operation_pair.second);
                        break;
                    case 0x3:
                        // this->container.insert(operation_pair.second);
                        break;
                }
            }
        }

    associative: {
            for (uint64_t i = 0; i < this->operations.size(); i++) {
            }
        }

        return measured_results;
    }
}; // test::framework::container


#endif //CONTAINERTEST_H
