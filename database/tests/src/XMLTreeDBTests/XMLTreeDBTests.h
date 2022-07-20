/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_

#include <Ishiko/TestFramework.hpp>

class XMLTreeDBTests : public Ishiko::TestSequence
{
public:
    XMLTreeDBTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void OpenTest3(Ishiko::Test& test);
    static void OpenTest4(Ishiko::Test& test);
    static void OpenTest5(Ishiko::Test& test);
    static void OpenTest6(Ishiko::Test& test);
    static void OpenTest7(Ishiko::Test& test);
    static void OpenTest8(Ishiko::Test& test);
    static void OpenTest9(Ishiko::Test& test);
    static void OpenTest10(Ishiko::Test& test);
    static void ParentTest1(Ishiko::Test& test);
    static void ParentTest2(Ishiko::Test& test);
    static void ChildNodesTest1(Ishiko::Test& test);
    static void ChildNodesTest2(Ishiko::Test& test);
    static void NextSiblingTest1(Ishiko::Test& test);
    static void NextSiblingTest2(Ishiko::Test& test);
    static void NextSiblingTest3(Ishiko::Test& test);
    static void InsertChildNodeTest1(Ishiko::Test& test);
    static void AppendChildNodeTest1(Ishiko::Test& test);
    static void AppendChildNodeTest2(Ishiko::Test& test);
    static void AppendChildNodeTest3(Ishiko::Test& test);
    static void AppendChildNodeTest4(Ishiko::Test& test);
    static void AppendChildNodeTest5(Ishiko::Test& test);
    static void AppendChildNodeTest6(Ishiko::Test& test);
    static void AppendChildNodeTest7(Ishiko::Test& test);
    static void AppendChildNodeTest8(Ishiko::Test& test);
    static void AppendChildNodeTest9(Ishiko::Test& test);
    static void AppendChildNodeTest10(Ishiko::Test& test);
    static void SetChildNodeTest1(Ishiko::Test& test);
    static void SetChildNodeTest2(Ishiko::Test& test);
    static void RemoveAllChildNodesTest1(Ishiko::Test& test);
};

#endif
