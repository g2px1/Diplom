//
// Created by Kirill Zhukov on 30.09.2023.
//

#ifndef DIPLOM_TESTOPERATIONS_H
#define DIPLOM_TESTOPERATIONS_H

enum SequenceOperations : unsigned char {
    INSERT_FRONT,
    INSERT_BACK, // push_back()
    INSERT_INDEXED, //  myVector.insert(myVector.begin() + indexToInsertAt, valueToInsert);
    ACCESS_ELEMENT, // read indexed
    EMPLACE,
    DELETE_FRONT, // pop_front()
    DELETE_INDEXED, // myVector.erase(myVector.begin() + indexToRemove);
    DELETE_BACK, // pop_back()
};

#endif //DIPLOM_TESTOPERATIONS_H
