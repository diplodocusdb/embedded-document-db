/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDTESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class RecordTests : public Ishiko::TestSequence
{
public:
    RecordTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
    static void ReadMasterFileMetadataTest1(Ishiko::Test& test);
    static void ReadDataStartTest1(Ishiko::Test& test);
    static void ReadDataEndTest1(Ishiko::Test& test);
    static void ReadNodeStartTest1(Ishiko::Test& test);
    static void ReadNodeEndTest1(Ishiko::Test& test);
    static void ReadParentNodeIDTest1(Ishiko::Test& test);
    static void ReadNodeNameTest1(Ishiko::Test& test);
    static void ReadNodeNameTest2(Ishiko::Test& test);
    static void ReadNodeIDTest1(Ishiko::Test& test);
    static void ReadNodeIDTest2(Ishiko::Test& test);
    static void ReadPersistentNodeIDTest1(Ishiko::Test& test);
    static void ReadInlineValueBinaryTest1(Ishiko::Test& test);
    static void ReadInlineValueBooleanTest1(Ishiko::Test& test);
    static void ReadInlineValueUTF8StringTest1(Ishiko::Test& test);
    static void WriteMasterFileMetadataTest1(Ishiko::Test& test);
    static void WriteDataStartTest1(Ishiko::Test& test);
    static void WriteDataEndTest1(Ishiko::Test& test);
    static void WriteNodeStartTest1(Ishiko::Test& test);
    static void WriteNodeEndTest1(Ishiko::Test& test);
    static void WriteParentNodeIDTest1(Ishiko::Test& test);
    static void WriteNodeNameTest1(Ishiko::Test& test);
    static void WriteNodeNameTest2(Ishiko::Test& test);
    static void WriteNodeIDTest1(Ishiko::Test& test);
    static void WriteNodeIDTest2(Ishiko::Test& test);
    static void WritePersistentNodeIDTest1(Ishiko::Test& test);
    static void WriteInlineValueBinaryTest1(Ishiko::Test& test);
    static void WriteInlineValueBooleanTest1(Ishiko::Test& test);
    static void WriteInlineValueUTF8StringTest1(Ishiko::Test& test);
};

#endif
