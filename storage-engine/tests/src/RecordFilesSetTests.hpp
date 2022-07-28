/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILESSETTESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILESSETTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class RecordFilesSetTests : public Ishiko::TestSequence
{
public:
    RecordFilesSetTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
    static void CreateMasterFileTest1(Ishiko::Test& test);
    static void OpenMasterFileTest1(Ishiko::Test& test);
    static void OpenMasterFileTest2(Ishiko::Test& test);
    static void FindSiblingNodesRecordGroupTest1(Ishiko::Test& test);
    static void FindSiblingNodesRecordGroupTest2(Ishiko::Test& test);
    static void FindSiblingNodesRecordGroupTest3(Ishiko::Test& test);
};

#endif
