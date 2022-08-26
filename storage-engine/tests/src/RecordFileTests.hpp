/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILETESTS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILETESTS_HPP

#include <Ishiko/TestFramework.hpp>

class RecordFileTests : public Ishiko::TestSequence
{
public:
    RecordFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void AllocatePageTest1(Ishiko::Test& test);
    static void AllocatePageTest2(Ishiko::Test& test);
    static void StorePageTest1(Ishiko::Test& test);
    static void StorePageTest2(Ishiko::Test& test);
    static void InsertPageAfterTest1(Ishiko::Test& test);
};

#endif
