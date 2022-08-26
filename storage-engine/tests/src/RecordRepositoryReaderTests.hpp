/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDREPOSITORYREADERTESTS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDREPOSITORYREADERTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class RecordRepositoryReaderTests : public Ishiko::TestSequence
{
public:
    RecordRepositoryReaderTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ReadTest1(Ishiko::Test& test);
    static void ReadTest2(Ishiko::Test& test);
    static void ReadTest3(Ishiko::Test& test);
    static void ReadTest4(Ishiko::Test& test);
    static void ReadTest5(Ishiko::Test& test);
    static void ReadLEB128Test1(Ishiko::Test& test);
    static void ReadLEB128Test2(Ishiko::Test& test);
    static void ReadLEB128Test3(Ishiko::Test& test);
    static void ReadLEB128Test4(Ishiko::Test& test);
    static void ReadLEB128Test5(Ishiko::Test& test);
};

#endif
