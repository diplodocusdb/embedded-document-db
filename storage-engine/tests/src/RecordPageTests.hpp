/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDPAGETESTS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDPAGETESTS_HPP

#include <Ishiko/TestFramework.hpp>

class RecordPageTests : public Ishiko::TestSequence
{
public:
    RecordPageTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ReadTest1(Ishiko::Test& test);
    static void ReadTest2(Ishiko::Test& test);
    static void ReadTest3(Ishiko::Test& test);
    static void ReadTest4(Ishiko::Test& test);
    static void ReadTest5(Ishiko::Test& test);
    static void WriteTest1(Ishiko::Test& test);
    static void GetTest1(Ishiko::Test& test);
    static void InsertTest1(Ishiko::Test& test);
    static void InsertTest2(Ishiko::Test& test);
    static void InsertTest3(Ishiko::Test& test);
    static void EraseTest1(Ishiko::Test& test);
    static void EraseTest2(Ishiko::Test& test);
    static void EraseTest3(Ishiko::Test& test);
    static void MoveToTest1(Ishiko::Test& test);
    static void MoveToTest2(Ishiko::Test& test);
};

#endif
