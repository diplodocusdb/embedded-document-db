/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_

#include <Ishiko/Tests.h>

class XMLTreeDBTests : public Ishiko::Tests::TestSequence
{
public:
    XMLTreeDBTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void CreateTest1(Ishiko::Tests::FileComparisonTest& test);
    static void OpenTest1(Ishiko::Tests::Test& test);
    static void OpenTest2(Ishiko::Tests::Test& test);
    static void OpenTest3(Ishiko::Tests::Test& test);
    static void OpenTest4(Ishiko::Tests::Test& test);
    static void OpenTest5(Ishiko::Tests::Test& test);
    static void OpenTest6(Ishiko::Tests::Test& test);
    static void OpenTest7(Ishiko::Tests::Test& test);
    static void ParentTest1(Ishiko::Tests::Test& test);
    static void ParentTest2(Ishiko::Tests::Test& test);
    static void ChildNodesTest1(Ishiko::Tests::Test& test);
    static void ChildNodesTest2(Ishiko::Tests::Test& test);
    static void NextSiblingTest1(Ishiko::Tests::Test& test);
    static void NextSiblingTest2(Ishiko::Tests::Test& test);
    static void NextSiblingTest3(Ishiko::Tests::Test& test);
    static void InsertChildNodeTest1(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest1(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest2(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest3(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest4(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest5(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest6(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest7(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest8(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest9(Ishiko::Tests::FileComparisonTest& test);
    static void AppendChildNodeTest10(Ishiko::Tests::FileComparisonTest& test);
    static void SetChildNodeTest1(Ishiko::Tests::FileComparisonTest& test);
    static void SetChildNodeTest2(Ishiko::Tests::FileComparisonTest& test);
    static void RemoveAllChildNodesTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
