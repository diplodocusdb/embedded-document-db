/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_DATABASE_TESTS_EMBEDDEDDOCUMENTDDBTESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_DATABASE_TESTS_EMBEDDEDDOCUMENTDDBTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class EmbeddedTreeDBTests : public Ishiko::TestSequence
{
public:
    EmbeddedTreeDBTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void OpenTest3(Ishiko::Test& test);
    static void OpenTest4(Ishiko::Test& test);
    static void OpenTest5(Ishiko::Test& test);
    static void ChildNodesTest1(Ishiko::Test& test);
    static void ChildNodesTest2(Ishiko::Test& test);
    static void InsertChildNodeTest1(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest1(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest2(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest3(Ishiko::Test& test);
    static void InsertChildNodeAfterTest1(Ishiko::Test& test);
    static void InsertChildNodeAfterTest2(Ishiko::Test& test);
    static void AppendChildNodeTest1(Ishiko::Test& test);
    static void AppendChildNodeTest2(Ishiko::Test& test);
    static void AppendChildNodeTest3(Ishiko::Test& test);
    static void AppendChildNodeTest4(Ishiko::Test& test);
    static void AppendChildNodeTest5(Ishiko::Test& test);
    static void AppendChildNodeTest6(Ishiko::Test& test);
    static void RemoveChildNodeTest1(Ishiko::Test& test);
    static void RemoveAllChildNodesTest1(Ishiko::Test& test);
};

#endif
