//
// Created by Kirill Zhukov on 02.10.2023.
//

#ifndef DIPLOM_CONTAINERFUNCTIONS_H
#define DIPLOM_CONTAINERFUNCTIONS_H

#include <cstdint>
#include <type_traits>

#ifdef _MSC_VER
#   define always_inline __forceinline
#elif defined(__GNUC__)
#   define always_inline __attribute__((always_inline)) inline
#else
#   define always_inline inline
#endif

namespace sequence {
    /**
     * @brief Used to check if value is a part of enum
     * */
    template <typename T>
    concept AvailableFunctionsType = std::is_enum_v<T>;

    /**
     * @enum AvailableFunctions
     * */
    enum AvailableFunctions : uint32_t {
        INSERT_FRONT = 0x0000'0001, /// INSERT_FRONT corresponds to insertion operations at the beginning
        INSERT_BACK = 0x0000'0010, /// INSERT_BACK corresponds to insertion operations at the end
        INSERT_INDEXED = 0x0000'0100, /// INSERT_INDEXED corresponds to insertion operations by index
        ACCESS_ELEMENT = 0x0000'1000, /// ACCESS_ELEMENT corresponds to access operations to the element
        EMPLACE = 0x0001'0000, /// EMPLACE corresponds to the operations of on-site construction of the element
        DELETE_FRONT = 0x0010'0000, /// DELETE_FRONT corresponds to deletion operations from the beginning
        DELETE_BACK = 0x0100'0000, /// DELETE_BACK corresponds to end deletion operations
        DELETE_INDEXED = 0x1000'0000, /// DELETE_INDEXED corresponds to deletion operations by index
    };

    /**
     * @brief add <b>INSERT_FRONT</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addInsertFrontOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::INSERT_FRONT);
    }

    /**
     * @brief add <b>INSERT_BACK</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addInsertBackOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::INSERT_BACK);
    }
    /**
     * @brief add <b>INSERT_INDEXED</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addInsertIndexedOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::INSERT_INDEXED);
    }
    /**
     * @brief add <b>ACCESS_ELEMENT</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addAccessElementOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::ACCESS_ELEMENT);
    }
    /**
     * @brief add <b>EMPLACE</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addEmplaceOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::EMPLACE);
    }
    /**
     * @brief add <b>DELETE_FRONT</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addDeleteFrontOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::DELETE_FRONT);
    }
    /**
     * @brief add <b>DELETE_INDEXED</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addDeleteIndexedOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::DELETE_INDEXED);
    }
    /**
     * @brief add <b>DELETE_BACK</b> operation to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addDeleteBackOperation(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions | AvailableFunctions::DELETE_BACK);
    }
    /**
     * @brief add <b>INSERT_FRONT</b>, <b>INSERT_BACK</b>, <b>INSERT_INDEXED</b>, <b>ACCESS_ELEMENT</b>,
     * <b>EMPLACE</b>, <b>DELETE_FRONT</b>, <b>DELETE_INDEXED</b>, <b>DELETE_BACK</b> operations to original value
     * @param availableFunctions original value
     * */
    always_inline AvailableFunctions addAllOperations(AvailableFunctions availableFunctions) {
        return static_cast<AvailableFunctions>(availableFunctions |
                                               AvailableFunctions::INSERT_FRONT |
                                               AvailableFunctions::INSERT_BACK |
                                               AvailableFunctions::INSERT_INDEXED |
                                               AvailableFunctions::ACCESS_ELEMENT |
                                               AvailableFunctions::EMPLACE |
                                               AvailableFunctions::DELETE_FRONT |
                                               AvailableFunctions::DELETE_INDEXED |
                                               AvailableFunctions::DELETE_BACK);
    }
    /**
     * @brief set provided operation to original value
     * @param availableFunctions original value
     * @param valueToSet value which will be set
     * */
    always_inline AvailableFunctions
    setOperation(AvailableFunctions availableFunctions, AvailableFunctions valueToSet) {
        return static_cast<AvailableFunctions>(availableFunctions | valueToSet);
    }
    /**
     * @brief check <b>INSERT_FRONT</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasInsertFront(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::INSERT_FRONT);
    }
    /**
     * @brief check <b>INSERT_BACK</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasInsertBack(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::INSERT_BACK);
    }
    /**
     * @brief check <b>INSERT_INDEXED</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasInsertIndexed(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::INSERT_INDEXED);
    }
    /**
     * @brief check <b>ACCESS_ELEMENT</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasAccessElement(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::ACCESS_ELEMENT);
    }
    /**
     * @brief check <b>EMPLACE</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasEmplace(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::EMPLACE);
    }
    /**
     * @brief check <b>DELETE_FRONT</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasDeleteFront(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::DELETE_FRONT);
    }
    /**
     * @brief check <b>DELETE_INDEXED</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasDeleteIndexed(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::DELETE_INDEXED);
    }
    /**
     * @brief check <b>DELETE_BACK</b> operation for availability
     * @param availableFunctions original value
     * */
    always_inline bool hasDeleteBack(AvailableFunctions availableFunctions) {
        return static_cast<bool>(availableFunctions & AvailableFunctions::DELETE_BACK);
    }
    /**
     * @brief check provided operation for availability
     * @param availableFunctions original value
     * @param valueToCheck value is checking for
     * @tparam T used to check if provided value is a part of <b>AvailableFunctions</b> enum
     * */
    template<AvailableFunctionsType T>
    always_inline bool hasOperation(AvailableFunctions availableFunctions, T valueToCheck) {
        return static_cast<bool>(availableFunctions & valueToCheck);
    }
}
#endif //DIPLOM_CONTAINERFUNCTIONS_H
