/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_SIBLINGNODESRECORDGROUPCACHETESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_SIBLINGNODESRECORDGROUPCACHETESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class SiblingNodesRecordGroupCacheTests : public Ishiko::TestSequence
{
public:
    SiblingNodesRecordGroupCacheTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
    static void SubscriptOperatorTest1(Ishiko::Test& test);
    static void SubscriptOperatorTest2(Ishiko::Test& test);
    static void FindTest1(Ishiko::Test& test);
    static void FindTest2(Ishiko::Test& test);
    static void EraseTest1(Ishiko::Test& test);
};

#endif
