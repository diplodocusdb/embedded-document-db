/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_MASTERFILETESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_MASTERFILETESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class MasterFileTests : public Ishiko::TestSequence
{
public:
    MasterFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest1(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest2(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest3(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest4(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest5(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest6(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest7(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest8(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest9(Ishiko::Test& test);
    static void AddSiblingNodesRecordGroupTest10(Ishiko::Test& test);
    // TODO
    //static void RemoveSiblingNodesRecordGroupTest1(Ishiko::Test& test);
};

#endif
