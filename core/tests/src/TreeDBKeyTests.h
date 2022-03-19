/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBKEYTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBKEYTESTS_H_

#include <Ishiko/Tests.hpp>

class TreeDBKeyTests : public Ishiko::TestSequence
{
public:
    TreeDBKeyTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
    static void ParentKeyTest1(Ishiko::Test& test);
    static void ParentKeyTest2(Ishiko::Test& test);
    static void ParentKeyTest3(Ishiko::Test& test);
    static void BaseTest1(Ishiko::Test& test);
    static void BaseTest2(Ishiko::Test& test);
    static void BaseTest3(Ishiko::Test& test);
    static void BaseTest4(Ishiko::Test& test);
};

#endif
