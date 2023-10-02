//
// Created by Kirill Zhukov on 30.09.2023.
//

#ifndef DIPLOM_TESTOPERATIONS_H
#define DIPLOM_TESTOPERATIONS_H

enum SequenceOperations : unsigned char {
    INSERT_FRONT    = 0x0,
    INSERT_BACK     = 0x1, // push_back()
    INSERT_INDEXED  = 0x2, //  myVector.insert(myVector.begin() + indexToInsertAt, valueToInsert);
    ACCESS_ELEMENT  = 0x3, // read indexed
    EMPLACE         = 0x4,
    DELETE_FRONT    = 0x5, // pop_front()
    DELETE_INDEXED  = 0x6, // myVector.erase(myVector.begin() + indexToRemove);
    DELETE_BACK     = 0x7, // pop_back()
};

#endif //DIPLOM_TESTOPERATIONS_H
