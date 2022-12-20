/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDPAGEWORKINGSETTESTS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDPAGEWORKINGSETTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class RecordPageWorkingSetTests : public Ishiko::TestSequence
{
public:
    RecordPageWorkingSetTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void GetTest1(Ishiko::Test& test);
};

#endif
