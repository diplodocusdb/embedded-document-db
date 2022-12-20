/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDREPOSITORYWRITERTESTS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDREPOSITORYWRITERTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class RecordRepositoryWriterTests : public Ishiko::TestSequence
{
public:
    RecordRepositoryWriterTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void WriteTest1(Ishiko::Test& test);
    static void WriteTest2(Ishiko::Test& test);
    static void WriteTest3(Ishiko::Test& test);
    static void WriteTest4(Ishiko::Test& test);
    static void WriteTest5(Ishiko::Test& test);
    static void WriteTest6(Ishiko::Test& test);
    static void WriteTest7(Ishiko::Test& test);
    static void WriteTest8(Ishiko::Test& test);
    static void WriteLEB128Test1(Ishiko::Test& test);
    static void WriteLEB128Test2(Ishiko::Test& test);
    static void WriteLEB128Test3(Ishiko::Test& test);
    static void WriteLEB128Test4(Ishiko::Test& test);
    static void WriteLEB128Test5(Ishiko::Test& test);
};

#endif
