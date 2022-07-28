/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBStorageEngineTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/EmbeddedDocumentDBStorageEngine.hpp"

using namespace DiplodocusDB;
using namespace Ishiko;

EmbeddedDocumentDBStorageEngineTests::EmbeddedDocumentDBStorageEngineTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "EmbeddedDocumentDBStorageEngine tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("createMasterFile test 1", CreateMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 1", OpenMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 2", OpenMasterFileTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 1", FindSiblingNodesRecordGroupTest1);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 2", FindSiblingNodesRecordGroupTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 3", FindSiblingNodesRecordGroupTest3);
}

void EmbeddedDocumentDBStorageEngineTests::ConstructionTest1(Test& test)
{
    EmbeddedDocumentDBStorageEngine storageEngine;

    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::CreateMasterFileTest1(Test& test)
{
    const char* basename = "MasterFileTests_CreateTest1.dpdb";

    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.createMasterFile(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_FAIL_IF(error);

    storageEngine.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::OpenMasterFileTest1(Test& test)
{
    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup;
    bool found = storageEngine.findSiblingNodesRecordGroup(NodeID(0), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup->size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ((*siblingsNodesRecordGroup)[0].name(), "/");
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::OpenMasterFileTest2(Test& test)
{
    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup;
    bool found = storageEngine.findSiblingNodesRecordGroup(NodeID(1), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup->size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ((*siblingsNodesRecordGroup)[0].name(), "key1");
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::FindSiblingNodesRecordGroupTest1(Test& test)
{
    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = storageEngine.findSiblingNodesRecordGroup(NodeID(0), siblingsNodesRecordGroup1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup1->size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ((*siblingsNodesRecordGroup1)[0].name(), "/");

    // Verify the cache is working as expected
    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = storageEngine.findSiblingNodesRecordGroup(NodeID(0), siblingsNodesRecordGroup2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found2);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup1.get(), siblingsNodesRecordGroup2.get());

    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::FindSiblingNodesRecordGroupTest2(Test& test)
{
    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = storageEngine.findSiblingNodesRecordGroup(NodeID(1), siblingsNodesRecordGroup1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup1->size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ((*siblingsNodesRecordGroup1)[0].name(), "key1");

    // Verify the cache is working as expected
    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = storageEngine.findSiblingNodesRecordGroup(NodeID(1), siblingsNodesRecordGroup2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found2);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup1.get(), siblingsNodesRecordGroup2.get());

    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBStorageEngineTests::FindSiblingNodesRecordGroupTest3(Test& test)
{
    Error error;

    EmbeddedDocumentDBStorageEngine storageEngine;
    storageEngine.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = storageEngine.findSiblingNodesRecordGroup(NodeID(3), siblingsNodesRecordGroup1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(!found1);

    // Verify the cache is working as expected
    std::shared_ptr<SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = storageEngine.findSiblingNodesRecordGroup(NodeID(3), siblingsNodesRecordGroup2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(!found2);

    ISHIKO_TEST_PASS();
}
